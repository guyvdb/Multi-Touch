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
#include <QDebug>
#include "Module.h"

#include <opencv2/highgui/highgui.hpp>

namespace mtv {

  /* -------------------------------------------------------------------------------------------
   * Default constructor
   * ------------------------------------------------------------------------------------------- */
  Module::Module() : QObject()
  {
  }

  /* -------------------------------------------------------------------------------------------
   * Destructor
   * ------------------------------------------------------------------------------------------- */
  Module::~Module() {
    this->clearErrors();
    QHash<QString, Setting*>::iterator i;
    for(i=this->settings.begin(); i != this->settings.end(); i++) delete i.value();
    this->settings.clear();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Setting *Module::setting(const QString name) {
    if(!this->settings.contains(name)) {
      Setting *s = new Setting(this, name);
      this->settings[name] = s;
    }
    return this->settings[name];
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Module::listSettings(QList<Setting*> &result) {
    QHash<QString, Setting*>::iterator i;
    for(i=this->settings.begin(); i != this->settings.end(); i++) result.append(i.value());
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool Module::isCapable(int flag) {
    return this->capabilities() & flag;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Module::addError(const QString propname, const QString message) {
    ModuleError *error = new ModuleError(this->getInstanceName(), propname,message);
    this->errors.append(error);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Module::addError(const QString message) {
    ModuleError *error = new ModuleError(this->getInstanceName(), "General", message);
    this->errors.append(error);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Module::clearErrors() {
    foreach(ModuleError *e, this->errors) delete e;
    this->errors.clear();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Module::hookFrameHandler(Module *source) {
    //qDebug() << "THIS: " << this << " SOURCE: " << source;
    qDebug() << "HOOK: " << source->getModuleName() << ":" << source->getInstanceName() << " -> " << this->getModuleName() << ":" << this->getInstanceName();
    this->connect(source,SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrame(mtv::Module*,QString,cv::Mat&)));
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Module::unhookFrameHandler(Module *source) {
    qDebug() << "UNHOOK: " << source->getModuleName() << ":" << source->getInstanceName() << " -> " << this->getModuleName() << ":" << this->getInstanceName();
    this->disconnect(source,SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrame(mtv::Module*,QString,cv::Mat&)));
  }

  /* -------------------------------------------------------------------------------------------
   * debugging method
   * ------------------------------------------------------------------------------------------- */
  void Module::save(const QString filename, cv::Mat &frame) {
    QString file = "../debug/";
    file.append(filename);
    file.append(".jpg");

    qDebug() << "SAVE FRAME: " << file << " Empty=" << frame.empty();

    std::string path(file.toAscii().constData());
    cv::imwrite(path,frame);
  }




}
