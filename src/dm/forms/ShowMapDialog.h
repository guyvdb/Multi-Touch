#ifndef SHOWMAPDIALOG_H
#define SHOWMAPDIALOG_H

#include <QDialog>

namespace Ui {
    class ShowMapDialog;
}

class ShowMapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowMapDialog(QWidget *parent = 0);
    ~ShowMapDialog();

private:
    Ui::ShowMapDialog *ui;
};

#endif // SHOWMAPDIALOG_H
