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

#ifndef PLOTTERDEMO_H
#define PLOTTERDEMO_H

#include <QDebug>
#include <QWidget>
#include <QMouseEvent>
#include "PenDialog.h"
#include <QFile>
#include "PGrid.h"
#include "PCurve.h"
#include "PSignature.h"
#include <cmath>
#include "AdderPGrid.h"

namespace Ui {
class PlotterDemo;
}

class PlotterDemo : public QWidget
{
    Q_OBJECT

public:
    explicit PlotterDemo(QWidget *parent = 0);
    ~PlotterDemo();


private:
    PSignature *timeSig;
    PSignature *ampSig;
    PGrid *mainGridX;
    PGrid *mainGridY;
    PGrid *baseGridX;
    PGrid *baseGridY;
    PGrid *helperGridX;
    PGrid *helperGridY;
    PCurve *curveXMouse;
    PCurve *curveYMouse;
    void dynacInit();




private slots:
    void on_exitButton_clicked();


    void on_sensor_newData(const qreal time, const qreal x, const qreal y);

private:
    Ui::PlotterDemo *ui;
};

#endif // PLOTTERDEMO_H
