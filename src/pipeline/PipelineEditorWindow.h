#ifndef PIPELINEEDITORWINDOW_H
#define PIPELINEEDITORWINDOW_H

#include <QMainWindow>

namespace Ui {
    class PipelineEditorWindow;
}

class PipelineEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PipelineEditorWindow(QWidget *parent = 0);
    ~PipelineEditorWindow();

private:
    Ui::PipelineEditorWindow *ui;
};

#endif // PIPELINEEDITORWINDOW_H
