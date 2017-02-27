#ifndef GRAPHVIEWER_H
#define GRAPHVIEWER_H

#include <QVector>
#include <QDialog>
#include <QPen>
#include <ui_mainwindow.h>

class GraphViewer {

    Ui::MainWindow *main_window_ui;
    bool first_time;
public:
    GraphViewer(Ui::MainWindow *ui);
    void createGraph(QVector<double>, QVector<double>, QVector<double>, QVector<double>);
    void setFirstTime(bool);
};

#endif // GRAPHVIEWER_H
