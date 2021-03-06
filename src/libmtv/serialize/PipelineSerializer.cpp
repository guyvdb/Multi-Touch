/* -------------------------------------------------------------------------------------------
 *                                   M U L T I - T O U C H
 *  -------------------------------------------------------------------------------------------
 *                             Copyright 2011, 2012 Guy van den Berg
 *                                      All Rights Reserved
 *
 *          This program is free software; you can redistribute it and/or modify it
 *          under the terms of the GNU General Public License as published by the Free
 *          Software Foundation; either version 2 of the License, or (at your option)
 *          any later version.
 *
 *          This program is distributed in the hope that it will be useful, but WITHOUT
 *          ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *          FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *          more details.
 *
 *          You should have received a copy of the GNU General Public License along with
 *          this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * ------------------------------------------------------------------------------------------- */
#include "PipelineSerializer.h"

#include <QFile>
#include <QDebug>


#include <QXmlStreamWriter>
#include <QStringList>
#include "pipeline/Setting.h"

#include "pipeline/Pipeline.h"

namespace mtv {

  LateBind::LateBind(Setting *setting, const QString instanceName, const QString frameName)
    : QObject(), setting(setting), instanceName(instanceName), frameName(frameName) {

  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  PipelineSerializer::PipelineSerializer() : QObject()
  {
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool PipelineSerializer::loadPipeline(QString filename, QStringList &errors) {
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      return false;
    }

    QByteArray bytes = file.readAll();
    file.close();
    return this->loadPipeline(bytes,errors);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool PipelineSerializer::loadPipeline(QByteArray &bytes, QStringList &errors) {
    Pipeline* pipeline = Pipeline::instance();

    if(pipeline->isRunning()) pipeline->stop();
    pipeline->clear();

    QXmlStreamReader r(bytes);
    Module* module = 0x0;

    while(!r.atEnd() && !r.hasError()) {
      QXmlStreamReader::TokenType token = r.readNext();


      if (token == QXmlStreamReader::StartElement) {
        QString name = r.name().toString();
        if(name == "setting") {
          if(module != 0x0) {
            this->addSetting(&r,module,errors);
          }
        } else if (name == "module") {
          if(module != 0x0) {
            pipeline->addModule(module);
          }
          module = this->createModule(&r, errors);
        } else if (name == "pipeline") {

        }
      }

    }

    //add last module
    if(module != 0x0) pipeline->addModule(module);

    this->preformLateBinds(errors);

    return true;

  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool PipelineSerializer::savePipeline(QString filename) {
    QByteArray bytes;
    if(!this->savePipeline(bytes)) {
      return false;
    }

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      return false;
    }

    qint64 written = file.write(bytes);
    file.close();

    if(written == bytes.length()) {
      return true;
    } else {
      return false;
    }

  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool PipelineSerializer::savePipeline(QByteArray &bytes) {
    Pipeline* pipeline = Pipeline::instance();
    QXmlStreamWriter w(&bytes);
    w.setAutoFormatting(true);
    w.writeStartDocument();
    w.writeStartElement("pipeline");
    w.writeAttribute("name",pipeline->getName());

    QList<Module*> modules;
    pipeline->listModules(modules);

    this->clearLateBindings();

    foreach(Module* module, modules) {
      w.writeStartElement("module");
      w.writeAttribute("name", module->getInstanceName());
      w.writeAttribute("type", module->getModuleName());

      QList<Setting*> settings;
      module->listSettings(settings);
      foreach(Setting *setting, settings) {
        w.writeStartElement("setting");
        w.writeAttribute("name", setting->getName());
        switch(setting->getType()) {
          case Setting::NONE :
            w.writeAttribute("type","none");
            break;
          case Setting::BOOLEAN :
            w.writeAttribute("type","boolean");
            w.writeAttribute("value",setting->asBool() ? "true" : "false");
            break;
          case Setting::STRING :
            w.writeAttribute("type","string");
            w.writeAttribute("value",setting->asString());
            break;
          case Setting::INTEGER :
            w.writeAttribute("type","integer");
            w.writeAttribute("value", QString::number(setting->asInteger()));
            break;
          case Setting::DOUBLE :
            w.writeAttribute("type","double");
            w.writeAttribute("value", QString::number(setting->asDouble()));
            break;
          case Setting::POINTLIST :
            w.writeAttribute("type","points");
            break;
          case Setting::FRAME :
            w.writeAttribute("type","frame");

            Module* m = setting->getModule();
            if(m != 0x0) {
              QString value = m->getInstanceName() + ":" + setting->getFrameName();
              w.writeAttribute("value", value);
            }
            break;
        }
        w.writeEndElement();
      }
      w.writeEndElement();
    }
    w.writeEndDocument();

    return true;
  }

  Module *PipelineSerializer::createModule(QXmlStreamReader *xml, QStringList &errors) {
    QString moduleName = xml->attributes().value("type").toString();
    QString instanceName = xml->attributes().value("name").toString();

    Module *result = Pipeline::instance()->createModule(moduleName, instanceName);
    if(result == 0x0) errors.append(Pipeline::instance()->getLastError());
    return result;
  }

  void PipelineSerializer::addSetting(QXmlStreamReader *xml, Module* module, QStringList &errors) {
    QString name = xml->attributes().value("name").toString();
    QString type = xml->attributes().value("type").toString();
    QString value = xml->attributes().value("value").toString();

    if(type == "boolean") {
      this->addBooleanSetting(name, value, module, errors);
    } else if (type == "string") {
      this->addStringSetting(name, value, module, errors);
    } else if (type == "integer") {
      this->addIntegerSetting(name, value, module, errors);
    } else if (type == "double") {
      this->addDoubleSetting(name, value, module, errors);
    } else if (type == "points") {
      this->addPointListSetting(name, value, module, errors);
    } else if (type == "frame") {
       this->addFrameSetting(name, value, module, errors);
    } else {
      errors.append("WARNING: Unknown setting type: " + type);
    }
  }



  void PipelineSerializer::addBooleanSetting(const QString name, const QString value, Module* module, QStringList &errors) {
    QString v = value.toLower();
    bool b = (v == "true" || v == "t" || v == "on" || v == "1" || v == "yes" || v =="y");
    module->setting(name)->set(b);
  }

  void PipelineSerializer::addStringSetting(const QString name, const QString value, Module* module, QStringList &errors) {
    module->setting(name)->set(value);
  }

  void PipelineSerializer::addIntegerSetting(const QString name, const QString value, Module* module, QStringList &errors) {
    bool ok = false;
    int i = value.toInt(&ok);
    if(ok) {
      module->setting(name)->set(i);
    } else {
      //TODO check min/max values
      errors.append("Setting: " + name + " not set on " + module->getModuleName() + ":" + module->getInstanceName() + ". Not an integer");
    }
  }

  void PipelineSerializer::addDoubleSetting(const QString name, const QString value, Module* module, QStringList &errors) {
    bool ok = false;
    double d = value.toDouble(&ok);
    if(ok) {
      qDebug() << "Setting " << name << " = " << d << " as double. Values = " << value;
      module->setting(name)->set(d);
    } else {
      //TODO check min/max values
      errors.append("Setting: " + name + " not set on " + module->getModuleName() + ":" + module->getInstanceName() + ". Not a double.");
    }
  }

  void PipelineSerializer::addPointListSetting(const QString name, const QString value, Module* module, QStringList &errors) {
    // not used yet
    Q_ASSERT(false);
  }

  void PipelineSerializer::addFrameSetting(const QString name, const QString value, Module* module, QStringList &errors) {
    QStringList parts = value.split(":");

    if(parts.length() != 2) {
      errors.append("Setting: " + name + " not set on " + module->getModuleName() + ":" + module->getInstanceName() + ". Format incorrect. Use <name:frame name>");
    } else {
      this->lateBindings.append(new LateBind( module->setting(name),parts[0],parts[1]));
    }
  }

  void PipelineSerializer::preformLateBinds(QStringList &errors) {
    foreach(LateBind* bind, this->lateBindings)  {
      Module *module = Pipeline::instance()->getModule(bind->getInstanceName());
      if(module != 0x0) {
        Setting *setting = bind->getSetting();
        setting->set(module,bind->getFrameName());
      } else {
        errors.append("Could not find " + bind->getInstanceName() + ":" + bind->getFrameName());

      }
    }

    this->clearLateBindings();
  }

  void PipelineSerializer::clearLateBindings() {
    foreach(LateBind* bind, this->lateBindings) delete bind;
    this->lateBindings.clear();
  }



}

