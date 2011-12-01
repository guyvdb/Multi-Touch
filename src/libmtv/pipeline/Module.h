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
        CAPNONE     = 0x00000000,
        CAPINPUT    = 0x00000001,
        CAPOUTPUT   = 0x00000002,
        CAPGUI      = 0x00000004
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
