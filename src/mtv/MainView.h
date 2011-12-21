#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QtGui/QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDesktopWidget>


class MainView : public QMainWindow
{
    Q_OBJECT

public:
    MainView(QWidget *parent = 0);
    ~MainView();
protected:
    virtual void resizeEvent(QResizeEvent *e);
private:

    void switchDisplay(const int screen, bool fullscreen = true);


    QGraphicsView *view;
    QGraphicsScene *scene;
    QDesktopWidget *desktop;
};

#endif // MAINVIEW_H
