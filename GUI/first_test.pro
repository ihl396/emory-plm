#-------------------------------------------------
#
# Project created by QtCreator 2016-10-29T21:21:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = first_test
TEMPLATE = app


SOURCES += main.cpp\
    qcustomplot.cpp \
    mainwindow.cpp \
    csvreader.cpp \
    graphviewer.cpp

HEADERS  += \
    qcustomplot.h \
    mainwindow.h \
    csvreader.h \
    datastructure.h \
    graphviewer.h

FORMS    += \
    mainwindow.ui

RESOURCES += \
    myresources.qrc
