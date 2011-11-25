#include "ModuleError.h"

namespace mtv {

ModuleError::ModuleError(const QString qualifiedModuleName, const QString propname, const QString message)
  : qualifiedName(qualifiedModuleName), propname(propname), message(message)
  {
  }

}
