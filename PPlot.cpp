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

#include "PPlot.h"

PPlot::PPlot(QWidget *parent) :
    QWidget(parent)
{
    //Выделение памяти
    hScroll = new QScrollBar(Qt::Horizontal,this);
    vScroll = new QScrollBar(Qt::Vertical, this);
    renderArea = new QPicture();
    painter = new QPainter();
    canvas = new PCanvas();
    //Начальная инициализация
    startInit();
    //сигналы и слоты
    connect(vScroll, SIGNAL(valueChanged(int)), this,SLOT(changeScroll()));
    connect(hScroll, SIGNAL(valueChanged(int)), this,SLOT(changeScroll()));

}

PPlot::~PPlot()
{
    delete vScroll;
    delete hScroll;
    delete painter;
    delete renderArea;
}

void PPlot::bindPCurve(PCurve &curve)
{
    curves.append(&curve);
    connect(&curve, SIGNAL(hasChange()), this, SLOT(objectsUpdated()));
    update();
}

void PPlot::bindPSignature(PSignature &signature)
{
    signatures.append(&signature);
    connect(&signature, SIGNAL(hasChange()), this, SLOT(objectsUpdated()));
    update();
}

void PPlot::enableAutoScale(bool enASc)
{
    autoScale = enASc;
    if (autoScale){
        canvas->setScaleX(0.0000000000000000001);
        canvas->setScaleY(0.0000000000000000001);
        canvas->setWindowSizeXPix(width());
        canvas->setWindowSizeYPix(height());
        hScroll->hide();
        vScroll->hide();
    }
    else{
        hScroll->setGeometry(0,height()-scrollSize,
                             width()-scrollSize, scrollSize);
        vScroll->setGeometry(width()-scrollSize,0,
                             scrollSize, height() - scrollSize);
        hScroll->show();
        vScroll->show();
    }
    update();
}

QColor PPlot::getBackgroundColor()
{
    return backgroundColor;
}

qreal PPlot::getScaleX()
{
    return canvas->getScaleX();
}

qreal PPlot::getScaleY()
{
    return canvas->getScaleY();
}


void PPlot::setBorderFrom(PCurve &curve)
{
    QRectF needRect;
    if (curves.contains(&curve)){
        needRect = curve.getLimits();
        canvas->setCanvasSizeXUnit(needRect.width());
        canvas->setCanvasSizeYUnit(needRect.height());
        canvas->setShiftXUnit(-needRect.left());
        canvas->setShiftYUnit(-needRect.top());
        resizeProcessing();
    }
}

void PPlot::saveAsSVG(QString filename)
{
    QSvgGenerator generator;
    generator.setFileName(filename);
    QPainter pntr;
    renderPlot();
    pntr.begin(&generator);
    renderArea->play(&pntr);
    pntr.end();
}

void PPlot::saveAsRaster(QString filename)
{
    QImage *image = new QImage((!autoScale)?width()-scrollSize:width(),
                               (!autoScale)?height()-scrollSize:height(),
                               QImage::Format_ARGB32);
    QPainter pntr;
    renderPlot();
    pntr.begin(image);
    renderArea->play(&pntr);
    pntr.end();
    image->save(filename);
    delete image;
}

void PPlot::setMinimalLimits(QRectF ml)
{
    minimalLimits = ml;
}

void PPlot::scrollToRight()
{
    hScroll->setValue(hScroll->maximum());
}

void PPlot::scrollToLeft()
{
    hScroll->setValue(0);
}

void PPlot::setBackgroundColor(QColor bgcol)
{
    backgroundColor = bgcol;
    update();
}

void PPlot::resizeEvent(QResizeEvent *)
{
    resizeProcessing();
    emit changedSize();
}

void PPlot::paintEvent(QPaintEvent *)
{
    qDebug()<<canvas->getWindowShiftXUnit();
    renderPlot();
    painter->begin(this);
    renderArea->play(painter);
    painter->end();
}

void PPlot::timerEvent(QTimerEvent *)
{
    bool inWidget;
    QPointF coord = QWidget::mapFromGlobal(QCursor::pos());
    inWidget = ( (coord.x() < width()) && (coord.x() > 0) && (coord.y() > 0) && (coord.y() < height()) );
    coord = canvas->windowPointToCanvasPointPix(coord);
    coord = canvas->canvasPointPixToUnit(coord);
    emit mouseCoord(coord.x(), coord.y(), inWidget);
}

void PPlot::renderPlot()
{
    int numberOfCurves = curves.size();
    int numberOfSignatures = signatures.size();
    painter->begin(renderArea);
    painter->setBrush(backgroundColor);
    painter->drawRect(0,0,canvas->getWindowSizeXPix(), canvas->getWindowSizeYPix());
    int numberOfGrids = grids.size();
    for (int i = 0; i < numberOfGrids; i++){
        grids.at(i)->getPicture(canvas).play(painter);
    }
    for (int i = 0; i < numberOfCurves; i++){
        curves.at(i)->getPicture(canvas).play(painter);
    }
    for (int i = 0; i < numberOfSignatures; i++){
        signatures.at(i)->getPicture(canvas).play(painter);
    }
    painter->end();
}

void PPlot::objectsUpdated()
{
    update();
}

void PPlot::setBorderFromAllCurves()
{
    QRectF needRect;
    int numberOfCurves = curves.size();
    if (numberOfCurves) needRect = curves.at(0)->getLimits();
    for (int i=1; i<numberOfCurves; i++){
        needRect = needRect.united(curves.at(i)->getLimits());
    }
    canvas->setCanvasSizeXUnit(needRect.width());
    canvas->setCanvasSizeYUnit(needRect.height());
    canvas->setShiftXUnit(-needRect.left());
    canvas->setShiftYUnit(-needRect.top());
    resizeProcessing();
}

void PPlot::startInit()
{
    minimalLimits = QRectF(-1,-1,2,2);
    startTimer(10);
    enableAutoScale(false);
    scrollSize = 15;
    scrollingJamp = 10; //пикселей
    canvas->setCanvasSizeXUnit(100);
    canvas->setCanvasSizeYUnit(100);
    canvas->setShiftXUnit(50);
    canvas->setShiftYUnit(50);
    setScale(10,10);
    backgroundColor = Qt::white;
}

void PPlot::resizeProcessing()
{
    if (autoScale){
        canvas->setScaleX(0.00000000000000000001);
        canvas->setScaleY(0.00000000000000000001);
        canvas->setWindowSizeXPix(width());
        canvas->setWindowSizeYPix(height());
    }
    else{
        canvas->setWindowSizeXPix(width()-scrollSize);
        canvas->setWindowSizeYPix(height()-scrollSize);
        hScroll->setGeometry(0,height()-scrollSize, width()-scrollSize, scrollSize);
        vScroll->setGeometry(width()-scrollSize,0,scrollSize, height() - scrollSize);
        qDebug()<<canvas->getWindowCenterXScroll()<<canvas->getWindowCenterYScroll();
        canvas->setWimdowFromScrollValue(
                    canvas->getWindowCenterXScroll(),
                    canvas->getWindowCenterYScroll());
        helperScaleFunction(canvas->getWindowCenterXScroll(),canvas->getWindowCenterYScroll());
    }
    update();
}

void PPlot::helperScaleFunction(qreal hScrollValue, qreal vScrollValue)
{
    disconnect(hScroll,SIGNAL(valueChanged(int)),this,SLOT(changeScroll()));
    disconnect(vScroll,SIGNAL(valueChanged(int)),this,SLOT(changeScroll()));
    hScroll->setValue(0);
    vScroll->setValue(0);
    hScroll->setMaximum(canvas->getMaxScrollXValue());
    vScroll->setMaximum(canvas->getMaxScrollYValue());
    hScroll->setValue(hScrollValue);
    vScroll->setValue(vScrollValue);
    connect(hScroll,SIGNAL(valueChanged(int)),this,SLOT(changeScroll()));
    connect(vScroll,SIGNAL(valueChanged(int)),this,SLOT(changeScroll()));
}

void PPlot::changeScroll()
{
    qDebug()<<hScroll->value()<<vScroll->value();
    canvas->setWimdowFromScrollValue(hScroll->value(), vScroll->value());
    update();
}

void PPlot::setScale(qreal xScale, qreal yScale)
{
    helperScaleFunction(canvas->setScaleX(xScale), canvas->setScaleY(yScale));
    update();

}

void PPlot::setShift(qreal sx, qreal sy)
{
    canvas->setShiftXUnit(sx);
    canvas->setShiftYUnit(sy);
    //helperScaleFunction(canvas->getWindowCenterXScroll(),canvas->getWindowCenterYScroll());
    update();
}

void PPlot::setSize(qreal w, qreal h)
{
    canvas->setCanvasSizeXUnit(w);
    canvas->setCanvasSizeYUnit(h);
    //helperScaleFunction(canvas->getWindowCenterXScroll(),canvas->getWindowCenterYScroll());
    update();
}

void PPlot::setScaleX(qreal xScale)
{
    qreal currScrollXVal = canvas->setScaleX(xScale);
    disconnect(hScroll,SIGNAL(valueChanged(int)),this,SLOT(changeScroll()));
    hScroll->setValue(0);
    hScroll->setMaximum(canvas->getMaxScrollXValue());
    hScroll->setValue(currScrollXVal);
    connect(hScroll,SIGNAL(valueChanged(int)),this,SLOT(changeScroll()));
    update();
}

void PPlot::setScaleY(qreal yScale)
{
    qreal currScrollYVal = canvas->setScaleY(yScale);
    disconnect(vScroll,SIGNAL(valueChanged(int)),this,SLOT(changeScroll()));
    vScroll->setValue(0);
    vScroll->setMaximum(canvas->getMaxScrollYValue());
    vScroll->setValue(currScrollYVal);
    connect(vScroll,SIGNAL(valueChanged(int)),this,SLOT(changeScroll()));
    update();
}


void PPlot::bindPGrid(PGrid &grid)
{
    grids.append(&grid);
    connect(&grid, SIGNAL(hasChange()), this, SLOT(objectsUpdated()));
    update();
}

void PPlot::unbindPCurve(PCurve &curve)
{
    disconnect(&curve, SIGNAL(hasChange()), this, SLOT(objectsUpdated()));
    curves.removeOne(&curve);
    update();
}

void PPlot::unbindPSignature(PSignature &signature)
{
    disconnect(&signature, SIGNAL(hasChange()), this, SLOT(objectsUpdated()));
    signatures.removeOne(&signature);
    update();
}

void PPlot::unbindPGrid(PGrid &grid)
{
    disconnect(&grid, SIGNAL(hasChange()), this, SLOT(objectsUpdated()));
    grids.removeOne(&grid);
    update();
}

