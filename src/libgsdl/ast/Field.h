#ifndef FIELD_H
#define FIELD_H

#include <QStringList>
#include "ast/Token.h"

namespace gsdl {
  class Group;

  class Field : public Token
  {
      Q_OBJECT
  public:
    explicit Field(const QString name, QObject *parent = 0);
    QString getLookupTableName() const {return this->lookupTableName; }
    void setLookupTableName(const QString value) {this->lookupTableName = value; }
    QString getValue() const {return this->value;}
    void setValue(const QString value) {this->value = value; }
    QString getName() const {return this->name; }
    void setHalfMacroFieldName(const QString value) {this->halfMacroFieldName = value;}
    QString getHalfMacroFieldName() const {return this->halfMacroFieldName; }
    void setModifierMacroFieldName(const QString value) {this->modifierMacroFieldName = value;}
    QString geModifierMacroFieldName() const {return this->modifierMacroFieldName; }
    void setModifierTableName(const QString value) {this->modifierTableName = value;}
    QString getModifierTableName() const {return this->modifierTableName; }
    Group* getGroup() {return this->group; }

    void appendAddMacroFactor(const QString value);


  private:
    void recalculateAddMacroFieldName();

    QString name;
    QString value;
    QString lookupTableName;
    QString halfMacroFieldName;
    QString modifierMacroFieldName;
    QString modifierTableName;
    Group* group;

    QStringList addMacroFactors;
  };

}
#endif // FIELD_H
