#ifndef BUTTON_H
#define BUTTON_H

#include "widget/BaseWidget.h"

class Button : public BaseWidget
{
    Q_OBJECT
public:
    explicit Button(QGraphicsItem * parent = 0, Qt::WindowFlags wFlags = 0);

signals:

public slots:

};

#endif // BUTTON_H
