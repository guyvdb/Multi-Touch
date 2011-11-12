#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "Settings.h"
#include "qjson/json_parser.hh"
#include "qjson/serializer.h"

namespace MT {

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
