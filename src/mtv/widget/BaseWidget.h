#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QGraphicsWidget>

class BaseWidget : public QGraphicsWidget
{
    Q_OBJECT
public:
    explicit BaseWidget(QGraphicsItem * parent = 0, Qt::WindowFlags wFlags = 0);

signals:

public slots:

};

#endif // BASEWIDGET_H
