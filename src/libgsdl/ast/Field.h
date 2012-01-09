#ifndef FIELD_H
#define FIELD_H

#include "ast/Token.h"

namespace gsdl {
  class Group;

  class Field : public Token
  {
      Q_OBJECT
  public:
    explicit Field(const QString name, QObject *parent = 0);
    QString getLookupTableName() const {return this->lookupTableName; }
    void setLookupTableName(const QString name) {this->lookupTableName = value; }
    QString getValue() const {return this->value;}
    void setValue(const QString value) {this->value = value; }
    QString getName() const {return this->name; }
    void setHalfMacroFieldName(const QString value) {this->halfMacroFieldName = value;}
    QString getHalfMacroFieldName() const {return this->halfMacroFieldName; }
    Group* getGroup() {return this->group; }
  private:
    QString name;
    QString value;
    QString lookupTableName;
    QString halfMacroFieldName;
    Group* group;
  };

}
#endif // FIELD_H
