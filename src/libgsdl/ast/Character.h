#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QList>
#include "ast/Token.h"
#include "ast/Group.h"
#include "ast/Field.h"


namespace gsdl {

  class GameSystem;

  class Character : public Token
  {
      Q_OBJECT
  public:
    explicit Character(QObject *parent = 0);
    Group* createGroup(const QString name);

    bool groupExists(const QString name);
    Group *getGroup(const QString name);

    bool fieldExists(const QString name);
    Field* getField(const QString name);

    void addFieldRef(Field *field);

    Group* getCurrentGroup() {return this->currentGroup; }

  private:

    GameSystem *gameSystem;
    QList<Group*> groups;
    QList<Field*> fields;
    Group* currentGroup;


  };

}

#endif // CHARACTER_H
