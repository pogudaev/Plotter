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

PCanvas::PCanvas(QObject *parent) :
    QObject(parent)
{
    scaleX = 1;
    scaleY = 1;
    windowSizeX = 10;
    windowSizeY = 10;
    canvasSizeX = 300;
    canvasSizeY = 300;
    shiftX = 150;
    shiftY = 150;
    windowShiftX = 150;
    windowShiftY = 150;
    scrollingJumpInterval = 1;
}

qreal PCanvas::setScaleX(qreal scx)
{
    qreal wsx = windowSizeX * (scaleX / scx);
    qreal windowCenterX = windowShiftX + windowSizeX/2;
    if (scx!=0){
        if (wsx > canvasSizeX){
            qDebug()<< "scale X reach of limit";
            scaleX = scaleX * (windowSizeX/canvasSizeX);
            windowSizeX = canvasSizeX;
        }
        else{
            windowSizeX = wsx;
            scaleX = scx;
        }
        windowShiftX = windowCenterX - windowSizeX/2;
        if (windowShiftX < 0) windowShiftX = 0;
        if (windowShiftX > (canvasSizeX-windowSizeX)) windowShiftX = (canvasSizeX-windowSizeX);
    }
    else qDebug()<<"error: scale X must not to be zero";
    return windowShiftX*scaleX / scrollingJumpInterval;
}

qreal PCanvas::setScaleY(qreal scy)
{
    qreal wsy = windowSizeY * (scaleY / scy);
    qreal windowCenterY = windowShiftY + windowSizeY/2;
    if (scy!=0){
        if (wsy > canvasSizeY){
            qDebug()<< "scale Y reach of limit";
            scaleY = scaleY * (windowSizeY/canvasSizeY);
            windowSizeY = canvasSizeY;
        }
        else{
            windowSizeY = wsy;
            scaleY = scy;
        }
        windowShiftY = windowCenterY - windowSizeY/2;
        if (windowShiftY < 0) windowShiftY = 0;
        if (windowShiftY > (canvasSizeY-windowSizeY)) windowShiftY = (canvasSizeY-windowSizeY);
    }
    else qDebug()<<"error: scale Y must not to be zero";
    return getMaxScrollYValue()-(windowShiftY*scaleY / scrollingJumpInterval);
}

void PCanvas::setShiftXPix(qreal shxp)
{
    shiftX = shxp / scaleX;
}

void PCanvas::setShiftYPix(qreal shyp)
{
    shiftY = shyp / scaleY;
}

void PCanvas::setShiftXUnit(qreal shxu)
{
    shiftX = shxu;
}

void PCanvas::setShiftYUnit(qreal shyu)
{
    shiftY = shyu;
}

void PCanvas::setCanvasSizeXUnit(qreal csxu)
{
    canvasSizeX = csxu;
}

void PCanvas::setCanvasSizeYUnit(qreal csyu)
{
    canvasSizeY = csyu;
}

void PCanvas::setCanvasSizeXPix(qreal csxp)
{
    canvasSizeX = csxp / scaleX;
}

void PCanvas::setWindowSizeXPix(qreal wsxp)
{
    windowSizeX = wsxp / scaleX;
    if (windowSizeX > canvasSizeX){
        windowSizeX = canvasSizeX;
        scaleX = wsxp/windowSizeX;
    }
}

void PCanvas::setWindowSizeYPix(qreal wsyp)
{
    windowSizeY = wsyp / scaleY;
    if (windowSizeY > canvasSizeY){
        windowSizeY = canvasSizeY;
        scaleY = wsyp / windowSizeY;
    }
}

void PCanvas::setScrollingJumpIntervalPix(qreal sjip)
{
    scrollingJumpInterval = sjip;
}

void PCanvas::setWimdowFromScrollValue(qreal scrX, qreal scrY)
{
    windowShiftX = (scrX * scrollingJumpInterval)/scaleX;
    windowShiftY = canvasSizeY - (scrY * scrollingJumpInterval)/scaleY - windowSizeY;
}

qreal PCanvas::getScaleX()
{
    return scaleX;
}

qreal PCanvas::getScaleY()
{
    return scaleY;
}

qreal PCanvas::getShiftXUnit()
{
    return shiftX;
}

qreal PCanvas::getShiftYUnit()
{
    return shiftY;
}

qreal PCanvas::getCanvasSizeXUnit()
{
    return canvasSizeX;
}

qreal PCanvas::getCanvasSizeYUnit()
{
    return canvasSizeY;
}

qreal PCanvas::getWindowSizeXPix()
{
    return windowSizeX * scaleX;
}

qreal PCanvas::getWindowSizeYPix()
{
    return windowSizeY * scaleY;
}

qreal PCanvas::getWindowSizeXUnit()
{
    return windowSizeX;
}

qreal PCanvas::getWindowSizeYUnit()
{
    return windowSizeY;
}

qreal PCanvas::getWindowShiftXUnit()
{
    return windowShiftX;
}

qreal PCanvas::getWindowShiftYUnit()
{
    return windowShiftY;
}

qreal PCanvas::getMaxScrollXValue()
{
    return (canvasSizeX - windowSizeX)/(scrollingJumpInterval/scaleX);
}

qreal PCanvas::getMaxScrollYValue()
{
    return (canvasSizeY - windowSizeY)/(scrollingJumpInterval/scaleY);
}

qreal PCanvas::getWindowCenterXScroll()
{
    //qDebug()<<(shiftX-windowSizeX/2)*scaleX/scrollingJumpInterval;
    //return (windowSizeX/2-shiftX)*scaleX/scrollingJumpInterval;
    return ((canvasSizeX-windowSizeX)/2)*scaleX/scrollingJumpInterval;
}

qreal PCanvas::getWindowCenterYScroll()
{
    return (shiftY-windowSizeY/2)*scaleY/scrollingJumpInterval;
}

QPointF PCanvas::canvasPointToWindowPointPix(QPointF cpp)
{
    QPointF ret;
    ret.setX((shiftX + (cpp.x() / scaleX) - windowShiftX) * scaleX);
    ret.setY((windowSizeY-((shiftY + (cpp.y() / scaleY) - windowShiftY))) * scaleY);
    return ret;
}

QPointF PCanvas::windowPointToCanvasPointPix(QPointF wpp)
{
    QPointF ret;
    ret.setX(((wpp.x() / scaleX) + windowShiftX - shiftX) * scaleX);
    ret.setY(((windowSizeY - (wpp.y() / scaleY)) + windowShiftY - shiftY) * scaleY);
    return ret;
}

QPointF PCanvas::canvasPointUnitToPix(QPointF cpu)
{
    QPointF ret;
    ret.setX(cpu.x() * scaleX);
    ret.setY(cpu.y() * scaleY);
    return ret;
}

QPointF PCanvas::canvasPointPixToUnit(QPointF cpp)
{
    QPointF ret;
    ret.setX(cpp.x() / scaleX);
    ret.setY(cpp.y() / scaleY);
    return ret;
}

bool PCanvas::xInWindow(qreal canvasX)
{
    return (((shiftX + canvasX) >= windowShiftX) && ((shiftX + canvasX) <= windowShiftX + windowSizeX));
}

bool PCanvas::yInWindow(qreal canvasY)
{
    return (((shiftY + canvasY) >= windowShiftY) && ((shiftY + canvasY) <= windowShiftY + windowSizeY));
}

bool PCanvas::pointInWindow(QPointF canvasPoint)
{
    return (yInWindow(canvasPoint.y()) && xInWindow(canvasPoint.x()));
}












