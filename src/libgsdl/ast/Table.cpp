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
#include "Table.h"

namespace gsdl {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Table::Table(const QString name, QObject *parent) : Token(parent), name(name)
  {
    this->currentItem = 0x0;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
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

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool Table::itemExists(const QString name) {
    return this->getItem(name) != 0x0;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Item* Table::getItem(const QString name) {
    foreach(Item*item, this->items) {
      if(item->getName() == name) return item;
    }
    return 0x0;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QByteArray Table::dump(const QString indent) {
    QByteArray result;
    result.append(indent).append("-- Table ").append(this->name).append(" --").append("\r\n");
    foreach(Item* item,this->items) result.append(item->dump(indent + "  "));
    return result;
  }

}
