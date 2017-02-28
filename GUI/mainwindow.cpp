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

    viewSelectionAction = new QAction("View Selection");
    viewSelectionAction->setShortcut(tr("Ctrl+V"));
    viewSelectionAction->setStatusTip(tr("Open a file"));

    undoViewSelectedAction = new QAction("Undo View Selected");
    undoViewSelectedAction->setShortcut(tr("Ctrl+U"));
    undoViewSelectedAction->setStatusTip(tr("Open a file"));

    rescaleViewAction = new QAction("Rescale View");
    rescaleViewAction->setShortcut(tr("Ctrl+R"));
    rescaleViewAction->setStatusTip(tr("Open a file"));

    cancelAction = new QAction("Cancel");
    cancelAction->setShortcut(tr("Ctrl+C"));
    cancelAction->setStatusTip(tr("Open a file"));
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);

    //toolMenu = new QToolBar("Toolbar", ui->toolBar);
    //toolMenu->addAction(openAct);
    connect(ui->customPlot, SIGNAL(rightMousePress(QMouseEvent*)), this, SLOT(rightMousePress())); /// might need to place this somewhere else
    rightClickMenu = new QMenu(ui->customPlot);
    rightClickMenu->addAction(viewSelectionAction);
    rightClickMenu->addAction(undoViewSelectedAction);
    rightClickMenu->addAction(rescaleViewAction);
    rightClickMenu->addAction(cancelAction);


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

/* RIGHT CLICK EVENT and RECTANGLE SCALING*/
void MainWindow::showRightClickMenu(const QPoint& pos) // this is a slot
{
    QPoint globalPos = ui->customPlot->mapToGlobal(pos);

    selection = ui->customPlot->graph(0)->selection();

    // Checks for no selection and hides options
    if (selection.dataPointCount() == 0)
    {
        viewSelectionAction->setEnabled(false);
        undoViewSelectedAction->setEnabled(false);
    }

    selectedItem = rightClickMenu->exec(globalPos);
    if (selectedItem)
    {
        if (selectedItem->text().contains("View Selection"))
        {
            // something was chosen, do stuff
            //ui->customPlot->setSelectionRectMode(QCP::srmZoom);
            //ui->customPlot->graph(0)->setSelectable(QCP::stDataRange);

            QVector<QCPGraphData> selectedData(selection.dataPointCount()); /// creates an empty QVector<QCPGraphData> array with the size of the data selection points
            //QCPGraphData test = selectedData[0];
            qDebug() << selection.dataRanges();
            QCPGraphDataContainer::const_iterator begin;
            QCPGraphDataContainer::const_iterator end;
            foreach (QCPDataRange dataRange, selection.dataRanges())
            {
                qDebug() << "Data was selected";
                QCPGraphDataContainer::const_iterator beginloop = ui->customPlot->graph()->data()->at(dataRange.begin()); // get range begin iterator from index
                QCPGraphDataContainer::const_iterator endloop = ui->customPlot->graph()->data()->at(dataRange.end()); // get range end iterator from index
                begin = beginloop;
                end = endloop;
                int j =0;
                for (QCPGraphDataContainer::const_iterator it=begin; it!=end; ++it)
                {
                    // iterator "it" will go through all selected data points
                    qDebug() << it->key;
                    selectedData[j].key = it->key;
                    selectedData[j].value = it->value;
                    j++;

                }
                double xAxisLowerBound = selectedData[0].key;
                double xAxisUpperBound = selectedData[selectedData.length()-1].key;
                //double yAxisLowerBound = selectedData[0].value;
                //double yAxisUpperBound = selectedData[selectedData.length()-1].value;
                ui->customPlot->xAxis->setRange(xAxisLowerBound,xAxisUpperBound);
                ui->customPlot->yAxis->setRange(-2, 2);
                ui->customPlot->replot();
            }
        }
        else if (selectedItem->text().contains("Undo View Selected"))
        {

        }
        else if (selectedItem->text().contains("Rescale View"))
        {
            ui->customPlot->rescaleAxes(true);
        }
    }
    else
    {
        // nothing was chosen
    }
}

void MainWindow::rightMousePress()
{
    const QPoint cursorLoc = ui->customPlot->mapFromGlobal(QCursor::pos());
    emit showRightClickMenu(cursorLoc);
}
