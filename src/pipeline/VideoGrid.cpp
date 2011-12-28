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
