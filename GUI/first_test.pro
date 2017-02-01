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
    markerpopup.cpp \
    labelpopup.cpp \
    editwindow.cpp \
    parameters.cpp

HEADERS  += mainwindow.h \
            qcustomplot.h \
    markerpopup.h \
    labelpopup.h \
    editwindow.h \
    parameters.h

FORMS    += mainwindow.ui \
    markerpopup.ui \
    labelpopup.ui \
    editwindow.ui \
    parameters.ui

RESOURCES += \
    myresources.qrc
