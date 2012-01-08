#ifndef GAMESYSTEMAST_H
#define GAMESYSTEMAST_H

#include <QObject>
#include <QList>

#include "ast/Token.h"
#include "ast/RuleSource.h"
#include "ast/Character.h"


namespace gsdl {

  class GameSystem : public Token
  {
      Q_OBJECT
  public:
    explicit GameSystem(const QString name, QObject *parent = 0);
    void addRuleSource(const QString value);
    Character* getCharacter() {return this->character; }

  private:
    QString name;
    QList<RuleSource*> sources;
    Character *character;

  };

}

#endif // GAMESYSTEMAST_H
