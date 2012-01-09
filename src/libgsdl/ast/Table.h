/* -------------------------------------------------------------------------------------------
 *                                   M U L T I - T O U C H
 *  -------------------------------------------------------------------------------------------
 *                             Copyright 2011, 2012 Guy van den Berg
 *                                      All Rights Reserved
 *
 *          This program is free software; you can redistribute it and/or modify it
 *          under the terms of the GNU General Public License as published by the Free
 *          Software Foundation; either version 2 of the License, or (at your option)
 *          any later version.
 *
 *          This program is distributed in the hope that it will be useful, but WITHOUT
 *          ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *          FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *          more details.
 *
 *          You should have received a copy of the GNU General Public License along with
 *          this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * ------------------------------------------------------------------------------------------- */
#ifndef TABLE_H
#define TABLE_H

#include "libgsdl_global.h"

#include "ast/Token.h"
#include "ast/Item.h"

namespace gsdl {

  class LIBGSDL_EXPORT Table : public Token
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

    QByteArray dump(const QString indent);
  private:
    QString name;
    QString foreignKeyFieldName;
    QList<Item*> items;
    Item *currentItem;

  };

}

#endif // TABLE_H
