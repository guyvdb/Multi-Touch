#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H


#include <QGraphicsWidget>
#include <QPixmap>
#include <QImage>

#include "pipeline/Module.h"

class VideoWidget : public QGraphicsWidget
{
    Q_OBJECT
public:
   VideoWidget(mtv::Module *module);
   ~VideoWidget();

   QString getModuleInstanceName();
protected:
   virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
   mtv::Module *module;
   QPixmap pixmap;
   QRect bounds;
   QImage MatToQImage(const cv::Mat &matrix);
private slots:
   void OnFrameReady(mtv::Module *module, const QString name, cv::Mat &matrix);

};

#endif // VIDEOWIDGET_H
