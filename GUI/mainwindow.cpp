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
    openAct = new QAction(QIcon(":/resources/toolbar/openRawDataFile.png"), tr("&Open Raw Data File"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open a file"));
    saveAct = new QAction(QIcon(":/resources/toolbar/saveFile.png"), tr("&Save File"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save a file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    /// connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    // Tool Button Actions
    handToolAct = new QAction(QIcon(":/resources/toolbar/handTool.png"), tr("Hand Tool"), this);
    markerToolAct = new QAction(QIcon(":/resources/toolbar/markerTool.png"), tr("Marker Tool"), this);
    labelToolAct = new QAction(QIcon(":/resources/toolbar/labelTool.png"), tr("Label Tool"), this);
    handToolAct->setCheckable(true);
    markerToolAct->setCheckable(true);
    labelToolAct->setCheckable(true);
    handToolAct->setShortcut(QKeySequence("Ctrl+H"));
    markerToolAct->setShortcut(QKeySequence("Ctrl+M"));
    labelToolAct->setShortcut(QKeySequence("Ctrl+L"));
    handToolAct->setStatusTip(tr("Hand Tool"));
    markerToolAct->setStatusTip(tr("Marker Tool"));
    labelToolAct->setStatusTip(tr("Label Tool"));


    // Right Click Actions
    viewSelectionAct = new QAction(tr("&View Selection"), this);
    viewSelectionAct->setShortcut(QKeySequence("CTRL+V"));
    viewSelectionAct->setStatusTip(tr("View Selection"));
    viewSelectionShortcut = new QShortcut(QKeySequence("CTRL+V"),this); /// Couldn't get the action shortcut to work, this works
    connect(viewSelectionAct, &QAction::triggered, this, &MainWindow::viewSelection);
    connect(viewSelectionShortcut, &QShortcut::activated, this, &MainWindow::viewSelection);

    undoViewSelectedAct = new QAction("Undo View Selected");
    undoViewSelectedAct->setShortcut(QKeySequence("Ctrl+U"));
    undoViewSelectedAct->setStatusTip(tr("Undo View Selected"));

    rescaleViewAct = new QAction(tr("&Rescale View"), this);
    rescaleViewAct->setShortcut(QKeySequence("CTRL+R"));
    rescaleViewAct->setStatusTip(tr("Rescale View"));
    rescaleViewShortcut = new QShortcut(QKeySequence("CTRL+R"),this); /// Couldn't get the action shortcut to work, this works
    connect(rescaleViewAct, &QAction::triggered, this, &MainWindow::rescaleView);
    connect(rescaleViewShortcut, &QShortcut::activated, this, &MainWindow::rescaleView);

    cancelAct = new QAction("Cancel");
    cancelAct->setShortcut(QKeySequence("Ctrl+C"));
    cancelAct->setStatusTip(tr("Cancel"));
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);

    // Toolbar Menu
    ui->toolBar->addAction(openAct);
    ui->toolBar->addAction(saveAct);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(handToolAct);//, "Hand Tool");
    ui->toolBar->addAction(markerToolAct);//, "Marker Tool");
    ui->toolBar->addAction(labelToolAct);//, "Label Tool");
    emit disableToolBar();
    connect(handToolAct, &QAction::triggered, this, &MainWindow::handToolTriggered);
    connect(markerToolAct, &QAction::triggered, this, &MainWindow::markerToolTriggered);
    connect(labelToolAct, &QAction::triggered, this, &MainWindow::labelToolTriggered);

    // Right Click Menu
    connect(ui->customPlot, SIGNAL(rightMousePress(QMouseEvent*)), this, SLOT(rightMousePress())); /// might need to place this somewhere else
    rightClickMenu = new QMenu(ui->customPlot);//new QMenu(ui->customPlot);
    //rightClickMenu->setContextMenuPolicy(Qt::ActionsContextMenu);
    rightClickMenu->addAction(viewSelectionAct);
    rightClickMenu->addAction(undoViewSelectedAct);
    rightClickMenu->addAction(rescaleViewAct);
    rightClickMenu->addAction(cancelAct);
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
    graphViewer.createGraph(data_structure.time_values, data_structure.x_acc_values, data_structure.y_acc_values, data_structure.z_acc_values, data_structure.magnitude_values);
    firstRun = false;
    // Defaults to Hand Tool when file is opened
    emit enableToolBar();
    emit handToolAct->trigger();
}

void MainWindow::save()
{

}

void MainWindow::enableToolBar()
{
    handToolAct->setEnabled(true);
    markerToolAct->setEnabled(true);
    labelToolAct->setEnabled(true);
    viewSelectionShortcut->setEnabled(true);
    rescaleViewShortcut->setEnabled(true);
}

void MainWindow::disableToolBar()
{
    handToolAct->setEnabled(false);
    markerToolAct->setEnabled(false);
    labelToolAct->setEnabled(false);
    viewSelectionShortcut->setEnabled(false);
    rescaleViewShortcut->setEnabled(false);
}

/* RIGHT CLICK EVENT and RECTANGLE SCALING*/
void MainWindow::rightMousePress()
{
    /// NEED TO ONLY ALLOW RIGHT CLICK WHEN A FILE IS LOADED
    if (!firstRun)
    {
        const QPoint cursorLoc = ui->customPlot->mapFromGlobal(QCursor::pos());
        emit showRightClickMenu(cursorLoc);
    }
}

void MainWindow::viewSelection()
{
    selection = ui->customPlot->graph(0)->selection();

    // Checks for selection
    if (selection.dataPointCount() != 0)
    {
        // creates an empty QVector<QCPGraphData> array with the size of the data selection points
        QVector<QCPGraphData> selectedData(selection.dataPointCount());
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
            /// Only takes into account of one graph
            double xAxisLowerBound = selectedData[0].key;
            double xAxisUpperBound = selectedData[selectedData.length()-1].key;
            //double yAxisLowerBound = selectedData[0].value;
            //double yAxisUpperBound = selectedData[selectedData.length()-1].value;
            ui->customPlot->xAxis->setRange(xAxisLowerBound,xAxisUpperBound);
            ui->customPlot->yAxis->setRange(-2, 2); /// make dynamic
            ui->customPlot->replot();
        }
    }
}

void MainWindow::rescaleView()
{
    /// FIGURE OUT WHY IT RESCALES IT TWICE
    ui->customPlot->rescaleAxes(true);
    ui->customPlot->replot();
    qDebug() << "Rescaled View";
}

void MainWindow::showRightClickMenu(const QPoint& pos) // this is a slot
{
    QPoint globalPos = ui->customPlot->mapToGlobal(pos);

    selection = ui->customPlot->graph(0)->selection();

    // Checks for no selection and hides options
    /// LOOK INTO STILL ENABLED WHEN NO SELECTION (MIGHT BE ONE DATA POINT SELECTED)
    if (selection.dataPointCount() == 0) /// Maybe set to == 0 || == 1?
    {
        viewSelectionAct->setEnabled(false);
        undoViewSelectedAct->setEnabled(false);
    }
    else
    {
        viewSelectionAct->setEnabled(true);
        undoViewSelectedAct->setEnabled(true);
    }

    selectedItem = rightClickMenu->exec(globalPos);
    if (selectedItem)
    {
        if (selectedItem->text().contains("View Selection"))
        {
            emit viewSelection();
        }
        else if (selectedItem->text().contains("Undo View Selected"))
        {

        }
        else if (selectedItem->text().contains("Rescale View"))
        {
            emit rescaleView();
        }
    }
    else
    {
        // nothing was chosen
    }
}

void MainWindow::handToolTriggered()
{
    if (handToolAct->isChecked() == true){
        markerToolAct->setChecked(false);
        labelToolAct->setChecked(false);
        emit markerToolTriggered();
        emit labelToolTriggered();
        qDebug() << "HandTool: toggled";
    }
    else{
        qDebug() << "HandTool: un-toggled";
    }
}

void MainWindow::markerToolTriggered()
{
    if (markerToolAct->isChecked() == true){
        handToolAct->setChecked(false);
        labelToolAct->setChecked(false);
        emit handToolTriggered();
        emit labelToolTriggered();
        qDebug() << "MarkerTool: toggled";

        ui->customPlot->setSelectionRectMode(QCP::srmSelect);
        ui->customPlot->graph(0)->setSelectable(QCP::stDataRange);
        ui->customPlot->graph(1)->setSelectable(QCP::stDataRange);
        ui->customPlot->graph(2)->setSelectable(QCP::stDataRange);//QCP::SelectionType(QCP::stDataRange)
    }
    else{
        qDebug() << "MarkerTool: un-toggled";

        ui->customPlot->setSelectionRectMode(QCP::srmNone);
        ui->customPlot->graph(0)->setSelectable(QCP::stNone);
        ui->customPlot->graph(1)->setSelectable(QCP::stNone);
        ui->customPlot->graph(2)->setSelectable(QCP::stNone);
    }
}

void MainWindow::labelToolTriggered()
{
    if (labelToolAct->isChecked() == true){
        handToolAct->setChecked(false);
        markerToolAct->setChecked(false);
        emit handToolTriggered();
        emit markerToolTriggered();
        qDebug() << "LabelTool: toggled";
    }
    else{
        qDebug() << "LabelTool: un-toggled";
    }
}
