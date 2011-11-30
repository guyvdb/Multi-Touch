#include "ModuleError.h"

namespace mtv {

ModuleError::ModuleError(const QString instanceName, const QString propname, const QString message)
  : instanceName(instanceName), propname(propname), message(message)
  {
  }

}
