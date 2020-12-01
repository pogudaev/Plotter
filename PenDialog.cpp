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

#include "PenDialog.h"
#include "ui_PenDialog.h"

PenDialog::PenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PenDialog)
{
    ui->setupUi(this);
    setLayout(ui->mainLayout);
    setWindowFlags(Qt::Tool);
    adjustSize();
}

QPen PenDialog::getPen(QColor background,
                       QWidget *parent, QString title,
                       QPen defaultPen)
{
    PenDialog pg(parent);
    bool st = false;
    QPen temp = defaultPen;
    pg.setStateValue(st);
    pg.setWindowTitle(title);
    pg.setOutputPen(temp);
    pg.setBackground(background);
    pg.show();
    pg.exec();
    if (st) return temp;
    else return defaultPen;
}

PenDialog::~PenDialog()
{
    delete ui;
}

void PenDialog::setOutputPen(QPen &pen)
{
    outputPen = &pen;
    ui->viewArea->setPen(*outputPen);
    ui->colorChoiser->setColor(outputPen->color());
    ui->widthBox->setValue(outputPen->widthF());
    ui->typeBox->setCurrentIndex(outputPen->style());
    if (outputPen->joinStyle() == Qt::RoundJoin){
        ui->cutBox->setCurrentIndex(1);
    }
    else{
        ui->cutBox->setCurrentIndex(0);
    }
}

void PenDialog::setStateValue(bool &state)
{
    this->state = &state;
}

void PenDialog::setBackground(QColor background)
{
    ui->viewArea->setBackground(background);
}

void PenDialog::on_typeBox_activated(int index)
{
    outputPen->setStyle(Qt::PenStyle(index));
    ui->viewArea->setPen(*outputPen);
}

void PenDialog::on_colorChoiser_hasChange()
{
    outputPen->setBrush(ui->colorChoiser->getColor());
    ui->viewArea->setPen(*outputPen);
}

void PenDialog::on_widthBox_valueChanged(double arg1)
{
    outputPen->setWidthF(arg1);
    ui->viewArea->setPen(*outputPen);
}

void PenDialog::on_cutBox_activated(int index)
{
    if (index){
        outputPen->setJoinStyle(Qt::RoundJoin);
        outputPen->setCapStyle(Qt::RoundCap);
    }
    else{
        outputPen->setJoinStyle(Qt::BevelJoin);
        outputPen->setCapStyle(Qt::SquareCap);
    }
    ui->viewArea->setPen(*outputPen);
}

void PenDialog::on_cancelButton_clicked()
{
    *state = false;
    close();
}

void PenDialog::on_okButton_clicked()
{
    *state = true;
    close();
}
