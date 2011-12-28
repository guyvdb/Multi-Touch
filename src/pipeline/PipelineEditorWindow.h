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
#ifndef PIPELINEEDITORWINDOW_H
#define PIPELINEEDITORWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMenu>
#include <QAction>

#include "pipeline/Module.h"
#include <opencv2/opencv.hpp>

#include "VideoGrid.h"
#include "VideoWidget.h"

namespace Ui {
    class PipelineEditorWindow;
}

class PipelineEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PipelineEditorWindow(QWidget *parent = 0);
    ~PipelineEditorWindow();

protected:
    virtual void resizeEvent(QResizeEvent *e);

private slots:

  void OnShowContextMenu(const QPoint &point);
  void on_actionLoad_triggered();
  void on_btnShowAllModules_clicked();
  void on_btnHideAllModules_clicked();

  void on_btnPipelineStart_clicked();

  void on_btnPipelineStop_clicked();

  void onSettingsWindowClosed(int value);
  void on_btnPause_clicked();


private:

    enum {
      NameAction,
      ViewAction,
      RemoveAction,
      SettingsAction
    };

    Ui::PipelineEditorWindow *ui;
    QGraphicsView *videoView;
    QGraphicsScene *videoScene;
    VideoGrid *grid;

    QHash<QString, VideoWidget*> widgets;
    QStringList widgetOrder;

    //void setFrame(QLabel *label, const QString name,  cv::Mat &matrix);
    void layoutVideoWidgets();
    void removeAllVideoWidgets();

    QAction* AddAction(const QString lable, int id, QMenu &menu);

};

#endif // PIPELINEEDITORWINDOW_H
