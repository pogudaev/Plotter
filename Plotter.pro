
QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Plotter
TEMPLATE = app


SOURCES += main.cpp \
    PlotterDemo.cpp \
    Head.cpp \
    Body.cpp \
    ResizeButton.cpp \
    ColorButton.cpp \
    PenDialog.cpp \
    LineView.cpp \
    AdderSomeThings.cpp \
    TwoButton.cpp \
    SettingPanel.cpp \
    PPlot.cpp \
    PSignature.cpp \
    PCurve.cpp \
    PCanvas.cpp \
    PGrid.cpp \
    AdderPGrid.cpp \
    GridDialog.cpp \
    AdderPCurve.cpp \
    Sensor.cpp

HEADERS  += \
    PlotterDemo.h \
    Head.h \
    Body.h \
    ResizeButton.h \
    ColorButton.h \
    PenDialog.h \
    LineView.h \
    AdderSomeThings.h \
    TwoButton.h \
    SettingPanel.h \
    PPlot.h \
    PSignature.h \
    PCurve.h \
    PCanvas.h \
    PGrid.h \
    AdderPGrid.h \
    GridDialog.h \
    AdderPCurve.h \
    Sensor.h

FORMS    += \
    PlotterDemo.ui \
    PenDialog.ui \
    SettingPanel.ui \
    GridDialog.ui

RESOURCES += \
    Resource.qrc

OTHER_FILES += \
    mainStyle.qss \
    Head.qss \
    index.html
