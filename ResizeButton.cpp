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

#include "ResizeButton.h"

ResizeButton::ResizeButton(QWidget *parent) :
    QWidget(parent)
{
}

void ResizeButton::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ResizeButton::mousePressEvent(QMouseEvent *me)
{
    pressCordX = me->globalX();
    pressCordY = me->globalY();
    oldGeometry = parentWidget()->parentWidget()->geometry();
}

void ResizeButton::mouseMoveEvent(QMouseEvent *me)
{
    deltaX = me->globalX()-pressCordX;
    deltaY = me->globalY()-pressCordY;
    QWidget *w = parentWidget()->parentWidget();
    w->setGeometry(oldGeometry.left(), oldGeometry.top(), oldGeometry.width()+deltaX, oldGeometry.height()+deltaY);

    //w->setGeometry(oldGeometry.left()+deltaX, oldGeometry.top()+deltaY, oldGeometry.width(), oldGeometry.height());
}
