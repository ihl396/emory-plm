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
    octaveinvoker.cpp

HEADERS  += \
    qcustomplot.h \
    mainwindow.h \
    csvreader.h \
    datastructure.h \
    graphviewer.h \
    graph.h \
    markup.h \
    octaveinvoker.h

FORMS    += \
    mainwindow.ui

RESOURCES += \
    myresources.qrc

DISTFILES += \
    plm_analyzer_model.qmodel \
    resources/toolbar/handTool.png

INCLUDEPATH += C:/Octave/Octave-4.2.0/include/octave-4.2.0/ # MAKE SURE THIS PATH EXISTS or change it to your system.
LIBS += -L"C:/Octave/Octave-4.2.0/lib/octave/4.2.0" -loctinterp
