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

#ifndef RESIZEBUTTON_H
#define RESIZEBUTTON_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>

class ResizeButton : public QWidget
{
    Q_OBJECT
public:
    explicit ResizeButton(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *me);
    void mouseMoveEvent(QMouseEvent *me);

private:
    int pressCordX;
    int pressCordY;
    QRect oldGeometry;
    int deltaX;
    int deltaY;


signals:

public slots:

};

#endif // RESIZEBUTTON_H
