#ifndef PIPELINEEDITORWINDOW_H
#define PIPELINEEDITORWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>


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

private:
    Ui::PipelineEditorWindow *ui;
    QGraphicsView *videoView;
    QGraphicsScene *videoScene;
    VideoGrid *grid;

    QHash<QString, VideoWidget*> widgets;
    QStringList widgetOrder;

    //void setFrame(QLabel *label, const QString name,  cv::Mat &matrix);
    void layoutVideoWidgets();

};

#endif // PIPELINEEDITORWINDOW_H
