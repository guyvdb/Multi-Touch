/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */
#include "Message.h"
#include "qjson/json_parser.hh"
#include "qjson/serializer.h"

namespace mtg {

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

}
