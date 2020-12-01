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

#include "AdderPCurve.h"

AdderPCurve::AdderPCurve(QWidget *parent) :
    AdderSomeThings(parent)
{
}

void AdderPCurve::clickBox(QWidget *wdg)
{

    TwoButton *tb = (TwoButton *)wdg;
    if (tb->getButtonID() == RemoveButton){
        plot->unbindPCurve(*((PCurve *)(tb->object)));
        delete tb;
        adjustSize();
    }
    else{
        QPen pen = PenDialog::getPen(plot->getBackgroundColor(),
                                     0,
                                     QString::fromUtf8("Установка линии"),
                                     ((PCurve *)(tb->object))->getPen());
        ((PCurve *)(tb->object))->setPen(pen);
    }
}

void AdderPCurve::callAdd()
{
    QString filename = "";
    filename = QFileDialog::getOpenFileName(this,
                                            QString::fromUtf8("Открыть файл траектории..."),
                                            QString(""),
                                            QString("(*.csv)"));
    if (!filename.isEmpty()){
        vblMain->removeItem(bottomLayout);
        TwoButton *newTwoButton = new TwoButton();
        newTwoButton->object = new PCurve();
        plot->bindPCurve(*(PCurve *)(newTwoButton->object));
        connect(newTwoButton, SIGNAL(click()), signMaper, SLOT(map()));
        signMaper->setMapping(newTwoButton,newTwoButton);
        vblMain->addWidget(newTwoButton);
        vblMain->addLayout(bottomLayout);
        ((PCurve *)(newTwoButton->object))->loadFromCSV(filename);
        QPen pen = PenDialog::getPen(plot->getBackgroundColor());
        ((PCurve *)(newTwoButton->object))->setPen(pen);
    }
}
