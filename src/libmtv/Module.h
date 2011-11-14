/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */

/*

  Module is the base class of all modules. A module has a capabilities flag. Possiable capabilities are:

    * NONE
    * INPUT
    * OUTPUT
    * GUI

 The output of the module is "named". For instance a CameraModule might output a "raw" frame. A ConvertToGrayScale module
 might require a "raw" frame and output a "grayscale" frame. A BackgroundMask might require "raw" frame
 and output a "mask" frame and an ExtractForeground module might take a "grayscale" and "mask" frame
 to generate a "foreground" frame.

 A module must never modify the input frame as this same frame could be the input of another module.

 A module generates a frame event when it has finished processing a frame. A module can queue its output or just discard
 the oldest frame and replace it with the newest. The module implement a thread safe methods of getNextFrame() which will
 be the current frame or a LIFO or FIFO frame depending on how the module is implemented.

 modules shall implement a chaining interface such as:

    convertToGrayScale.connectTo(cameraModule).as("raw")
    backgroundMask.connectTo(cameraModule)
    extractForeground.connectTo(backgoundMask).as("mask")
    extractForeground.connectTo(convertToGrayScale).as("grayscale")

 The first module is connected to a Pipeline object to provide threading for the execution of tasks.

 A module shall implement a run() method where its logic will be executed from within a thread of the pipelines thread pool.
 the run method should block if the module is threaded, otherwise, run() should return immidiatley and processing should
 occure after the module has received sufficient frame() events to allow it to process and generate its own frame event.

 Modules implement named settings, which are implemented as QVariants. This includes lists and maps. These named settings
 should all be set to reasonable defaults on module construction. The user should not have to make any changes to the settings
 for the module to operate reasonable well.

 All settings of a module should have descriptions set on module construction. If the setting is a map, the description value
 should be a map of descriptions. See the Setting object for more details.

 The module should indicate if it should be run in the "main" thread of the pipeline, or if it should be placed on its own
 thread. This should come from a configuration file.





 */


#ifndef MODULE_H
#define MODULE_H

#include <QObject>
#include <QHash>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>

#include <opencv2/core/core.hpp>

#include "libmtv_global.h"
#include "Setting.h"


namespace mtv {


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


      Module(int capabilities);
      ~Module();

      /* must be overridden by implementing classes */
      virtual void hello() = 0;
      virtual QString name() const = 0;
      virtual void frame(Module *module, const QString &name) = 0;

      /* capabilities */
      bool isCapable(int flag);
      bool isInputOnly();
      bool isOutputOnly();

      /* settings */
      QVariant getSetting(const QString name);
      void setSetting(const QString name, QVariant value);
      QVariant getSettingDescription(const QString name);
      void setSettingDescription(const QString name, QVariant value);
      bool hasSetting(const QString name);

      /* chaining */
      bool chain(Module* module);
      bool unchain(Module *module);




  private:
      QHash<QString, QVariant> settings;
      QHash<QString, QVariant> settingDescriptions;
      int capabilities;
  signals:
      void sendFrameReady(Module* module, const QString &name);

  private slots:
      void frameReady(Module* module, const QString &name);

  };


}

#endif // MODULE_H
