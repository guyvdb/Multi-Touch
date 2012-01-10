#ifndef BRIDGE_H
#define BRIDGE_H

#include <QObject>

namespace character {

  class Bridge : public QObject
  {
      Q_OBJECT
  public:
      explicit Bridge(QObject *parent = 0);
  signals:

  public slots:
    void fieldChanged(const QString name);

  };

}

#endif // BRIDGE_H
