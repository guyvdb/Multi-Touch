#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <QString>
#include <QUuid>

namespace mtdnd {
  class BaseModel
  {
  public:
    BaseModel(const QString id="");
    QString id;
  private:
    QString createIdentity();
  };
}

#endif // BASEMODEL_H
