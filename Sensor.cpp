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

#include "Sensor.h"

Sensor::Sensor(QWidget *parent) :
    QWidget(parent)
{
    time = 0;
    startTimer(50);
}

void Sensor::timerEvent(QTimerEvent *)
{
    QPointF pos = QWidget::mapFromGlobal(QCursor::pos());
    if (pos.x()<width() && pos.x()>0 && pos.y()>0 && pos.y()<height()){
        time+=0.05;
        emit newData(time, pos.x()-100, -pos.y()+100);
    }
}

void Sensor::paintEvent(QPaintEvent *)
{
    QPainter pntr;
    pntr.begin(this);
    pntr.drawRect(0,0,width()-1, height()-1);
    pntr.setPen(Qt::black);
    pntr.drawText(geometry(),Qt::AlignCenter, QString::fromUtf8("Сенсор"));
    pntr.end();
}
