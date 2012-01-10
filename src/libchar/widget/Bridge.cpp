#include "Bridge.h"
#include <QDebug>

namespace character {

  Bridge::Bridge(QObject *parent) : QObject(parent)
  {
  }

  void Bridge::fieldChanged(const QString name) {
    qDebug() << "FIELD CHANGE: " << name;
  }
}
