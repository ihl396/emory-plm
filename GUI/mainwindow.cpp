#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datastructure.h"
#include "csvreader.h"
#include "graphviewer.h"

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

    GraphViewer graphViewer(ui);

    graphViewer.setFirstTime(firstRun);
    graphViewer.createGraph(data_structure.time_values, data_structure.x_acc_values, data_structure.y_acc_values, data_structure.z_acc_values);
    firstRun = false;
}
