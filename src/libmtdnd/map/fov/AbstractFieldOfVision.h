#ifndef ABSTRACTFIELDOFVISION_H
#define ABSTRACTFIELDOFVISION_H

#include <QObject>

#include "map/Matrix.h"

class AbstractFieldOfVision : public QObject
{
    Q_OBJECT
public:
    AbstractFieldOfVision(Matrix *obsticals);

signals:

public slots:

};

#endif // ABSTRACTFIELDOFVISION_H
