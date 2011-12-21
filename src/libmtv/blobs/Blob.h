#ifndef BLOB_H
#define BLOB_H

#include <QObject>
#include <QList>
#include <QPoint>
//#include <QColor>


namespace mtv {

  class Blob : public QObject
  {
      Q_OBJECT
  public:
      Blob();
      ~Blob();

      QList<QPoint*>* getPoints() {return &this->points; }

      void addPoint(QPoint* point);
      void addPoint(const int x, const int y);

      void setId(const int value) {this->id = value; }
      int getId() {return this->id; }


  private:
      QList<QPoint*> points;
      int id;
      float area;
      float length;
      float angle;
      float acceleration;
      float sitting;
      float age;

      bool object;
      bool simulated;
      bool hole;

      //QColor color;


  signals:

  public slots:

  };

}

#endif // BLOB_H
