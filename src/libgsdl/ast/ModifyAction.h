#ifndef MODIFYACTION_H
#define MODIFYACTION_H

#include <QObject>


namespace gsdl {
  class ModifyAction
  {
  public:
    enum ActionType {
      IncrementAction
    };


    ModifyAction(QString target, ActionType type, QObject *parent = 0);
    QString target;
    QString param;
    ActionType type;
  };

}

#endif // MODIFYACTION_H
