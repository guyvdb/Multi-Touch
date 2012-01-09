#ifndef GOUP_H
#define GOUP_H

#include <QObject>
#include <QList>

#include "ast/Token.h"
#include "ast/Field.h"

namespace gsdl {

  class Character;


  class Group : public Token
  {
      Q_OBJECT
  public:
    explicit Group(const QString name,  QObject *parent = 0);
    QString getName() const {return this->name;}

    Field* createField(const QString name);
    bool fieldExists(const QString name);
    Field* getField(const QString name);
    Field* getCurrentField(){return this->currentField; }
  private:


    QString name;
    QList<Field*> fields;
    Character *character;
    Field *currentField;

  };

}

#endif // GOUP_H
