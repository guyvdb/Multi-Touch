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

namespace MTG {

    class Message
    {
    public:

        typedef struct packet {
            bool ok;
            QString type;
            QVariantMap data;
        } packet_t;



        static Message::packet_t decode(QByteArray bytes);
        static QByteArray encode(QString type, QVariantMap message);

    };

}
#endif // MESSAGE_H
