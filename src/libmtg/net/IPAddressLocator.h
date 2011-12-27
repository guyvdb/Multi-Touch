#ifndef IPADDRESSLOCATOR_H
#define IPADDRESSLOCATOR_H

#include <QString>

#include "libmtg_global.h"

namespace mtdnd {

  class LIBMTG_EXPORT IPAddressLocator
  {
  public:
    static QString getMachineAddress();
  };

}

#endif // IPADDRESSLOCATOR_H
