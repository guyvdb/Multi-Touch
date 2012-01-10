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
#ifndef MESSAGE_H
#define MESSAGE_H

#include <QVariant>
#include <QVariantMap>

namespace mtdnd {

  class Message
  {
  public:

    typedef struct Packet {
      bool ok;
      QString type;
      QString from;
      QVariantMap data;
    } DataPacket;


    // Quick methods for sending message without construction a message
    static Message::DataPacket decode(QByteArray bytes);
    static QByteArray encode(QString from, QString type, QVariantMap message);
    static QByteArray encode(Message::DataPacket &packet);
    static QByteArray encode(mtdnd::Message &message);



    Message(const QString type);
    void set(const QString name, const int value);
    void set(const QString name, const double value);
    void set(const QString name, const bool value);
    void set(const QString name, const QString value);

    void setFrom(const QString value) {this->packet.from = value; }

    Message::DataPacket getPacket() {return this->packet; }

  private:
    Message::DataPacket packet;


  };

}
#endif // MESSAGE_H
