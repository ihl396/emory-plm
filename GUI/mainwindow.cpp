#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datastructure.h"
#include "csvreader.h"
//#include "markerpopup.h"

#include <QLCDNumber>
#include <QObject>
#include <QTimer>

#include <QMessageBox>
#include <QTextStream>
#include <QList>
#include <QStringList>
#include <QDir>
#include <Qstring>
#include <QFileDialog>

#include <QKeyEvent>
#include <QList>
#include <QString>
#include <QDir>
#include <QFile>
#include <QDebug>


#include <iostream>
#include <iomanip>


MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    firstRun = true;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"),"C://","all files (*.*)");
}

void MainWindow::on_pushButton_2_clicked()
{
    QString filename2 = QFileDialog::getOpenFileName(this,tr("Open File"),"C://","Octave/MATLAB scripts (*.m);;all files (*.*)");
}

void MainWindow::on_pushButton_3_clicked()
{
    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);
    QString csv_file = QFileDialog::getOpenFileName(this,tr("Open File"),QDir::currentPath(),"CSV files (*.csv);;all files (*.*)");

    struct DataStructure data_structure;

    CsvReader csvReader(model);
    csvReader.importCSV(csv_file);
    data_structure = csvReader.exportData(data_structure);


    createGraph(data_structure.time_values, data_structure.x_acc_values, data_structure.y_acc_values, data_structure.z_acc_values, firstRun);
    firstRun = false;
}

void MainWindow::createGraph(QVector<double> timeStamp,QVector<double> xAccValues,QVector<double> yAccValues,QVector<double> zAccValues, bool firstRun)
{
    if (firstRun) {
        ui->customPlot->addGraph();
        ui->customPlot->addGraph();
        ui->customPlot->addGraph();
    }

    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);
    ui->customPlot->graph(0)->setData(timeStamp, xAccValues);
    ui->customPlot->graph(0)->setName("X Acceleration");
    ui->customPlot->graph(1)->setData(timeStamp, yAccValues);
    ui->customPlot->graph(1)->setPen(QPen(Qt::red));
    ui->customPlot->graph(1)->setName("Y Acceleration");
    ui->customPlot->graph(2)->setData(timeStamp, zAccValues);
    ui->customPlot->graph(2)->setPen(QPen(Qt::green));
    ui->customPlot->graph(2)->setName("Z Acceleration");

    ui->customPlot->xAxis->setLabel("time (milliseconds)");
    ui->customPlot->yAxis->setLabel("acceleration (g's)");

    ui->customPlot->xAxis->setRange(0, timeStamp.back() + timeStamp.back()/20);
    ui->customPlot->yAxis->setRange(-2, 2);
    ui->customPlot->replot();
}
