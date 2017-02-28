#include "mainwindow.h"
#include "datastructure.h"
#include "csvreader.h"
#include "graphviewer.h"

#include <QDir>
#include <QFileDialog>

#include <QString>
#include <QDebug>


#include <iostream>
#include <iomanip>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    ui->setupUi(this);
    firstRun = true;

    createActions();
    createMenus();
    setWindowTitle(tr("PLM Analyser"));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions() {
    openAct = new QAction(tr("&Open Raw Data File"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open a file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
}

void MainWindow::open()
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
