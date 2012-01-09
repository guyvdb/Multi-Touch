#include "ast/Field.h"
#include "ast/Group.h"

namespace gsdl {

  Field::Field(const QString name, QObject *parent) : Token(parent), name(name)
  {
    this->group = qobject_cast<Group*>(parent);
  }

  void Field::appendAddMacroFactor(const QString value) {
    this->addMacroFactors.append(value);
    this->recalculateAddMacroFieldName();
  }

  void Field::recalculateAddMacroFieldName() {
    QString n = "";

    if(this->addMacroFactors.length() > 0) {
      n.append(this->addMacroFactors.at(0));
      n.append(" plus ");
    }

    if(this->addMacroFactors.length() > 1) {
      n.append(this->addMacroFactors.at(1));
    }

    this->name = n;
  }

}
