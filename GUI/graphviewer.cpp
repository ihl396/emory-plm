#include "graphviewer.h"

GraphViewer::GraphViewer(Ui::MainWindow *input) {
    first_time = true;
    main_window_ui = input;
}

void GraphViewer::createGraph(QVector<double> time_values, QVector<double> x_acc_values, QVector<double> y_acc_values, QVector<double> z_acc_values) {

    if (first_time) {
        main_window_ui->customPlot->addGraph();
        main_window_ui->customPlot->addGraph();
        main_window_ui->customPlot->addGraph();
        first_time = false;
    }

    main_window_ui->customPlot->legend->setVisible(true);
    main_window_ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);
    main_window_ui->customPlot->graph(0)->setData(time_values, x_acc_values);
    main_window_ui->customPlot->graph(0)->setName("X Acceleration");
    main_window_ui->customPlot->graph(1)->setData(time_values, y_acc_values);
    main_window_ui->customPlot->graph(1)->setPen(QPen(Qt::red));
    main_window_ui->customPlot->graph(1)->setName("Y Acceleration");
    main_window_ui->customPlot->graph(2)->setData(time_values, z_acc_values);
    main_window_ui->customPlot->graph(2)->setPen(QPen(Qt::green));
    main_window_ui->customPlot->graph(2)->setName("Z Acceleration");

    main_window_ui->customPlot->xAxis->setLabel("time (milliseconds)");
    main_window_ui->customPlot->yAxis->setLabel("acceleration (g's)");

    main_window_ui->customPlot->xAxis->setRange(0, time_values.back() + time_values.back()/20);
    main_window_ui->customPlot->yAxis->setRange(-2, 2);
    main_window_ui->customPlot->replot();
}

void GraphViewer::setFirstTime(bool input) {
    first_time = input;
}
