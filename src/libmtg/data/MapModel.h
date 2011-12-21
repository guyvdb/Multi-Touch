#ifndef MAPMODEL_H
#define MAPMODEL_H

#include "libmtg_global.h"
#include <QString>

namespace mtg {

  class LIBMTG_EXPORT MapModel
  {
  public:
      MapModel(const QString name, const QString file);
      QString name;
      QString file;
  };

}

#endif // MAPMODEL_H
