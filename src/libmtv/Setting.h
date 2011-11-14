/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */

/*
  A setting is a variable used in a module that is adjustable by some external code.

 */

#ifndef SETTING_H
#define SETTING_H

#include<QVariant>
#include <QObject>
#include <QString>
#include <QList>

namespace mtv {

  class FrameMatrixInfo {

  };


  class Setting : public QObject
  {
    Q_OBJECT
  public:
      enum SETTING_DATATYPE {
        SETTING_NONE,
        SETTING_BOOL,
        SETTING_STRING,
        SETTING_DOUBLE,
        SETTING_POINTLIST,
        SETTING_FRAME
      };

      Setting(const QString name, const QString value);
      Setting(const QString name, int value);
      Setting(const QString  name, bool value);
      Setting(const QString name, double value);
      ~Setting();

      void setValue(QVariant value);
      QVariant getValue();



      SETTING_DATATYPE getDataType();
      void setDataType(SETTING_DATATYPE type);

      void setReadOnly(bool value);
      bool isReadOnly();

      void setIsFrameMatrix(bool value);
      bool isFrameMatrix();

      void setFrameMatrixInfo(mtv::FrameMatrixInfo info);
      mtv::FrameMatrixInfo getFrameMatrixInfo;


      bool haveMin();
      bool haveMax();
      int getMin();
      void setMin(int value);
      int getMax();
      void setMax(int value);


  signals:
      void changed(Setting &setting);

  private:
      QVariant value;

  };

}

#endif // SETTING_H
