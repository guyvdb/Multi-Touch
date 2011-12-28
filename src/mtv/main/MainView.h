/* -------------------------------------------------------------------------------------------
 *                                   M U L T I - T O U C H
 *  -------------------------------------------------------------------------------------------
 *                             Copyright 2011, 2012 Guy van den Berg
 *                                      All Rights Reserved
 *
 *          This program is free software; you can redistribute it and/or modify it
 *          under the terms of the GNU General Public License as published by the Free
 *          Software Foundation; either version 2 of the License, or (at your option)
 *          any later version.
 *
 *          This program is distributed in the hope that it will be useful, but WITHOUT
 *          ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *          FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *          more details.
 *
 *          You should have received a copy of the GNU General Public License along with
 *          this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * ------------------------------------------------------------------------------------------- */
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
