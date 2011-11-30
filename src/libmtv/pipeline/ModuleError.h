/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */
#ifndef MODULEERROR_H
#define MODULEERROR_H

#include <QString>

namespace mtv {

  class ModuleError
  {
  public:
      ModuleError(const QString instanceName, const QString propname, const QString message);
      QString getInstanceName() const {return this->instanceName;}
      QString getPropName() const {return this->propname;}
      QString getMessage() const {return this->message;}
  private:
    QString instanceName;
    QString propname;
    QString message;
  };

}

#endif // MODULEERROR_H
