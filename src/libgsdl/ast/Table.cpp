#include "Table.h"

namespace gsdl {

  Table::Table(const QString name, QObject *parent) : Token(parent), name(name)
  {
    this->currentItem = 0x0;
  }

  Item* Table::createItem(const QString name) {
    if(!this->itemExists(name)) {
      Item *i = new Item(name, this);
      this->items.append(i);
      this->currentItem = i;
      return i;
    }
    this->currentItem = this->getItem(name);
    return this->currentItem;
  }

  bool Table::itemExists(const QString name) {
    return this->getItem(name) != 0x0;
  }

  Item* Table::getItem(const QString name) {
    foreach(Item*item, this->items) {
      if(item->getName() == name) return item;
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
  }
  */
}
