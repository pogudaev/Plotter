/*
Plotter - graph Builder
Copyright (C) 2020 Alexander Pogudaev

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

	Alexander Pogudaev
	pogudaev@yandex.ru
*/

#include "LineView.h"

LineView::LineView(QWidget *parent) :
    QWidget(parent)
{
    orientation = Polygonal;
}

void LineView::setPen(QPen pen)
{
    this->pen = pen;
    update();
}

void LineView::setOrientation(ViewType orient)
{
    orientation = orient;
    update();
}


void LineView::setBackground(QColor background)
{
    this->background = background;
}

void LineView::paintEvent(QPaintEvent *)
{
    QPainter pntr;
    pntr.begin(this);
    pntr.setBrush(background);
    pntr.setPen(Qt::gray);
    pntr.drawRect(0,0,width()-1, height()-1);
    pntr.setPen(pen);
    switch (orientation) {
    case Horisontal:
        pntr.drawLine(10, height()/2, width()-10, height()/2);
        break;
    case Vertical:
        pntr.drawLine(width()/2,10,width()/2,height()-10);
        break;
    default:
        pntr.drawLine(60, height()/2, width()-20, height()/2);
        pntr.drawLine(width()-20, height()/2, width()-40, height()/4);
        pntr.drawLine(width()-40, height()/4, 40, height()/4);
        pntr.drawLine(40, height()/4, 20, height()/2);
        pntr.drawLine(20, height()/2, 40, height()*3/4);
        pntr.drawLine(40, height()*3/4,  width()-40, height()*3/4);
        break;
    }
    pntr.end();
}
