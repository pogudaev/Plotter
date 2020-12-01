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

#include "PSignature.h"

PSignature::PSignature(QObject *parent) :
    QObject(parent)
{
    backgroundColor = Qt::white;
    textColor = Qt::black;
    orientation = Qt::Vertical;
}

PSignature::PSignature(const PSignature &signature) :
    QObject(0)
{
    orientation = signature.orientation;
    backgroundColor = signature.backgroundColor;
    textColor = signature.textColor;
    minimalStep = signature.minimalStep;
}

PSignature::~PSignature()
{

}

void PSignature::setMinimalStep(qreal minStep)
{
    minimalStep = minStep;
    emit hasChange();
}

qreal PSignature::getMinStep()
{
    return minimalStep;
}

void PSignature::setBackground(QColor bgcolor)
{
    backgroundColor = bgcolor;
    emit hasChange();
}

void PSignature::setTextColor(QColor textColor)
{
    this->textColor = textColor;
    emit hasChange();
}

QColor PSignature::getTextColor()
{
    return textColor;
}

QColor PSignature::getBackground()
{
    return backgroundColor;
}

void PSignature::setOrientation(Qt::Orientation orient)
{
    orientation = orient;
    emit hasChange();
}

Qt::Orientation PSignature::getOrientation()
{
    return orientation;
}

QPicture PSignature::getPicture(PCanvas *canvas)
{
    QPicture ret;
    QPainter pntr;
    pntr.begin(&ret);
    if (orientation == Qt::Horizontal){
        for (qreal x = 0; x<canvas->getCanvasSizeXUnit()-canvas->getShiftXUnit(); x+=minimalStep){
            if (canvas->xInWindow(x)){
                QPointF ps;
                ps = QPointF(x,0);
                ps = canvas->canvasPointToWindowPointPix(canvas->canvasPointUnitToPix(ps));
                ps.setY(canvas->getWindowSizeYPix()-30);
                helperRenderFunction(pntr,x,ps);
            }
        }
        for (qreal x = -minimalStep; x> -canvas->getShiftXUnit(); x-=minimalStep){
            if (canvas->xInWindow(x)){
                QPointF ps;
                ps = QPointF(x,0);
                ps = canvas->canvasPointToWindowPointPix(canvas->canvasPointUnitToPix(ps));
                ps.setY(canvas->getWindowSizeYPix()-30);
                helperRenderFunction(pntr,x,ps);
            }
        }
    }
    else{
        for (qreal y = 0; y<canvas->getCanvasSizeYUnit()-canvas->getShiftYUnit(); y+=minimalStep){
            if (canvas->yInWindow(y)){
                QPointF ps;
                ps = QPointF(0,y);
                ps = canvas->canvasPointToWindowPointPix(canvas->canvasPointUnitToPix(ps));
                ps.setX(30);
                helperRenderFunction(pntr,y,ps);
            }
        }
        for (qreal y = -minimalStep; y> -canvas->getShiftYUnit(); y-=minimalStep){
            if (canvas->yInWindow(y)){
                QPointF ps;
                ps = QPointF(0,y);
                ps = canvas->canvasPointToWindowPointPix(canvas->canvasPointUnitToPix(ps));
                ps.setX(30);
                helperRenderFunction(pntr,y,ps);
            }
        }
    }
    pntr.end();
    return ret;
}

void PSignature::helperRenderFunction(QPainter &pntr, qreal value, QPointF &coord)
{
    QPainter temppntr;
    QPicture tespic;
    QRectF labelArea;
    labelArea.setTopLeft(coord);
    labelArea.setSize(QSizeF(0,0));
    QRectF frame;
        temppntr.begin(&tespic);
        temppntr.drawText(labelArea, Qt::AlignCenter, QString::number(value), &frame);
        temppntr.end();
        pntr.setPen(QPen(textColor,1));
    pntr.setBrush(backgroundColor);
    pntr.drawRect(frame.x()-3,frame.y()-3,frame.width()+6,frame.height()+6);
    pntr.drawText(frame, Qt::AlignCenter, QString::number(value));
    return;
}





