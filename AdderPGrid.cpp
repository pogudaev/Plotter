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

#include "AdderPGrid.h"

AdderPGrid::AdderPGrid(QWidget *parent) :
    AdderSomeThings(parent)
{
    addButton->setText(QString::fromUtf8("Добавить сетку..."));
}

void AdderPGrid::clickBox(QWidget *wdg)
{
    TwoButton *tb = (TwoButton *)wdg;
    if (tb->getButtonID() == RemoveButton){
        plot->unbindPGrid(*((PGrid *)(tb->object)));
        delete tb;
        adjustSize();
    }
    else{
        *((PGrid *)(tb->object)) = GridDialog::getGrid(plot->getBackgroundColor(), *((PGrid *)(tb->object)));
    }
}

void AdderPGrid::callAdd()
{
    vblMain->removeItem(bottomLayout);
    TwoButton *newTwoButton = new TwoButton();
    newTwoButton->object = new PGrid();
    plot->bindPGrid(*(PGrid *)(newTwoButton->object));
    connect(newTwoButton, SIGNAL(click()), signMaper, SLOT(map()));
    signMaper->setMapping(newTwoButton,newTwoButton);
    vblMain->addWidget(newTwoButton);
    vblMain->addLayout(bottomLayout);
    *(PGrid *)(newTwoButton->object) =
            GridDialog::getGrid(plot->getBackgroundColor(),*((PGrid *)(newTwoButton->object)));
}
