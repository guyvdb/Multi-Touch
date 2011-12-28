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
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "Settings.h"
#include "qjson/json_parser.hh"
#include "qjson/serializer.h"

namespace mtdnd {

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    Settings::Settings(const QString filename, QObject *parent) : QObject(parent), filename(filename)
    {

    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    bool Settings::load() {
        if(QFile::exists(this->filename)) {
            QJson::Parser parser;
            QFile file(this->filename);
            bool ok;

            if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
            this->map = parser.parse(&file,&ok).toMap();
            file.close();
            return ok;
        } else {
            return false;
        }
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    bool Settings::save() {
        QJson::Serializer serializer;
        QByteArray json = serializer.serialize(this->map);

        if(QFile::exists(this->filename)) QFile::remove(this->filename);

        QFile file(this->filename);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
        QTextStream out(&file);

        out << json;
        file.close();
        return true;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void Settings::merge(QVariantMap *defaults) {

        //defaults->insert()

        //this->recursiveMerge(defaults,this->getMap());
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    //void Settings::recursiveMerge(QVariant *source, QVariant *dest) {
        /*
        QVariantMap::Iterator i;

        for(i=source->begin(); i!=source->end();i++){
           QVariant key = i.key();
           QVariant value = i.value();


           if(value.type() == QVariant::Map) {
               qDebug() << key << " is a map";
               if(!dest->contains(key.toString())) {
                   qDebug() << "DEST DOES NOT CONTAIN KEY";
                   QVariantMap child;
                   dest->insert(key.toString(), child);
               }

               QVariant sourceChild = source->value(key.toString());
               QVariant destChild = dest->value(key.toString());

               this->recursiveMerge(&sourceChild, &destChild);


           } else {

           }


           qDebug() << "key: " << key << " : value : " << value;
           qDebug() << "KEYTYPE: " << key.type();
           qDebug() << "VALUETYPE: " << value.type();

        }*/
    //}

    //key:  QVariant(QString, "files")  : value :  QVariant(QVariantMap, QMap(("foo", QVariant(QString, "Bar") ) )  )

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    QVariantMap *Settings::getMap() {
        return &this->map;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void Settings::dump() {
        qDebug() << this->map;
    }

}
