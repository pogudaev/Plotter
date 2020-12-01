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

#include "PCurve.h"

PCurve::PCurve(QObject *parent) :
    QObject(parent)
{
    pen = QPen(Qt::black,2,Qt::SolidLine,
               Qt::RoundCap, Qt::RoundJoin);
}

PCurve::PCurve(const PCurve &curve) :
    QObject(0)
{
    points = curve.points;
    pen = curve.pen;
}

void PCurve::addBackPoint(QPointF point)
{
    points.push_back(point);
    extendLimit(point);
    emit hasChange();
}

void PCurve::addFrontPoint(QPointF point)
{
    points.push_front(point);
    extendLimit(point);
    emit hasChange();
}

void PCurve::insertPrevPoint(int n, QPointF point)
{
    points.insert(n, point);
    extendLimit(point);
    emit hasChange();
}

QPicture PCurve::getPicture(PCanvas *canvas)
{
    QPicture ret;
    QPainter pntr;
    QPointF temp;
    QPointF lastPoint;
    QVector<QLineF> lines;
    int counter = 0;
    bool start = false;
    if (!points.isEmpty()){
        do{
            temp = points.at(counter);
            if (start){
                if (!canvas->pointInWindow(temp)){
                    start = false;
                }
                temp = canvas->canvasPointToWindowPointPix(canvas->canvasPointUnitToPix(temp));
                lines.append(QLineF(lastPoint, temp));
                lastPoint = temp;
            }
            else{
                if (canvas->pointInWindow(temp)){
                    //нашли новую стартовую точку
                    if (counter>0){
                        //у точки есть предшественник
                        lastPoint = canvas->canvasPointToWindowPointPix(canvas->canvasPointUnitToPix(points.at(counter-1)));
                        temp = canvas->canvasPointToWindowPointPix(canvas->canvasPointUnitToPix(temp));
                        lines.append(QLineF(lastPoint, temp));
                        lastPoint = temp;
                    }
                    else{
                        //у точки нет предшественников
                        lastPoint = canvas->canvasPointToWindowPointPix(canvas->canvasPointUnitToPix(temp));
                    }
                    start = true;
                }
            }
            counter++;
        }
        while (counter<points.size());
    }
    pntr.begin(&ret);
    pntr.setPen(pen);
    pntr.drawLines(lines);
    pntr.end();
    return ret;
}

QRectF PCurve::getLimits()
{
    return limits;
}

void PCurve::setPen(QPen pen)
{
    this->pen = pen;
}

QPen PCurve::getPen()
{
    return pen;
}

void PCurve::loadFromCSV(QString filename)
{
    QFile file(filename);
    file.open(QFile::ReadOnly);
    QString data = file.readAll();
    file.close();
    QStringList list = data.split(QString("\n"),QString::SkipEmptyParts);
    QStringList point;
    double x, y;
    bool state;
    while(!list.isEmpty()){
        point = list.first().split(QString(";"));
        list.removeFirst();
        state = true;
        x = point.first().replace(",",".").toDouble(&state);
        if (!state){
            qDebug()<<"errorX csv";
            state = true;
        }
        y = point.last().replace(",",".").toDouble(&state);
        if (!state){
            qDebug()<<"errorY csv";
            state = true;
        }
        addFrontPoint(QPointF(x,y));
    }
    limits = findLimits();
}

QRectF PCurve::findLimits()
{
    QRectF ret;
    qreal top, left, right, bottom;
    top = bottom = points.at(0).y();
    left = right = points.at(0).x();
    for (int i = 0; i<points.size(); i++){
        if (points.at(i).y() < top) top = points.at(i).y();
        if (points.at(i).x() > right) right = points.at(i).x();
        if (points.at(i).y() > bottom) bottom = points.at(i).y();
        if (points.at(i).x() < left) left = points.at(i).x();
    }
    ret.setCoords(left,top,right,bottom);
    return ret;
}

void PCurve::extendLimit(QPointF point)
{
    if (point.x() > limits.right()) limits.setRight(point.x());
    if (point.x() < limits.left()) limits.setLeft(point.x());
    if (point.y() < limits.top()) limits.setTop(point.y());
    if (point.y() > limits.bottom()) limits.setBottom(point.y());
}
