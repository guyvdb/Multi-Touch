#ifndef ADDMODULEDIALOG_H
#define ADDMODULEDIALOG_H

#include <QDialog>

namespace Ui {
    class AddModuleDialog;
}

class AddModuleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddModuleDialog(QWidget *parent = 0);
    ~AddModuleDialog();

private:
    Ui::AddModuleDialog *ui;
};

#endif // ADDMODULEDIALOG_H
