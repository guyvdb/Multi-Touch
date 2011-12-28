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
#ifndef BLOBFINDERMODULE_H
#define BLOBFINDERMODULE_H

#include "pipeline/Module.h"
#include "libmtv_global.h"


namespace mtv {


/*

  class LIBMTV_EXPORT BlobFinderModule : public Module
  {
    Q_OBJECT
  public:
    BlobFinderModule();

    //
    virtual int capabilities() const;

    //
    virtual void start();
    virtual void stop();

    virtual QString getModuleName() {return "blob-finder";}

  protected:

    // tick
    virtual void tick() {}

  protected slots:
    virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);

  private:


  };


  class BlobFinderModuleFactory : public ModuleFactory {
  public:
    virtual Module* createInstance() {return qobject_cast<Module*>(new BlobFinderModule()); }
  };
*/

}

#endif // BLOBFINDERMODULE_H
