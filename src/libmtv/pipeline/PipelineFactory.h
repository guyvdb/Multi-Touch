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
#ifndef FACTORY_H
#define FACTORY_H

#include <QMetaObject>
#include <QObject>
#include <QHash>
#include <QString>
#include <QList>
#include "Module.h"
#include "libmtv_global.h"

namespace mtv {


    class /*LIBMTV_EXPORT*/ PipelineFactory : public QObject
    {
        Q_OBJECT
    public:
      ~PipelineFactory();
      PipelineFactory();
      QStringList listModules();
      Module* createInstance(const QString moduleName, const QString instanceName);
      QString getLastError() const;
    private:
      void defineModules();
      void define(const QString name, ModuleFactory *factory);
      QHash<QString,  ModuleFactory *> modules;
      QString lastError;
    };





}

#endif // FACTORY_H
