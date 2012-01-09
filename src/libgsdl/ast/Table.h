#ifndef TABLE_H
#define TABLE_H

#include "ast/Token.h"
#include "ast/Item.h"

namespace gsdl {

  class Table : public Token
  {
      Q_OBJECT
  public:
    explicit Table(const QString name, QObject *parent = 0);
    QString getName() const {return this->name; }

    void setForeignKeyFieldName(const QString value) {this->foreignKeyFieldName = value;}
    QString getForeignKeyFieldName() const {return this->foreignKeyFieldName; }

    Item* createItem(const QString name);
    bool itemExists(const QString name);
    Item* getItem(const QString name);
    Item* getCurrentItem(){return this->currentItem; }

  private:
    QString name;
    QString foreignKeyFieldName;
    QList<Item*> items;
    Item *currentItem;

  };

}

#endif // TABLE_H
