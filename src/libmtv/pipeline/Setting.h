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
      enum PropertyType {
          NONE,
          BOOLEAN,
          STRING,
          INTEGER,
          DOUBLE,
          POINTLIST,
          FRAME
      };

      /* constructors */
      Setting(const QString name);
      Setting(const QString name, bool value);
      Setting(const QString name, const QString value);
      Setting(const QString name, int value);
      Setting(const QString name, double value);
      Setting(const QString name, Module *module, const QString frameName);

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

      /* property type */
      PropertyType getPropertyType() {return this->type;}

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

      /* frame info */
      Module * getModule();
      QString getFrameName() const;

      /* name */
      QString getName() const;


  signals:
      void beforeSettingChanged(mtv::Setting *setting);
      void afterSettingChanged(mtv::Setting *setting);
  private:
    PropertyType type;
    QString name;
    QString frameName;



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
