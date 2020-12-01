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

#include "PGrid.h"

PGrid::PGrid(QObject *parent) :
    QObject(parent)
{
    pen = QPen(Qt::black,1,Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin);
    step = infinity;
    orientation = Qt::Vertical;

}

PGrid::PGrid(const PGrid &grid):
    QObject(0)
{
    this->step = grid.step;
    this->orientation = grid.orientation;
    this->pen = grid.pen;
}

PGrid::PGrid(QPen pen, qreal step, Qt::Orientation orient, QObject *parent) :
    QObject(parent)
{
    this->pen = pen;
    this->step = step;
    this->orientation = orient;
}

PGrid::~PGrid()
{

}

PGrid &PGrid::operator=(const PGrid &grid)
{
    pen = grid.pen;
    step = grid.step;
    orientation = grid.orientation;
    emit hasChange();
}

void PGrid::setStep(qreal step)
{
    this->step = step;
    emit hasChange();
}

qreal PGrid::getStep()
{
    return step;
}

void PGrid::setPen(QPen pen)
{
    this->pen = pen;
    emit hasChange();
}

QPen PGrid::getPen()
{
    return pen;
}

void PGrid::setOrientation(Qt::Orientation orient)
{
    orientation = orient;
    emit hasChange();
}

Qt::Orientation PGrid::getOrientation()
{
    return orientation;
}

QPicture PGrid::getPicture(PCanvas *canvas)
{
    QPicture ret;
    QPainter pntr;
    pntr.begin(&ret);
    pntr.setPen(pen);
    QPointF p1, p2;
    if (orientation == Qt::Vertical && (minStep/canvas->getScaleX() < step)){
        for (qreal x = 0; x<canvas->getCanvasSizeXUnit()-canvas->getShiftXUnit(); x+=step){
            if (canvas->xInWindow(x)){
                p1.setY(canvas->getWindowShiftYUnit() - canvas->getShiftYUnit());
                p2.setY(canvas->getWindowShiftYUnit() + canvas->getWindowSizeYUnit() - canvas->getShiftYUnit());
                p1.setX(x);
                p2.setX(x);
                p1 = canvas->canvasPointToWindowPointPix(canvas->canvasPointUnitToPix(p1));
                p2 = canvas->canvasPointToWindowPointPix(canvas->canvasPointUnitToPix(p2));
                pntr.drawLine(p1,p2);
            }
        }
        for (qreal x = 0; x> -canvas->getShiftXUnit(); x-=step){
            if (canvas->xInWindow(x)){
                p1.setY(canvas->getWindowShiftYUnit() - canvas->getShiftYUnit());
                p2.setY(canvas->getWindowShiftYUnit() + canvas->getWindowSizeYUnit() - canvas->getShiftYUnit());
                p1.setX(x);
                p2.setX(x);
                p1 = canvas->canvasPointToWindowPointPix(canvas->canvasPointUnitToPix(p1));
                p2 = canvas->canvasPointToWindowPointPix(canvas->canvasPointUnitToPix(p2));
                pntr.drawLine(p1,p2);
            }
        }
    }
    if (orientation == Qt::Horizontal && (minStep/canvas->getScaleY() < step)){
        for (qreal y = 0; y<canvas->getCanvasSizeYUnit()-canvas->getShiftYUnit(); y+=step){
            if (canvas->yInWindow(y)){
                p1.setX(canvas->getWindowShiftXUnit() - canvas->getShiftXUnit());
                p2.setX(canvas->getWindowShiftXUnit() + canvas->getWindowSizeXUnit() - canvas->getShiftXUnit());
                p1.setY(y);
                p2.setY(y);
                p1 = canvas->canvasPointToWindowPointPix(canvas->canvasPointUnitToPix(p1));
                p2 = canvas->canvasPointToWindowPointPix(canvas->canvasPointUnitToPix(p2));
                pntr.drawLine(p1,p2);
            }
        }
        for (qreal y = 0; y> -canvas->getShiftYUnit(); y-=step){
            if (canvas->yInWindow(y)){
                p1.setX(canvas->getWindowShiftXUnit() - canvas->getShiftXUnit());
                p2.setX(canvas->getWindowShiftXUnit() + canvas->getWindowSizeXUnit() - canvas->getShiftXUnit());
                p1.setY(y);
                p2.setY(y);
                p1 = canvas->canvasPointToWindowPointPix(canvas->canvasPointUnitToPix(p1));
                p2 = canvas->canvasPointToWindowPointPix(canvas->canvasPointUnitToPix(p2));
                pntr.drawLine(p1,p2);
            }
        }
    }
    pntr.end();
    return ret;
}


