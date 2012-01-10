#ifndef PARSERWINDOW_H
#define PARSERWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QWebView>


#include "widget/CharacterForm.h"
#include "ast/GameSystem.h"

namespace Ui {
    class ParserWindow;
}

class ParserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ParserWindow(QWidget *parent = 0);
    ~ParserWindow();
protected:
  void resizeEvent(QResizeEvent *);

private slots:
  void on_btnClose_clicked();
  void on_btnParse_clicked();
private:
    Ui::ParserWindow *ui;
    QPlainTextEdit *text;
    QPlainTextEdit *html;
    gsdl::GameSystem *system;
    character::CharacterForm *form;

};

#endif // PARSERWINDOW_H
