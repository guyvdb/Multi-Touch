#include "BaseModel.h"

namespace mtdnd {

  BaseModel::BaseModel(const QString id)
  {
    this->id = id.isEmpty() ? this->createIdentity() : id;
  }

  QString BaseModel::createIdentity() {
    QString base = QUuid::createUuid().toString();
    base.replace("{","");
    base.replace("}","");
    base.replace("-","");
    return base;
  }


}
