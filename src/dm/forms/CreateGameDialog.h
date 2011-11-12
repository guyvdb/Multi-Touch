#ifndef CREATEGAMEDIALOG_H
#define CREATEGAMEDIALOG_H

#include <QDialog>

namespace Ui {
    class CreateGameDialog;
}

class CreateGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateGameDialog(QWidget *parent = 0);
    ~CreateGameDialog();
    QString getFileName() const;

private:
    Ui::CreateGameDialog *ui;
};

#endif // CREATEGAMEDIALOG_H
