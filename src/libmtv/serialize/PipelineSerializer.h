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
#ifndef PIPELINESERIALIZER_H
#define PIPELINESERIALIZER_H

#include <QObject>
#include <QXmlStreamReader>

#include "libmtv_global.h"

#include "pipeline/Module.h"

namespace mtv {

  class LateBind : public QObject {
    Q_OBJECT
  public:
    LateBind(Setting * setting, const QString instanceName, const QString frameName);

    Setting *getSetting() {return this->setting;}
    QString getInstanceName() {return this->instanceName;}
    QString getFrameName() {return this->frameName;}
    //QString getPropertyName() {return this->propertyName; }

  private:
    Setting *setting;
    QString instanceName;
    QString frameName;
    //QString propertyName;
  };

  class LIBMTV_EXPORT PipelineSerializer : public QObject
  {
      Q_OBJECT
  public:
      PipelineSerializer();

      bool loadPipeline(QString filename, QStringList &errors);
      bool loadPipeline(QByteArray &bytes, QStringList &errors);

      bool savePipeline(QString filename);
      bool savePipeline(QByteArray &bytes);

  private:
      Module *createModule(QXmlStreamReader *xml, QStringList &errors);
      void addSetting(QXmlStreamReader *xml, Module* module, QStringList &errors);


      void addBooleanSetting(const QString name, const QString value, Module* module, QStringList &errors);
      void addStringSetting(const QString name, const QString value, Module* module, QStringList &errors);
      void addIntegerSetting(const QString name, const QString value, Module* module, QStringList &errors);
      void addDoubleSetting(const QString name, const QString value, Module* module, QStringList &errors);
      void addPointListSetting(const QString name, const QString value, Module* module, QStringList &errors);
      void addFrameSetting(const QString name, const QString value, Module* module, QStringList &errors);

      void preformLateBinds(QStringList &errors);
      void clearLateBindings();
      QList<LateBind*> lateBindings;


  };

}

#endif // PIPELINESERIALIZER_H
