#-------------------------------------------------
#
# Project created by QtCreator 2015-04-26T00:13:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += printsupport

TARGET = Image-Analysis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mylabel.cpp \
    dlgimage.cpp \
    qcustomplot.cpp \
    imageprocessor.cpp

HEADERS  += mainwindow.h \
    dlgimage.h \
    mylabel.h \
    qcustomplot.h \
    imageprocessor.h

FORMS    += mainwindow.ui \
    dlgimage.ui
