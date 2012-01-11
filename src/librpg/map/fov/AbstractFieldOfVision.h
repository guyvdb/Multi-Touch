#ifndef ABSTRACTFIELDOFVISION_H
#define ABSTRACTFIELDOFVISION_H

#include <QObject>
#include <QPoint>

#include "map/Matrix.h"

namespace rpg {


  class AbstractFieldOfVision : public QObject
  {
      Q_OBJECT
  public:
    AbstractFieldOfVision(Matrix *obsticals);
    ~AbstractFieldOfVision();

    virtual void addPointOfView(const int row, const int col, const int radius) = 0;
    virtual void addPointOfView(QPoint point, const int radius) = 0;
    void reset();
    Matrix *getMatrix() {return this->matrix; }


    void light(const int row, const int col);
    bool isBlocked(const int row, const int col);

  protected:
    Matrix *obsticals;
    Matrix *matrix;



  };

}

#endif // ABSTRACTFIELDOFVISION_H
