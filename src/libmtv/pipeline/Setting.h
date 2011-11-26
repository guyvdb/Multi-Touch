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

      Setting(const QString name);
      Setting(const QString name, bool value);
      Setting(const QString name, const QString value);
      Setting(const QString name, int value);
      Setting(const QString name, double value);
      Setting(const QString name, Module *module, const QString frameName);

      bool isReadOnly();
      void setReadOnly(bool value);

      bool hasMin();
      void setHasMin(bool value);
      int getMin();
      void setMin(int value);

      bool hasMax();
      void setHasMax(bool value);
      int getMax();
      void setMax(int value);

      PropertyType getPropertyType() {return this->type;}

      void set(const QString value);
      void set(bool value);
      void set(int value);
      void set(double value);
      void set(Module*module, const QString frameName);

      bool asBool();
      QString asString();
      double asDouble();
      int asInteger();

      Module * getModule();
      QString getFrameName() const;
      QString getName() const;

      //void hookModule(const char *amember, Qt::ConnectionType atype);  // hook the modules frameReady event to amember, atype
      //void unhookModule(const char *amember, Qt::ConnectionType atype);// unhook the modules frameReady event from amember, atype

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


    void init();

  signals:

  public slots:

  };

}
#endif // PROPERTY_H
