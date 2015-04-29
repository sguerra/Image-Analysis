#-------------------------------------------------
#
# Project created by QtCreator 2015-04-26T00:13:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Image-Analysis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mylabel.cpp \
    dlgimage.cpp

HEADERS  += mainwindow.h \
    dlgimage.h \
    mylabel.h

FORMS    += mainwindow.ui \
    dlgimage.ui
