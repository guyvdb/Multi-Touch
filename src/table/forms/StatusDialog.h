#ifndef DISCOVERYDIALOG_H
#define DISCOVERYDIALOG_H

#include <QDialog>

namespace Ui {
    class StatusDialog;
}

class StatusDialog : public QDialog
{
    Q_OBJECT

public:
    StatusDialog(QWidget *parent = 0);
    ~StatusDialog();

  void setStatus(const QString msg);

private:
    Ui::StatusDialog *ui;
};

#endif // DISCOVERYDIALOG_H
