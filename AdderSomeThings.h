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

#ifndef ADDERSOMETHINGS_H
#define ADDERSOMETHINGS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QVector>
#include <QSignalMapper>
#include "TwoButton.h"
#include "PPlot.h"


class AdderSomeThings : public QWidget
{
    Q_OBJECT
public:
    explicit AdderSomeThings(QWidget *parent = 0);
    virtual ~AdderSomeThings();
    void setPPlot(PPlot *plot);


private:

protected:
    QVector<TwoButton *> buttons;
    QSignalMapper *signMaper;
    QVBoxLayout *vblMain;
    QHBoxLayout *bottomLayout;
    QPushButton *addButton;
    PPlot *plot;

signals:

private slots:
    virtual void clickBox(QWidget *wdg);
    virtual void callAdd();



};

#endif // ADDERSOMETHINGS_H
