/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
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

  class Pipeline;

  class LIBMTV_EXPORT Module : public QObject
  {
      Q_OBJECT
  public:

      enum {
        CAP_NONE              = 0x00000000,
        CAP_GUI               = 0x00000001, // can set parameters via the gui
        CAP_INPUT_FRAME       = 0x00000002, // accepts video frames as input
        CAP_OUTPUT_FRAME      = 0x00000004, // produces video frames as output
        CAP_INPUT_POINTS      = 0x00000008, // accepts a vector of vector points as input  - std::vector< std::vector< cv::Point > >
        CAP_OUTPUT_POINTS     = 0x00000010  // produces a vector of vector points as output - std::vector< std::vector< cv::Point > >


      };


      Module();
      ~Module();

      /* capabilities of this module */
      virtual int capabilities() const = 0;

      /* start and stop this module */
      virtual void start() = 0;
      virtual void stop() = 0;

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

      /* pipline */
      void setPipeline(Pipeline *pipeline) {this->pipeline = pipeline; }

      /* errors */
      void addError(const QString propname, const QString message);
      void addError(const QString message);
      void clearErrors();
      QList<ModuleError*> getErrors() {return this->errors;}
      QString getLastError() {return this->lastError; }

      /* ordinal position for displaying in the pipeline editor */
      void setOrdinal(int value) {this->ordinal = value;}
      int getOrdinal() {return this->ordinal; }

  protected:
      /* tick */
      virtual void tick() = 0;
      void startTicking(int frequency);
      void stopTicking();

      /* debug method */
      void dump(const QString name, cv::Mat &matrix);

      /* Image Convertion */
      //TODO test and convert color spaces
      //void convert(cv::Mat &source, cv::Mat & dest);

  private:
      QHash<QString, Setting*> settings;
      QString instanceName;
      Pipeline *pipeline;
      QList<ModuleError*> errors;
      QString lastError;
      QTimer *timer;
      int ordinal;
  signals:
      void frameReady(mtv::Module* module, const QString name, cv::Mat &matrix);
  protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix) = 0;

  private slots:
      void OnTimerTimedOut();
  };


  class ModuleFactory {
  public:
    virtual Module* createInstance() = 0;
  };



}

#endif // MODULE_H
