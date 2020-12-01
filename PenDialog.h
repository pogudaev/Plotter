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

#ifndef PENDIALOG_H
#define PENDIALOG_H

#include <QWidget>
#include <QPen>
#include <QString>
#include <QDialog>
#include <QDebug>

namespace Ui {
class PenDialog;
}

class PenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PenDialog(QWidget *parent = 0);
    static QPen getPen(QColor background, QWidget *parent = 0,
                       QString title = QString::fromUtf8("Установка линии"),
                       QPen defaultPen = QPen(Qt::black,2,Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    ~PenDialog();

private slots:
    void on_typeBox_activated(int index);

    void on_colorChoiser_hasChange();

    void on_widthBox_valueChanged(double arg1);

    void on_cutBox_activated(int index);

    void on_cancelButton_clicked();

    void on_okButton_clicked();

protected:
    Ui::PenDialog *ui;


private:
    void setOutputPen(QPen &pen);
    void setStateValue(bool &state);
    void setBackground(QColor background);

    bool *state;

    QPen *outputPen;
};

#endif // PENDIALOG_H
