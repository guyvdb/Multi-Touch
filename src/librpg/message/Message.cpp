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
#include "Message.h"
#include "qjson/json_parser.hh"
#include "qjson/serializer.h"

namespace mtdnd {

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    Message::DataPacket Message::decode(QByteArray bytes) {
        QJson::Parser parser;
        DataPacket result;

        QVariantMap msg = parser.parse(bytes,&result.ok).toMap();
        if(result.ok) {
            result.data = msg.value("data").toMap();
            result.type = msg.value("type").toString();
            result.from = msg.value("from").toString();
        }
        return result;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    QByteArray Message::encode(QString from, QString type, QVariantMap message) {
        QJson::Serializer serializer;
        QVariantMap msg;
        msg.insert("type",type);
        msg.insert("data",message);
        msg.insert("from",from);
        return serializer.serialize(msg);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    QByteArray Message::encode(Message::DataPacket &packet) {
      return Message::encode(packet.from, packet.type, packet.data);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    QByteArray Message::encode(Message &message) {
      Message::DataPacket packet = message.getPacket();
      return Message::encode(packet.from, packet.type, packet.data);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    Message::Message(const QString type) {
      this->packet.type = type;
    }



    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void Message::set(const QString name, const int value) {
      this->packet.data[name] = value;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void Message::set(const QString name, const double value) {
      this->packet.data[name] = value;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void Message::set(const QString name, const bool value) {
      this->packet.data[name] = value;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void Message::set(const QString name, const QString value) {
      this->packet.data[name] = value;
    }

}
