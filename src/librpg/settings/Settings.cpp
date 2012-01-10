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
    void Settings::merge(QVariantMap &defaults) {

      foreach(QString key, defaults.keys()) {
        QVariant defval = defaults.value(key);

        if(!this->map.contains(key)) {
          this->map[key] = defval;
        } else {
          if(defval.canConvert<QVariantMap>()){
            this->mergeMaps(this->map.value(key),defval);
          }
        }
      }
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void Settings::mergeMaps(QVariant setting,  QVariant defaults) {
      // TODO implement map merging
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void Settings::set(const QString key, QVariant value) {
      this->map[key] = value;
    }

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
