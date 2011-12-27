#ifndef UDPWINDOW_H
#define UDPWINDOW_H

#include <QMainWindow>

namespace Ui {
    class UdpWindow;
}

class UdpWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UdpWindow(QWidget *parent = 0);
    ~UdpWindow();

private slots:
  void on_btnClose_clicked();

  void on_btnSend_clicked();

private:
    Ui::UdpWindow *ui;
};

#endif // UDPWINDOW_H
