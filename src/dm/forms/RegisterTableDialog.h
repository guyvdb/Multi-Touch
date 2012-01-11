#ifndef REGISTERTABLEDIALOG_H
#define REGISTERTABLEDIALOG_H

#include <QDialog>
#include "engine/GameEngine.h"

namespace Ui {
    class RegisterTableDialog;
}

class RegisterTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterTableDialog(rpg::GameEngine *engine);
    ~RegisterTableDialog();

private slots:
  void on_buttonBox_accepted();
  void on_buttonBox_rejected();
private:
    Ui::RegisterTableDialog *ui;
    rpg::GameEngine *engine;
};

#endif // REGISTERTABLEDIALOG_H
