#ifndef GAMESYSTEMAST_H
#define GAMESYSTEMAST_H

#include <QObject>
#include <QList>
#include <QMap>

#include "libgsdl_global.h"

#include "ast/Token.h"
#include "ast/RuleSource.h"
#include "ast/Character.h"
#include "ast/Table.h"


namespace gsdl {

  class LIBGSDL_EXPORT GameSystem : public Token
  {
      Q_OBJECT
  public:
    explicit GameSystem(const QString name, QObject *parent = 0);
    RuleSource* createRuleSource(const QString value);


    Table* createTable(const QString value);
    bool tableExists(const QString name);
    Table* getTable(const QString name);
    Table* getCurrentTable(){return this->currentTable; }

    Character* getCharacter() {return this->character; }
    void setName(const QString value) {this->name = value; }
    QString getName() const {return this->name; }

    void addGuiMapping(const QString key, const QString value) {this->guiMappings[key] = value; }

  private:
    QString name;
    QList<RuleSource*> sources;
    Character *character;
    QList<Table*> tables;
    Table* currentTable;
    QMap<QString, QString> guiMappings;


  };

}

#endif // GAMESYSTEMAST_H
