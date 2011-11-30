#ifndef VIDEOGRID_H
#define VIDEOGRID_H

#include <QGraphicsWidget>

class VideoGrid : public QGraphicsWidget
{
    Q_OBJECT
public:
    VideoGrid(QSize blockSize, QSize size);
    void resizeTo(QSize size);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QSize blockSize;
    QSize totalSize;
    QRect bounds;

signals:

public slots:

};

#endif // VIDEOGRID_H
