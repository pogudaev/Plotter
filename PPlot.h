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

#ifndef PPLOT_H
#define PPLOT_H

#include <QWidget>
#include <QDebug>
#include <QList>
#include <QRectF>
#include <QScrollBar>
#include <QPainter>
#include <QPicture>
#include "PCurve.h"
#include "PGrid.h"
#include "PSignature.h"
#include "PCanvas.h"
#include <QtSvg/QSvgGenerator>

class PPlot : public QWidget
{
    Q_OBJECT
public:
    explicit PPlot(QWidget *parent = 0);
    ~PPlot();
    void bindPCurve(PCurve &curve);
    void bindPSignature(PSignature &signature);
    void bindPGrid(PGrid &grid);
    void unbindPCurve(PCurve &curve);
    void unbindPSignature(PSignature &signature);
    void unbindPGrid(PGrid &grid);
    void unbindAllPGrids();
    void unbindAllPCurves();
    void unbindAllPSignatures();
    void unbindAll();
    void enableLogScale(bool enLSc);
    void setScaleX(qreal xScale);
    void setScaleY(qreal yScale);
    void setScale(qreal xScale, qreal yScale);
    void setShift(qreal sx, qreal sy);
    void setSize(qreal w, qreal h);
    void enableAutoScale(bool enASc);
    void setBackgroundColor(QColor bgcol);
    QColor getBackgroundColor();
    qreal getScaleX();
    qreal getScaleY();
    void setMinimalLimits(QRectF ml);
    void scrollToRight();
    void scrollToLeft();




protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    virtual void renderPlot();

private:
    QList<PGrid *> grids;
    QList<PCurve *> curves;
    QList<PSignature *> signatures;
    QScrollBar *vScroll, *hScroll;
    PCanvas *canvas;
    int scrollSize;
    bool autoScale;
    QRectF visiblePartOfRenderArea;
    qint32 plotSizeXPix;
    qint32 plotSizeYPix;
    qreal plotSizeXUnit;
    qreal plotSizeYUnit;
    QRect geometryOfRenderArea;  //pix
    QPicture *renderArea;
    QPainter *painter;
    qreal verticalScale;    //пикселей на единицу
    qreal horizontalScale;   //пикселей на единицу
    qint32 scrollingJamp;  //пикселей
    qint32 numberOfRegionX;
    qint32 numberOfRegionY;
    QColor backgroundColor;
    QRectF minimalLimits;
    void startInit();
    void resizeProcessing();
    void helperScaleFunction(qreal hScrollValue, qreal vScrollValue);


signals:
    void changedSize();
    void mouseCoord(qreal x, qreal y, bool inWidget);



private slots:
    void changeScroll();
    void objectsUpdated();


public slots:
    void setBorderFromAllCurves();
    void setBorderFrom(PCurve &curve);
    void saveAsSVG(QString filename);
    void saveAsRaster(QString filename);
};

#endif // PPLOT_H
