#include "ast/Field.h"
#include "ast/Group.h"

namespace gsdl {

  Field::Field(const QString name, QObject *parent) : Token(parent), name(name)
  {
    this->group = qobject_cast<Group*>(parent);
  }

}
