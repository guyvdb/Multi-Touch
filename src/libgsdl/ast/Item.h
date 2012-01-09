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
#ifndef ITEM_H
#define ITEM_H

#include <QStringList>
#include "libgsdl_global.h"
#include "ast/Token.h"

namespace gsdl {

  class LIBGSDL_EXPORT Item : public Token
  {
      Q_OBJECT
  public:
    explicit Item(const QString name, QObject *parent = 0);
    QString getName() const {return this->name;}
    void setValue(const QString value) {this->value = value; }
    QString getValue() const {return this->value; }    
    void addInfo(const QString value){ this->info.append(value); }

    QByteArray dump(const QString indent);
  private:
    QString name;
    QString value;
    QStringList info;


  };

}

#endif // ITEM_H
