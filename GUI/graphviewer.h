#ifndef GRAPHVIEWER_H
#define GRAPHVIEWER_H

#include <QVector>
#include <QDialog>
#include <QPen>
#include <ui_mainwindow.h>

class GraphViewer {

    Ui::MainWindow *main_window_ui;
    bool first_time;
    bool axis_graphs;
public:
    GraphViewer(Ui::MainWindow *ui);
    void createGraph(QVector<double>, QVector<double>, QVector<double>, QVector<double>, QVector<double>);
    void setFirstTime(bool);
    void axisGraphs();
private slots:
    void on_toolButton_triggered(QAction *arg1);
    void on_toolButton_2_triggered(QAction *arg1);
    void on_toolButton_clicked();
    void on_toolButton_2_clicked();
};

#endif // GRAPHVIEWER_H
