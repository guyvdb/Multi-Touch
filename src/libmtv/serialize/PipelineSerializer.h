#ifndef PIPELINESERIALIZER_H
#define PIPELINESERIALIZER_H

#include <QObject>
#include <QXmlStreamReader>

#include "libmtv_global.h"

#include "pipeline/Module.h"

namespace mtv {

  class LateBind : public QObject {
    Q_OBJECT
  public:
    LateBind(Setting * setting, const QString instanceName, const QString frameName);

    Setting *getSetting() {return this->setting;}
    QString getInstanceName() {return this->instanceName;}
    QString getFrameName() {return this->frameName;}

  private:
    Setting *setting;
    QString instanceName;
    QString frameName;
  };

  class LIBMTV_EXPORT PipelineSerializer : public QObject
  {
      Q_OBJECT
  public:
      PipelineSerializer();

      bool loadPipeline(QString filename, QStringList &errors);
      bool loadPipeline(QByteArray &bytes, QStringList &errors);

      bool savePipeline(QString filename);
      bool savePipeline(QByteArray &bytes);

  private:
      Module *createModule(QXmlStreamReader *xml, QStringList &errors);
      void addSetting(QXmlStreamReader *xml, Module* module, QStringList &errors);


      void addBooleanSetting(const QString name, const QString value, Module* module, QStringList &errors);
      void addStringSetting(const QString name, const QString value, Module* module, QStringList &errors);
      void addIntegerSetting(const QString name, const QString value, Module* module, QStringList &errors);
      void addDoubleSetting(const QString name, const QString value, Module* module, QStringList &errors);
      void addPointListSetting(const QString name, const QString value, Module* module, QStringList &errors);
      void addFrameSetting(const QString name, const QString value, Module* module, QStringList &errors);

      void preformLateBinds(QStringList &errors);
      void clearLateBindings();
      QList<LateBind*> lateBindings;


  };

}

#endif // PIPELINESERIALIZER_H
