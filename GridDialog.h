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

#ifndef GRIDDIALOG_H
#define GRIDDIALOG_H

#include <QWidget>
#include <QDialog>
#include "PGrid.h"
#include "PenDialog.h"

namespace Ui {
class GridDialog;
}

class GridDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GridDialog(QWidget *parent = 0);
    ~GridDialog();
    static PGrid getGrid(QColor background,
                         PGrid defaultGrid = PGrid(QPen(Qt::gray,
                                                        1,Qt::DashLine,
                                                        Qt::RoundCap,
                                                        Qt::RoundJoin),
                                                   infinity,
                                                   Qt::Vertical),
                         QWidget *parent = 0,
                         QString title = QString::fromUtf8("Настройка сетки..."));


private slots:
    void on_lineButton_clicked();

    void on_directionBox_activated(int index);

    void on_stepBox_valueChanged(double arg1);

    void on_cancelButton_clicked();

    void on_okButton_clicked();

private:
    void setOutputGrid(PGrid &grid);
    void setStateValue(bool &state);
    void setBackground(QColor background);

    bool *state;
    QColor background;
    PGrid *outputGrid;


    Ui::GridDialog *ui;
};

#endif // GRIDDIALOG_H
