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

#include "ColorButton.h"
#include <QDebug>


ColorButton::ColorButton(QWidget *parent) :
    QPushButton(parent)
{
    color = Qt::white;
}

QColor ColorButton::getColor()
{
    return color;
}

void ColorButton::setColor(QColor color)
{
    this->color = color;
    update();
}

void ColorButton::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    p.setBrush(color);
    p.drawEllipse(5,5,width()-10,height()-10);
    p.end();
}

void ColorButton::mousePressEvent(QMouseEvent *)
{

    setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: \
                    0 #e0e0ef, stop: 0.5 #e4e4ef, stop: 0.51 #d7d7ef, stop: 1.0 #b0b9e0);\
                    border: 1px solid rgb(85, 85, 255); \
                    border-radius: 10px;\
                    margin: 1px 0px 1px 0px;\
                    min-width: 40;\
                    min-height: 40;");
}

void ColorButton::mouseReleaseEvent(QMouseEvent *)
{
    setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, \
                    stop: 0 #f0f0ff, stop: 0.5 #f4f4ff, stop: 0.51 #e7e7ff, stop: 1.0 #d0d9f0);\
                    border: 1px solid rgb(85, 85, 255); \
                    border-radius: 10px;\
                    min-width: 40;\
                    min-height: 40;");
    QColor tempColor = QColorDialog::getColor(Qt::white,this,
                                   QString::fromUtf8("Выбор цвета ..."),
                                   QColorDialog::ShowAlphaChannel);

    if (tempColor.isValid()){
        color = tempColor;
        update();
        emit hasChange();
    }
}


/*

QWidget {
    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #f0f0ff, stop: 0.5 #f4f4ff, stop: 0.51 #e7e7ff, stop: 1.0 #d0d9f0);
    border: 1px solid rgb(85, 85, 255);
    border-radius: 10px;
}

QWidget:pressed {
    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e0e0ef, stop: 0.5 #e4e4ef, stop: 0.51 #d7d7ef, stop: 1.0 #b0b9e0);
    margin: 1px 0px 1px 0px;
}

QWidget::hover {
    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,   stop: 0 #fffaff, stop: 0.5 #fff0c0,  stop: 0.51 #fff0c0, stop: 1.0 #d0d9f0);
}

 */

