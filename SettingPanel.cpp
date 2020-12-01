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

#include "SettingPanel.h"
#include "ui_SettingPanel.h"

SettingPanel::SettingPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingPanel)
{
    ui->setupUi(this);
    setLayout(ui->mainLayout);
    ui->pageGrid->setLayout(ui->gridLayout);
    ui->pagePlot->setLayout(ui->plotLayout);
    ui->pageCurve->setLayout(ui->curveLayout);
    ui->pageSignature->setLayout(ui->signatureLayout);
    //============
    sigX = new PSignature();
    ui->colorTextX->setColor(Qt::black);
    ui->colorBgX->setColor(Qt::white);
    sigX->setTextColor(ui->colorTextX->getColor());
    sigX->setBackground(ui->colorBgX->getColor());
    sigX->setMinimalStep(ui->stepXBox->value());
    sigX->setOrientation(Qt::Horizontal);
    sigY = new PSignature();
    ui->colorTextY->setColor(Qt::black);
    ui->colorBgY->setColor(Qt::white);
    sigY->setTextColor(ui->colorTextY->getColor());
    sigY->setBackground(ui->colorBgY->getColor());
    sigY->setMinimalStep(ui->stepYBox->value());
    sigY->setOrientation(Qt::Vertical);

}

SettingPanel::~SettingPanel()
{
    delete ui;
    delete sigX;
    delete sigY;
}

void SettingPanel::setPPlot(PPlot *plot)
{
    this->plot = plot;
    ui->adderGrid->setPPlot(plot);
    ui->adderCurve->setPPlot(plot);
    ui->colorPlotButton->setColor(plot->getBackgroundColor());
    ui->scaleXBox->setValue(plot->getScaleX());
    ui->scaleYBox->setValue(plot->getScaleY());
}

void SettingPanel::on_colorPlotButton_hasChange()
{
    plot->setBackgroundColor(ui->colorPlotButton->getColor());
}

void SettingPanel::on_autoScaleBox_clicked(bool checked)
{
    plot->enableAutoScale(checked);
    ui->scaleXBox->setValue(plot->getScaleX());
    ui->scaleYBox->setValue(plot->getScaleY());
    if (checked){
        ui->scaleXBox->setEnabled(false);
        ui->scaleYBox->setEnabled(false);
    }
    else{
        ui->scaleXBox->setEnabled(true);
        ui->scaleYBox->setEnabled(true);
    }
}

void SettingPanel::on_scaleXBox_valueChanged(double arg1)
{
    plot->setScaleX(arg1);
    ui->scaleXBox->setValue(plot->getScaleX());
}

void SettingPanel::on_scaleYBox_valueChanged(double arg1)
{
    plot->setScaleY(arg1);
    ui->scaleYBox->setValue(plot->getScaleY());
}

void SettingPanel::plot_resized()
{
    ui->scaleXBox->setValue(plot->getScaleX());
    ui->scaleYBox->setValue(plot->getScaleY());
}

void SettingPanel::plot_coord(qreal x, qreal y, bool inWidget)
{
    if (inWidget){
        ui->coordXValue->setText(QString::number(x));
        ui->coordYValue->setText(QString::number(y));
    }
    else{
        ui->coordXValue->setText(QString("n/a"));
        ui->coordYValue->setText(QString("n/a"));
    }
}

void SettingPanel::on_cutButton_clicked()
{
    emit crop();
}

void SettingPanel::on_saveButton_clicked()
{
    QString selectedFilter;
    QString filename = QFileDialog::getSaveFileName(this,
                                                    QString::fromUtf8("Сохранить как ..."),
                                                    QString(),
                                                    QString::fromUtf8("Растровые изображения (*.png *.bmp *.jpg);;Векторные изображения (*.svg)"),
                                                    &selectedFilter);
    if (!filename.isEmpty()){
        if (selectedFilter == QString::fromUtf8("Растровые изображения (*.png *.bmp *.jpg)")){
            emit saveRaster(filename);
        }
        else emit saveSVG(filename);
    }
}

void SettingPanel::on_enableXBox_clicked(bool checked)
{
    if (checked) plot->bindPSignature(*sigX);
    else plot->unbindPSignature(*sigX);
}

void SettingPanel::on_enableYBox_clicked(bool checked)
{
    if (checked) plot->bindPSignature(*sigY);
    else plot->unbindPSignature(*sigY);
}

void SettingPanel::on_stepXBox_valueChanged(double arg1)
{
    sigX->setMinimalStep(arg1);
}

void SettingPanel::on_stepYBox_valueChanged(double arg1)
{
    sigY->setMinimalStep(arg1);
}

void SettingPanel::on_colorTextX_hasChange()
{
    sigX->setTextColor(ui->colorTextX->getColor());
}



void SettingPanel::on_colorTextY_hasChange()
{
    sigY->setTextColor(ui->colorTextY->getColor());
}

void SettingPanel::on_colorBgX_hasChange()
{
    sigX->setBackground(ui->colorBgX->getColor());
}

void SettingPanel::on_colorBgY_hasChange()
{
    sigY->setBackground(ui->colorBgY->getColor());
}
