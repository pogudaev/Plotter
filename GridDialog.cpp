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

#include "GridDialog.h"
#include "ui_GridDialog.h"

#include <QDebug>
GridDialog::GridDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GridDialog)
{
    ui->setupUi(this);
    setLayout(ui->mainLayout);
    setWindowFlags(Qt::Tool);
    adjustSize();
}

GridDialog::~GridDialog()
{
    delete ui;
}

PGrid GridDialog::getGrid(QColor background, PGrid defaultGrid, QWidget *parent, QString title)
{
    PGrid temp = defaultGrid;
    bool st = false;
    GridDialog gd(parent);
    gd.setOutputGrid(temp);
    gd.setBackground(background);
    gd.setWindowTitle(title);
    gd.setStateValue(st);
    gd.show();
    gd.exec();
    if (st) return temp;
    else return defaultGrid;
}

void GridDialog::setOutputGrid(PGrid &grid)
{
    outputGrid = &grid;
    ui->stepBox->setValue(outputGrid->getStep());
    ui->directionBox->setCurrentIndex(int(outputGrid->getOrientation())-1);
    ui->lineType->setOrientation(ViewType(outputGrid->getOrientation()));
    ui->lineType->setPen(outputGrid->getPen());
    ui->lineType->setBackground(background);
}

void GridDialog::setStateValue(bool &state)
{
    this->state = &state;
}

void GridDialog::setBackground(QColor background)
{
    this->background = background;
    ui->lineType->setBackground(background);
    ui->lineType->update();
}


void GridDialog::on_lineButton_clicked()
{
    outputGrid->setPen(PenDialog::getPen(background, this,
                                         QString::fromUtf8("Выбор сетки..."),
                                         outputGrid->getPen()));
    ui->lineType->setPen(outputGrid->getPen());
}

void GridDialog::on_directionBox_activated(int index)
{
    outputGrid->setOrientation(Qt::Orientation(index+1));
    ui->lineType->setOrientation(ViewType(outputGrid->getOrientation()));
}


void GridDialog::on_stepBox_valueChanged(double arg1)
{
    outputGrid->setStep(arg1);
}

void GridDialog::on_cancelButton_clicked()
{
    *state = false;
    close();
}

void GridDialog::on_okButton_clicked()
{
    *state = true;
    close();
}
