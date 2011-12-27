#ifndef MAPMODEL_H
#define MAPMODEL_H

#include "libmtg_global.h"
#include <QString>

#include "BaseModel.h"

namespace mtdnd {

  class LIBMTG_EXPORT MapModel : public BaseModel
  {
  public:
      MapModel(const QString name, const QString file, QString id="");
      QString name;
      QString file;
  };

}

#endif // MAPMODEL_H
