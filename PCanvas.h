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

#ifndef PCANVAS_H
#define PCANVAS_H

#include <QDebug>
#include <QObject>
#include <QPointF>

//система координат canvas традиционная математическая
//система координат window соотвествует экраннной

class PCanvas : public QObject
{
    Q_OBJECT
public:
    explicit PCanvas(QObject *parent = 0);
    //set
    qreal setScaleX(qreal scx);   //возращает положение полосы прокрутки
    qreal setScaleY(qreal scy);
    void setShiftXPix(qreal shxp);
    void setShiftYPix(qreal shyp);
    void setShiftXUnit(qreal shxu);
    void setShiftYUnit(qreal shyu);
    void setCanvasSizeXUnit(qreal csxu);
    void setCanvasSizeYUnit(qreal csyu);
    void setCanvasSizeXPix(qreal csxp);
    void setCanvasSizeYPix(qreal csyp);
    void setWindowSizeXPix(qreal wsxp);
    void setWindowSizeYPix(qreal wsyp);
    void setWindowSizeXUnit(qreal wsxu);
    void setWindowSizeYUnit(qreal wsyu);
    void setWindowShiftXPix(qreal wshxp);
    void setWindowShiftYPix(qreal wshyp);
    void setWindowShiftXUnit(qreal wshxu);
    void setWindowShiftYUnit(qreal wshyu);
    void setScrollingJumpIntervalPix(qreal sjip);
    void setWimdowFromScrollValue(qreal scrX, qreal scrY);

    //get
    qreal getScaleX();
    qreal getScaleY();
    qreal getShiftXPix();
    qreal getShiftYPix();
    qreal getShiftXUnit();
    qreal getShiftYUnit();
    qreal getCanvasSizeXUnit();
    qreal getCanvasSizeYUnit();
    qreal getCanvasSizeXPix();
    qreal getCanvasSizeYPix();
    qreal getWindowSizeXPix();
    qreal getWindowSizeYPix();
    qreal getWindowSizeXUnit();
    qreal getWindowSizeYUnit();
    qreal getWindowShiftXPix();
    qreal getWindowShiftYPix();
    qreal getWindowShiftXUnit();
    qreal getWindowShiftYUnit();
    qreal getMaxScrollXValue();
    qreal getMaxScrollYValue();
    qreal getActualScrollXValue();
    qreal getActualScrollYValue();
    qreal getWindowCenterXScroll();
    qreal getWindowCenterYScroll();

    //transform
    QPointF canvasPointToWindowPointPix(QPointF cpp);
    QPointF windowPointToCanvasPointPix(QPointF wpp);
    QPointF canvasPointUnitToPix(QPointF cpu);
    QPointF canvasPointPixToUnit(QPointF cpp);

    bool xInWindow(qreal canvasX);
    bool yInWindow(qreal canvasY);
    bool pointInWindow(QPointF canvasPoint);

private:
    qreal shiftX;           //unit          //смещение системы координат относительно нижнего левого угла
    qreal shiftY;           //unit          //смещение системы координат относительно нижнего левого угла
    qreal canvasSizeX;      //unit          //размер поля
    qreal canvasSizeY;      //unit
    qreal windowSizeX;      //unit          //размер окна
    qreal windowSizeY;      //unit
    qreal windowShiftX;     //unit          //смещение нижнего левого угла окна относительно нижнего левого угла поля
    qreal windowShiftY;     //unit
    qreal scaleX;           //pixel/unit    //масштаб
    qreal scaleY;           //pixel/unit
    qreal scrollingJumpInterval;   //pixel
signals:


public slots:

};

#endif // PCANVAS_H
