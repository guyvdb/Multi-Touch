#ifndef FRAME_H
#define FRAME_H

#include "widget/BaseWidget.h"

class Frame : public BaseWidget
{
    Q_OBJECT
public:  
    explicit Frame(const QString caption, QGraphicsItem * parent = 0);
protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
  QString caption;
signals:

public slots:

};

#endif // FRAME_H
