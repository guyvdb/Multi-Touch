#include "VideoGrid.h"
#include <QPainter>

VideoGrid::VideoGrid(QSize blockSize, QSize size) : QGraphicsWidget(), blockSize(blockSize), totalSize(size)
{
    this->setMinimumSize(size);
}

void VideoGrid::resizeTo(QSize size) {
    this->totalSize = size;
    this->setMinimumSize(size);
    this->update();
}

void VideoGrid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
   /*
    int cols =   this->size().width() / this->blockSize.width();
    int rows = this->size().height() / this->blockSize.height();

    painter->setPen(Qt::gray);

    int left = 1;

    for(int col = 0; col < cols; col++) {
        painter->drawLine(left,1,left,this->size().height());
        left = left + this->blockSize.width();
    }

    int top = 1;

    for(int row = 0; row < rows; row ++) {
        painter->drawLine(0,top,this->size().width(),top);
        top = top + this->blockSize.height();
    }
    */

}
