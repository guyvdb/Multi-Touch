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
#ifndef PROPERTY_H
#define PROPERTY_H

#include <QObject>
#include "libmtv_global.h"

namespace mtv {

  class Module;

  class LIBMTV_EXPORT Setting : public QObject
  {
      Q_OBJECT
  public:
      enum SettingType {
          NONE,
          BOOLEAN,
          STRING,
          INTEGER,
          DOUBLE,
          POINTLIST,
          FRAME
      };

      /* constructors */
      Setting(Module *owner, const QString name);
      Setting(Module *owner, const QString name, bool value);
      Setting(Module *owner, const QString name, const QString value);
      Setting(Module *owner, const QString name, int value);
      Setting(Module *owner, const QString name, double value);
      Setting(Module *owner, const QString name, Module *module, const QString frameName);

      /* read only */
      bool isReadOnly();
      void setReadOnly(bool value);

      /* min integer value */
      bool hasMin();
      void setHasMin(bool value);
      int getMin();
      void setMin(int value);

      /* max integer value */
      bool hasMax();
      void setHasMax(bool value);
      int getMax();
      void setMax(int value);

      /* choices */
      bool hasChoices();
      void setHasChoices(bool value);
      QString getChoices();
      void setChoices(const QString value);

      /* setting type */
      SettingType getType() {return this->type;}

      /* set value */
      void set(const QString value);
      void set(bool value);
      void set(int value);
      void set(double value);
      void set(Module*module, const QString frameName);

      /* get value */
      bool asBool();
      QString asString();
      double asDouble();
      int asInteger();

      QString displayValue();

      /* frame info */
      Module * getModule();
      QString getFrameName() const;

      /* name */
      QString getName() const;


  signals:
      void beforeSettingChanged(mtv::Setting *setting);
      void afterSettingChanged(mtv::Setting *setting);
  private:
    SettingType type;
    QString name;
    QString frameName;


    Module *owner;

    bool bValue;
    QString sValue;
    int iValue;
    double dValue;
    Module* mValue;

    bool readOnly;
    bool hasMaxValue;
    bool hasMinValue;
    int maxValue;
    int minValue;

    bool hasValueChoices;
    QString choices;

    void init();

  signals:

  public slots:

  };

}
#endif // PROPERTY_H
