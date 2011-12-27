/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
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



        static Message::DataPacket decode(QByteArray bytes);
        static QByteArray encode(QString from, QString type, QVariantMap message);

    };

}
#endif // MESSAGE_H
