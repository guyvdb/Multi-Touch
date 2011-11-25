#include "Module.h"

namespace mtv {

  /* -------------------------------------------------------------------------------------------
   * Default constructor
   * ------------------------------------------------------------------------------------------- */
  Module::Module() : QObject()
  {
    //this->addProp("threaded",false);
    //this->addProp("instance","unknown");
    this->timer = new QTimer();
    this->timer->setSingleShot(false);
    this->connect(this->timer, SIGNAL(timeout()), this, SLOT(OnTimerTimedOut()));
  }

  /* -------------------------------------------------------------------------------------------
   * Destructor
   * ------------------------------------------------------------------------------------------- */
  Module::~Module() {
    // DELETE all errors
    this->clearErrors();
    delete this->timer;
    QHash<QString, Setting*>::iterator i;
    for(i=this->settings.begin(); i != this->settings.end(); i++) delete i.value();
    this->settings.clear();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Setting *Module::setting(const QString name) {
    if(!this->settings.contains(name)) {
      Setting *s = new Setting(name);
      this->settings[name] = s;
    }
    return this->settings[name];
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  /*bool Module::setProp(const QString name, QVariant value) {
    if (!this->props.contains(name)) {
      this->lastError = "No such property '" + name + "'";
      return false;
    }
    Prop *p = this->props[name];
    p->setValue(value);
    return true;
  }*/

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  /*Prop* Module::getProp(const QString name){
    if (!this->props.contains(name)) {
      this->lastError = "No such property '" + name + "'";
      return 0x0;
    }
    return this->props[name];
  }*/

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  /*Prop* Module::addProp(const QString name) {
    if(this->props.contains(name)) {
      this->lastError = "Property with name '" + name + "' already exists.";
      return 0x0;
    }

    Prop *p = new Prop(name);
    this->props[name] = p;
    return p;
  }*/

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
 /* Prop* Module::addProp(const QString name, QVariant value) {
    if(this->props.contains(name)) {
      this->lastError = "Property with name '" + name + "' already exists.";
      return 0x0;
    }

    Prop* p = this->addProp(name);
    if(p){
      p->setValue(value);
    }
    return p;
  }*/


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
    ModuleError *error = new ModuleError(this->createQualifiedName(), propname,message);
    this->errors.append(error);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Module::addError(const QString message) {

    ModuleError *error = new ModuleError(this->createQualifiedName(), "General", message);
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
  QString Module::createQualifiedName(const QString moduleName, const QString instanceName) {
     return moduleName + "->" + instanceName;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QString  Module::createQualifiedName() {
    return Module::createQualifiedName(this->moduleName,  this->setting("instance")->asString());
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QString Module::getInstanceName() {
    return this->setting("instance")->asString();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Module::startTicking(int frequency) {
    this->timer->setInterval(frequency);
    this->timer->start();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Module::stopTicking() {
    this->timer->stop();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Module::OnTimerTimedOut() {
    this->tick();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  /*void Module::frameReady(const QString name, cv::Mat &matrix) {

  }*/

}
