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
#ifndef MAP_H
#define MAP_H

#include "qdjango/QDjangoModel.h"
#include "libmtg_global.h"

namespace mtdnd {

  class LIBMTDND_EXPORT Map : public QDjangoModel
  {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString file READ file WRITE setFile)

  public:
    Map();
    QString name() const {return this->m_name;}
    void setName(const QString value) {this->m_name = value;}
    QString file() const {return this->m_file;}
    void setFile(const QString value) {this->m_file = value;}

  private:
    QString m_name;
    QString m_file;
  };

}
#endif // MAP_H
