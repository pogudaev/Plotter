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

#ifndef PCURVE_H
#define PCURVE_H

#include <QObject>
#include <QVector>
#include <QPointF>
#include <QPicture>
#include <QPainter>
#include "PCanvas.h"
#include <QFile>

class PCurve : public QObject
{
    Q_OBJECT
public:
    explicit PCurve(QObject *parent = 0);
    PCurve(PCurve const &curve);
    void addBackPoint(QPointF point);
    void addFrontPoint(QPointF point);
    void insertPrevPoint(int n, QPointF point);
    QPointF getPoint(int n);
    QVector<int> findBetween(QPointF leftTop, QPointF rightBottom);
    void clear();
    QPicture getPicture(PCanvas *canvas);
    QRectF getLimits();
    void setPen(QPen pen);
    QPen getPen();
    void loadFromCSV(QString filename);





private:
    QVector<QPointF> points;
    QPen pen;
    QRectF limits;
    QRectF findLimits();
    void extendLimit(QPointF point);


signals:
    void hasChange();

public slots:

};

#endif // PCURVE_H
