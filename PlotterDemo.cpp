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

#include "PlotterDemo.h"
#include "ui_PlotterDemo.h"

PlotterDemo::PlotterDemo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotterDemo)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    ui->head->setLayout(ui->headLayout);
    ui->substrate->setLayout(ui->gridLayout);
    this->setLayout(ui->mainLayout);

    //=======================
    ui->demo1Page->setLayout(ui->demo1Layout);
    ui->settingWidget->setPPlot(ui->plot);
    //=======================
    connect(ui->plot, SIGNAL(changedSize()), ui->settingWidget, SLOT(plot_resized()));
    connect(ui->plot, SIGNAL(mouseCoord(qreal,qreal,bool)), ui->settingWidget, SLOT(plot_coord(qreal,qreal,bool)));
    connect(ui->settingWidget, SIGNAL(crop()), ui->plot, SLOT(setBorderFromAllCurves()));
    connect(ui->settingWidget, SIGNAL(saveSVG(QString)), ui->plot, SLOT(saveAsSVG(QString)));
    connect(ui->settingWidget, SIGNAL(saveRaster(QString)), ui->plot, SLOT(saveAsRaster(QString)));

    //======================
    ui->demo2Page->setLayout(ui->dynamicLayout);
    dynacInit();

}

PlotterDemo::~PlotterDemo()
{
    delete ui;
    delete timeSig;
    delete ampSig;
    delete mainGridX;
    delete mainGridY;
    delete baseGridX;
    delete baseGridY;
    delete helperGridX;
    delete helperGridY;
    delete curveXMouse;
    delete curveYMouse;
}

void PlotterDemo::dynacInit()
{
    ui->dynamicPlot->update();
    timeSig = new PSignature();
    timeSig->setMinimalStep(5);
    timeSig->setOrientation(Qt::Horizontal);
    ui->dynamicPlot->bindPSignature(*timeSig);
    ampSig = new PSignature();
    ampSig->setMinimalStep(25);
    ampSig->setOrientation(Qt::Vertical);
    ui->dynamicPlot->bindPSignature(*ampSig);
    mainGridX = new PGrid();
    mainGridX->setStep(infinity);
    mainGridX->setOrientation(Qt::Horizontal);
    mainGridX->setPen(QPen(Qt::white,3,Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
    ui->dynamicPlot->bindPGrid(*mainGridX);
    mainGridY = new PGrid();
    mainGridY->setStep(infinity);
    mainGridY->setOrientation(Qt::Vertical);
    mainGridY->setPen(QPen(Qt::white,3,Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
    ui->dynamicPlot->bindPGrid(*mainGridY);
    baseGridX = new PGrid();
    baseGridX->setStep(25);
    baseGridX->setOrientation(Qt::Horizontal);
    baseGridX->setPen(QPen(Qt::white,1,Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
    ui->dynamicPlot->bindPGrid(*baseGridX);
    baseGridY = new PGrid();
    baseGridY->setStep(5);
    baseGridY->setOrientation(Qt::Vertical);
    baseGridY->setPen(QPen(Qt::white,1,Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
    ui->dynamicPlot->bindPGrid(*baseGridY);
    helperGridY = new PGrid();
    helperGridY->setStep(0.5);
    helperGridY->setOrientation(Qt::Vertical);
    helperGridY->setPen(QPen(Qt::white,1,Qt::DotLine, Qt::SquareCap, Qt::BevelJoin));
    ui->dynamicPlot->bindPGrid(*helperGridY);
    helperGridX = new PGrid();
    curveXMouse = new PCurve();
    curveXMouse->setPen(QPen(Qt::blue,2,Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
    curveYMouse = new PCurve();
    curveYMouse->setPen(QPen(Qt::red,2,Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
    ui->dynamicPlot->bindPCurve(*curveXMouse);
    ui->dynamicPlot->bindPCurve(*curveYMouse);
    ui->dynamicPlot->setBackgroundColor(Qt::black);

    ui->dynamicPlot->setMinimalLimits(QRectF(0,-100,10,200));
    ui->dynamicPlot->setShift(0,100);
    ui->dynamicPlot->setSize(10,200);
    ui->dynamicPlot->setScale(100,1);
    ui->dynamicPlot->scrollToLeft();
}


void PlotterDemo::on_exitButton_clicked()
{
    this->close();
}




void PlotterDemo::on_sensor_newData(const qreal time, const qreal x, const qreal y)
{
    curveXMouse->addBackPoint(QPointF(time,x));
    curveYMouse->addBackPoint(QPointF(time,y));
    ui->dynamicPlot->setBorderFromAllCurves();
    ui->dynamicPlot->setScale(100,1);
    ui->dynamicPlot->scrollToRight();
}
