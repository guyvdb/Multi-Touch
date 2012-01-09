#include "GameSystem.h"

namespace gsdl {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  GameSystem::GameSystem(const QString name, QObject *parent) : Token(parent), name(name)
  {
    this->character = new Character(this);
    this->currentTable = 0x0;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  RuleSource * GameSystem::createRuleSource(const QString value) {
    RuleSource *source = new RuleSource(value, this);
    this->sources.append(source);
    return source;
  }

  Table* GameSystem::createTable(const QString value) {
    if(!this->tableExists(value)) {
      Table* t = new Table(value,this);
      this->tables.append(t);
      this->currentTable = t;
      return t;
    }
    this->currentTable = this->getTable(value);
    return this->currentTable;
  }

  bool GameSystem::tableExists(const QString name) {
    return this->getTable(name) != 0x0;
  }

  Table* GameSystem::getTable(const QString name) {
    foreach(Table* table, this->tables) {
      if(table->getName() == name) return table;
    }
    return 0x0;
  }


  /*
  Field* Group::createField(const QString name) {
    if(!fieldExists(name)) {
      Field *f = new Field(name, this);
      this->fields.append(f);
      this->character->addFieldRef(f);
      this->currentField = f;
      return f;
    }
    this->currentField = this->getField(name);
    return this->currentField;
  }

  bool Group::fieldExists(const QString name) {
    return this->getField(name) != 0x0;
  }

  Field* Group::getField(const QString name) {
    foreach(Field  *field, this->fields) {
      if(field->getName() == name) return field;
    }
    return 0x0;
  }*/


}
