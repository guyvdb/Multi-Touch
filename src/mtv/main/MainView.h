#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QtGui/QMainWindow>
//#include <QGraphicsView>
//#include <QGraphicsScene>
#include <QDesktopWidget>
#include <QList>


#include "widget/View.h"
#include "widget/Scene.h"

#include "widget/Frame.h"


class MainView : public QMainWindow
{
    Q_OBJECT

public:
    MainView(QWidget *parent = 0);
    ~MainView();

private:


    View *view;
    Scene *scene;
    QDesktopWidget *desktop;


    Frame *systemFrame;
    Frame *videoFrame;





};





#endif // MAINVIEW_H
