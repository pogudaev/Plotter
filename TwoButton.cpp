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

#include "TwoButton.h"

TwoButton::TwoButton(QWidget *parent) :
    QWidget(parent)
{
    object = 0;
    setting = new QPushButton(QString::fromUtf8("Настроить"));
    remove = new QPushButton(QString::fromUtf8("Удалить"));
    box = new QHBoxLayout();
    setLayout(box);
    box->setMargin(0);
    box->addWidget(setting);
    box->addWidget(remove);
    buttonID = NoneButton;
    connect(setting, SIGNAL(clicked()), this, SLOT(setting_on_click()));
    connect(remove, SIGNAL(clicked()), this, SLOT(remove_on_click()));
}

TwoButton::~TwoButton()
{
    delete setting;
    delete remove;
    delete box;
    if (object) delete object;
}


ButtonID TwoButton::getButtonID()
{
    return buttonID;
}

void TwoButton::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TwoButton::setting_on_click()
{
    buttonID = SettingButton;
    emit click();
}

void TwoButton::remove_on_click()
{
    buttonID = RemoveButton;
    emit click();
}
