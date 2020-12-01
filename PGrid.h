#ifndef PGRID_H
#define PGRID_H

#include <QObject>
#include <QPen>
#include <QPicture>
#include <QPainter>
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

#include "PCanvas.h"

#define infinity (1.0/0.0)

class PGrid : public QObject
{
    Q_OBJECT
public:
    explicit PGrid(QObject *parent = 0);
    PGrid(PGrid const &grid);
    PGrid(QPen pen, qreal step, Qt::Orientation orient, QObject *parent = 0);
    ~PGrid();
    PGrid &operator=(PGrid const &grid);

    void setStep(qreal step);
    qreal getStep();
    void setPen(QPen pen);
    QPen getPen();
    void setOrientation(Qt::Orientation orient);
    Qt::Orientation getOrientation();
    QPicture getPicture(PCanvas *canvas);


private:
    QPen pen;
    qreal step;
    Qt::Orientation orientation;
	constexpr static const qreal minStep = 4;



signals:
    void hasChange();

public slots:

};

#endif // PGRID_H
