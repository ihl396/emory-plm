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
    graphviewer.cpp \
    graph.cpp \
    markup.cpp \
    setupwindow.cpp

HEADERS  += \
    qcustomplot.h \
    mainwindow.h \
    csvreader.h \
    datastructure.h \
    graphviewer.h \
    graph.h \
    markup.h \
    setupwindow.h

FORMS    += \
    mainwindow.ui \
    setupwindow.ui

RESOURCES += \
    myresources.qrc

DISTFILES += \
    plm_analyzer_model.qmodel \
    resources/toolbar/handTool.png
