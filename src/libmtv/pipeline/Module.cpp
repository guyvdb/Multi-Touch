#include <QDebug>
#include "Module.h"

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

}
