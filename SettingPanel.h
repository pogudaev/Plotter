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

#ifndef SETTINGPANEL_H
#define SETTINGPANEL_H

#include <QWidget>
#include "PPlot.h"

namespace Ui {
class SettingPanel;
}

class SettingPanel : public QWidget
{
    Q_OBJECT

public:
    explicit SettingPanel(QWidget *parent = 0);
    ~SettingPanel();
    void setPPlot(PPlot *plot);

private slots:
    void on_colorPlotButton_hasChange();

    void on_autoScaleBox_clicked(bool checked);

    void on_scaleXBox_valueChanged(double arg1);

    void on_scaleYBox_valueChanged(double arg1);

    void on_cutButton_clicked();

    void on_saveButton_clicked();

    void on_enableXBox_clicked(bool checked);

    void on_enableYBox_clicked(bool checked);

    void on_stepXBox_valueChanged(double arg1);

    void on_stepYBox_valueChanged(double arg1);

    void on_colorTextX_hasChange();

    void on_colorTextY_hasChange();

    void on_colorBgX_hasChange();

    void on_colorBgY_hasChange();

public slots:
    void plot_resized();
    void plot_coord(qreal x, qreal y, bool inWidget);

private:
    PPlot *plot;
    PSignature *sigX, *sigY;
    Ui::SettingPanel *ui;

signals:
    void crop();
    void saveSVG(QString filename);
    void saveRaster(QString filename);
};

#endif // SETTINGPANEL_H
