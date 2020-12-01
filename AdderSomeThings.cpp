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

#include "AdderSomeThings.h"
#include <QDebug>

AdderSomeThings::AdderSomeThings(QWidget *parent) :
    QWidget(parent)
{
    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    signMaper = new QSignalMapper(this);
    vblMain = new QVBoxLayout(this);
    vblMain->setMargin(0);
    addButton = new QPushButton("+",this);
    bottomLayout = new QHBoxLayout();
    bottomLayout->setMargin(0);
    setLayout(vblMain);
    vblMain->addLayout(bottomLayout);
    bottomLayout->addWidget(addButton);
    connect(addButton,SIGNAL(clicked()),this,SLOT(callAdd()));
    connect(signMaper,SIGNAL(mapped(QWidget*)),this,SLOT(clickBox(QWidget*)));
}

AdderSomeThings::~AdderSomeThings()
{
    delete vblMain;
    delete addButton;
    delete bottomLayout;
    delete signMaper;
}

void AdderSomeThings::setPPlot(PPlot *plot)
{
    this->plot = plot;
}

void AdderSomeThings::clickBox(QWidget* wdg)
{
    TwoButton *tb = (TwoButton *)wdg;
    if (tb->getButtonID() == RemoveButton){
        delete tb;
        adjustSize();
    }
}

void AdderSomeThings::callAdd()
{
    vblMain->removeItem(bottomLayout);
    TwoButton *newTwoButton = new TwoButton();
    connect(newTwoButton, SIGNAL(click()), signMaper, SLOT(map()));
    signMaper->setMapping(newTwoButton,newTwoButton);
    vblMain->addWidget(newTwoButton);
    vblMain->addLayout(bottomLayout);
}
