#ifndef PIPELINEEDITORWINDOW_H
#define PIPELINEEDITORWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QImage>

#include "pipeline/Module.h"
#include <opencv2/opencv.hpp>

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
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();

  void OnFrameReady(mtv::Module *module, const QString name, cv::Mat &matrix); 
private:
    Ui::PipelineEditorWindow *ui;

    void setFrame(QLabel *label, const QString name,  cv::Mat &matrix);
    QImage MatToQImage(const cv::Mat &matrix);

};

#endif // PIPELINEEDITORWINDOW_H
