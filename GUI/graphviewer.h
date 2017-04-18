#ifndef GRAPHVIEWER_H
#define GRAPHVIEWER_H

#include <QVector>
#include <QDialog>
#include <QPen>
#include <ui_mainwindow.h>
#include "setupwindow.h"
#include "mainwindow.h"

class GraphViewer {

    Ui::MainWindow *main_window_ui;
    class SetupWindow *setupWindow_ui;
    bool first_time;
public:
    GraphViewer(Ui::MainWindow *ui = 0, SetupWindow *sWin = 0);
    void createGraph(QVector<double>, QVector<double>, QVector<double>, QVector<double>, QVector<double>);
    void setFirstTime(bool);
    double getGraphKeyMin();
    double getGraphKeyMax();
    double getGraphKeyUpper();
    double getGraphValueMin();
    double getGraphValueMax();
    void setGraphKeyMin(double);
    void setGraphKeyMax(double);
    void setGraphValueMin(double);
    void setGraphValueMax(double);
    //void setCustomPlotChanges();
    void setGraphRanges(int keyScale, int valueMin, int valueMax);

    double graphKeyMin;
    double graphKeyMax;
    double graphKeyUpper;
    int graphKeyScale;
    double graphValueMin;
    double graphValueMax;
private slots:
    void on_toolButton_triggered(QAction *arg1);
    void on_toolButton_2_triggered(QAction *arg1);
    void on_toolButton_clicked();
    void on_toolButton_2_clicked();
};

#endif // GRAPHVIEWER_H
