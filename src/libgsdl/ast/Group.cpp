#include "ast/Group.h"
#include "ast/Character.h"

namespace gsdl {

  Group::Group(const QString name, QObject *parent) : Token(parent), name(name)
  {
    this->character = qobject_cast<Character*>(parent);
    this->currentField = 0x0;
  }

  Field* Group::createField(const QString name) {
    if(!fieldExists(name)) {
      this->fields.append(new Field(name, this));
    }
    return this->getField(name);
  }

  bool Group::fieldExists(const QString name) {
    return this->getField(name) != 0x0;
  }

  Field* Group::getField(const QString name) {
    foreach(Field  *field, this->fields) {
      if(field->getName() == name) return field;
    }
    return 0x0;
  }

}
