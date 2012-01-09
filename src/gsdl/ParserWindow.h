#ifndef PARSERWINDOW_H
#define PARSERWINDOW_H

#include <QMainWindow>

namespace Ui {
    class ParserWindow;
}

class ParserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ParserWindow(QWidget *parent = 0);
    ~ParserWindow();

private slots:
  void on_btnClose_clicked();

  void on_btnParse_clicked();

private:
    Ui::ParserWindow *ui;
};

#endif // PARSERWINDOW_H
