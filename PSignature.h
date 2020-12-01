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

#ifndef PSIGNATURE_H
#define PSIGNATURE_H

#include <QObject>
#include <QPainter>
#include "PCanvas.h"
#include <QPicture>

class PSignature : public QObject
{
    Q_OBJECT
public:
    explicit PSignature(QObject *parent = 0);
    PSignature(PSignature const &signature);
    ~PSignature();
    void setMinimalStep(qreal minStep);
    qreal getMinStep();
    void setBackground(QColor bgcolor);
    void setTextColor(QColor textColor);
    QColor getTextColor();
    QColor getBackground();
    void setOrientation(Qt::Orientation orient);
    Qt::Orientation getOrientation();
    QPicture getPicture(PCanvas *canvas);

private:
    qreal minimalStep;
    QColor textColor;
    QColor backgroundColor;
    Qt::Orientation orientation;
    void helperRenderFunction(QPainter &pntr, qreal value, QPointF &coord);

signals:

    void hasChange();

public slots:

};

#endif // PSIGNATURE_H
