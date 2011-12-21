#include "Blob.h"

namespace mtv {

  Blob::Blob() :  QObject()
  {
    this->area = 0;
    this->length = 0;
    this->age = 0;
    this->sitting = 0;


    this->hole = false;
    this->simulated = false;
    this->object = false;

    //this->color = QColor(255,255,255);
  }

  Blob::~Blob() {
    foreach(QPoint *point, this->points) delete point;
  }

  void Blob::addPoint(const int x, const int y) {
    this->addPoint(new QPoint(x,y));
  }

  void Blob::addPoint(QPoint *point) {
    this->points.append(point);
  }


}
