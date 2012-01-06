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


#ifndef MODULE_H
#define MODULE_H

#include <QObject>
#include <QHash>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>
#include <QTimer>




#include <opencv2/core/core.hpp>

#include "libmtv_global.h"
#include "ModuleError.h"
#include "Setting.h"


namespace mtv {

  typedef std::vector < cv::Point > PointsList;
  typedef std::vector < PointsList > ListOfPointsList;

  class Pipeline;

  class LIBMTV_EXPORT Module : public QObject
  {
      Q_OBJECT
  public:

      enum CapabilityFlags {
        CapabilityNone                        = 0x00000000,
        CapabilityGui                         = 0x00000001, // can set parameters via the gui
        CapabilityInputFrame                  = 0x00000002, // accepts video frames as input
        CapabilityOutputFrame                 = 0x00000004, // produces video frames as output
        CapabilityInputListOfPointsList       = 0x00000008, // accepts a vector of vector points as input  - std::vector< std::vector< cv::Point > >
        CapabilityOutputListOfPontsList       = 0x00000010  // produces a vector of vector points as output - std::vector< std::vector< cv::Point > >
      };

      enum OutputFlags {
        OutputNone                            = 0x00000000, // nothing generated from our process call
        OutputPrimaryFrame                    = 0x00000001, // a frame has been generated
        OutputSecondaryFrame                  = 0x00000002,
        OutputListOfPointsList                = 0x00000004  // a points list has been generated
      };


      Module();
      ~Module();

      /* capabilities of this module */
      virtual int capabilities() const = 0;

      /* start and stop this module */
      virtual void start() = 0;
      virtual void stop() = 0;
      virtual void pause() = 0;
      virtual void resume() = 0;

      /* settings */
      Setting *setting(const QString name);
      void listSettings(QList<Setting*> &result);

      /* module name */
      virtual QString getModuleName() = 0;

      /* capabilities */
      bool isCapable(int flag);

      /* instance name  */
      QString getInstanceName() {return this->instanceName; }
      void setInstanceName(const QString value) {this->instanceName = value; }

      /* errors */
      void addError(const QString propname, const QString message);
      void addError(const QString message);
      void clearErrors();
      QList<ModuleError*> getErrors() {return this->errors;}
      QString getLastError() {return this->lastError; }

      /* ordinal position for displaying in the pipeline editor */
      void setOrdinal(int value) {this->ordinal = value;}
      int getOrdinal() {return this->ordinal; }

      /* eventing of settings */
      void hookFrameHandler(Module *source);
      void unhookFrameHandler(Module *source);

      QHash<QString, mtv::Setting*>* getSettings() {return &this->settings; }

  protected:
      void save(const QString filename, cv::Mat &frame);
  private:
      QHash<QString, mtv::Setting*> settings;
      QString instanceName;
      QList<ModuleError*> errors;
      QString lastError;
      int ordinal;
  signals:
      void frameReady(mtv::Module* module, const QString name, cv::Mat &matrix);
  protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix) = 0;
      virtual void tick() = 0;
  };


  class ModuleFactory {
  public:
    virtual Module* createInstance() = 0;
  };



}

#endif // MODULE_H
