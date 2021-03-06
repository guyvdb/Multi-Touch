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
#include "Setting.h"
#include "pipeline/Module.h"

#include <QDebug>
namespace mtv {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Setting::Setting(Module *owner, const QString name) : QObject(), owner(owner) {
    this->init();
    this->name = name;

  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Setting::Setting(Module *owner, const QString name, bool value) : QObject(), owner(owner) {
    this->init();
    this->name = name;
    this->bValue = value;
    this->type = BOOLEAN;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Setting::Setting(Module *owner, const QString name, const QString value) : QObject(), owner(owner) {
    this->init();
    this->name = name;
    this->sValue = value;
    this->type = STRING;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Setting::Setting(Module *owner, const QString name, int value) : QObject(), owner(owner) {
    this->init();
    this->name = name;
    this->iValue = value;
    this->type = INTEGER;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Setting::Setting(Module *owner, const QString name, double value) : QObject(), owner(owner) {
    this->init();
    this->name = name;
    this->dValue = value;
    this->type = DOUBLE;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Setting::Setting(Module *owner, const QString name, Module *module, const QString frameName) : QObject(), owner(owner) {
    this->init();
    this->name = name;
    this->mValue = module;
    this->type = FRAME;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Setting::init() {
    this->readOnly = false;
    this->hasMaxValue = false;
    this->hasMinValue = false;
    this->maxValue = 0;
    this->minValue = 0;
    this->mValue = 0x0;
    this->choices = "";
    this->hasValueChoices = false;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool Setting::isReadOnly() {
    return this->readOnly;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Setting::setReadOnly(bool value) {
    this->readOnly = value;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool Setting::hasMin() {
    return this->hasMaxValue;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Setting::setHasMin(bool value) {
    this->hasMinValue = value;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  int Setting::getMin() {
    return this->minValue;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Setting::setMin(int value) {
    this->minValue = value;
    this->hasMinValue = true;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool Setting::hasMax() {
    return this->hasMaxValue;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Setting::setHasMax(bool value) {
    this->hasMaxValue = value;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  int Setting::getMax() {
    return this->maxValue;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Setting::setMax(int value) {
    this->maxValue = value;
    this->hasMaxValue = true;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool Setting::hasChoices() {
    return this->hasValueChoices;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Setting::setHasChoices(bool value) {
    this->hasValueChoices = value;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QString Setting::getChoices() {
    return this->choices;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Setting::setChoices(const QString value) {
    this->hasValueChoices = true;
    this->choices = value;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Setting::set(const QString value) {
    emit beforeSettingChanged(this);
    this->sValue = value;
    this->type = STRING;
    emit afterSettingChanged(this);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Setting::set(bool value) {
    emit beforeSettingChanged(this);
    this->bValue = value;
    this->type = BOOLEAN;
    emit afterSettingChanged(this);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Setting::set(int value) {
    emit beforeSettingChanged(this);
    this->iValue = value;
    this->type = INTEGER;
    emit afterSettingChanged(this);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Setting::set(double value) {
    emit beforeSettingChanged(this);
    this->dValue = value;
    this->type = DOUBLE;
    emit afterSettingChanged(this);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Setting::set(Module*module, const QString frameName) {

    if(this->mValue != 0x0) this->owner->unhookFrameHandler(this->mValue);

    emit beforeSettingChanged(this);
    this->mValue = module;
    this->frameName = frameName;
    this->type = FRAME;


    if(module != 0x0) this->owner->hookFrameHandler(module);

    emit afterSettingChanged(this);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool Setting::asBool() {
    Q_ASSERT(this->type == BOOLEAN);
    return this->bValue;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QString Setting::asString() {
    Q_ASSERT(this->type == STRING);
    return this->sValue;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  double Setting::asDouble() {
    Q_ASSERT(this->type == DOUBLE);
    return this->dValue;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  int Setting::asInteger() {
    Q_ASSERT(this->type == INTEGER);
    return this->iValue;
  }

  QString Setting::displayValue() {
    switch(this->type) {
    case NONE:
      return "none";
    case BOOLEAN:
      return this->asBool() ? "true" : "false";
    case STRING:
      return this->asString();
    case INTEGER:
      return QString::number(this->asInteger());
    case DOUBLE:
      return QString::number(this->asDouble());
    case POINTLIST:
      return "point-list";
    case FRAME:
      return "frame";
    }
    return "error";
  }



  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Module * Setting::getModule() {
    return this->mValue;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QString Setting::getFrameName() const {
    return this->frameName;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QString Setting::getName() const {
    return this->name;
  }



}
