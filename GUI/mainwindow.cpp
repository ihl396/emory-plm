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
    handToolAct->setShortcut(QKeySequence("H"));
    markerToolAct->setShortcut(QKeySequence("M"));
    labelToolAct->setShortcut(QKeySequence("L"));
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

    labelSelectionAct = new QAction(tr("&Label Selection"), this);
    labelSelectionAct->setShortcut(QKeySequence("CTRL+L"));
    labelSelectionAct->setStatusTip(tr("Label Selection"));
    labelSelectionShortcut = new QShortcut(QKeySequence("CTRL+L"),this); /// Couldn't get the action shortcut to work, this works
    //connect(labelSelectionAct, &QAction::triggered, this, &MainWindow::);
    //connect(labelSelectionShortcut, &QShortcut::activated, this, &MainWindow::);

    // Add Marker Actions
    addUpMarker = new QAction(tr("&Up Marker"), this);
    addUpMarker->setShortcut(QKeySequence("CTRL+U"));
    addUpMarker->setStatusTip(tr("Up Marker"));
    //addUpMarkerShortcut = new QShortcut(QKeySequence("CTRL+R"),this); /// Couldn't get the action shortcut to work, this works
    //connect(addUpMarker, &QAction::triggered, this, &MainWindow::);
    //connect(addUpMarkerShortcut, &QShortcut::activated, this, &MainWindow::);

    addDownMarker = new QAction(tr("&Down Marker"), this);
    addDownMarker->setShortcut(QKeySequence("CTRL+D"));
    addDownMarker->setStatusTip(tr("Down Marker"));
    //addDownMarkerShortcut = new QShortcut(QKeySequence("CTRL+R"),this); /// Couldn't get the action shortcut to work, this works
    //connect(addDownMarker, &QAction::triggered, this, &MainWindow::);
    //connect(addDownMarkerShortcut, &QShortcut::activated, this, &MainWindow::);

    addPMarker = new QAction(tr("&P Marker"), this);
    addPMarker->setShortcut(QKeySequence("CTRL+P"));
    addPMarker->setStatusTip(tr("P Marker"));
    //addPMarkerShortcut = new QShortcut(QKeySequence("CTRL+R"),this); /// Couldn't get the action shortcut to work, this works
    //connect(addPMarker, &QAction::triggered, this, &MainWindow::);
    //connect(addPMarkerShortcut, &QShortcut::activated, this, &MainWindow::);

    addRMarker = new QAction(tr("&R Marker"), this);
    addRMarker->setShortcut(QKeySequence("CTRL+R"));
    addRMarker->setStatusTip(tr("R Marker"));
    //addRMarkerShortcut = new QShortcut(QKeySequence("CTRL+R"),this); /// Couldn't get the action shortcut to work, this works
    //connect(addRMarker, &QAction::triggered, this, &MainWindow::);
    //connect(addRMarkerShortcut, &QShortcut::activated, this, &MainWindow::);

    addKMarker = new QAction(tr("&K Marker"), this);
    addKMarker->setShortcut(QKeySequence("CTRL+K"));
    addKMarker->setStatusTip(tr("K Marker"));
    //addKMarkerShortcut = new QShortcut(QKeySequence("CTRL+R"),this); /// Couldn't get the action shortcut to work, this works
    //connect(addKMarker, &QAction::triggered, this, &MainWindow::);
    //connect(addKMarkerShortcut, &QShortcut::activated, this, &MainWindow::);

    addIMarker = new QAction(tr("&I Marker"), this);
    addIMarker->setShortcut(QKeySequence("CTRL+I"));
    addIMarker->setStatusTip(tr("I Marker"));
    //addIMarkerShortcut = new QShortcut(QKeySequence("CTRL+R"),this); /// Couldn't get the action shortcut to work, this works
    //connect(addIMarker, &QAction::triggered, this, &MainWindow::);
    //connect(addIMarkerShortcut, &QShortcut::activated, this, &MainWindow::);

    rescaleViewAct = new QAction(tr("&Rescale View"), this);
    rescaleViewAct->setShortcut(QKeySequence("CTRL+SHIFT+R"));
    rescaleViewAct->setStatusTip(tr("Rescale View"));
    rescaleViewShortcut = new QShortcut(QKeySequence("CTRL+SHIFT+R"),this); /// Couldn't get the action shortcut to work, this works
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
    // Add Marker Menu
    addMarkerMenu = new QMenu("Add Marker");
    addMarkerMenu->setStatusTip(tr("Add Marker"));
    //rightClickMenu->setContextMenuPolicy(Qt::ActionsContextMenu);
    rightClickMenu->addAction(viewSelectionAct);
    rightClickMenu->addAction(labelSelectionAct);
    rightClickMenu->addMenu(addMarkerMenu);
    addMarkerMenu->addAction(addUpMarker);
    addMarkerMenu->addAction(addDownMarker);
    addMarkerMenu->addAction(addPMarker);
    addMarkerMenu->addAction(addRMarker);
    addMarkerMenu->addAction(addKMarker);
    addMarkerMenu->addAction(addIMarker);
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

void MainWindow::setMinMax(QList<double> keys, QList<double> values) {
    if (firstSelectionCheck)
    {
        xAxisKeyMin = *keys.begin();
        xAxisKeyMax = *(keys.end()-1);
        xAxisValueMin = *min_element(values.begin(), values.end()-1);
        xAxisValueMax = *max_element(values.begin(), values.end());
    }
    else
    {
        xAxisKeyMin = min(*keys.begin(), xAxisKeyMin);
        xAxisKeyMax = max(*(keys.end()-1), xAxisKeyMax);
        xAxisValueMin = min(*min_element(values.begin(), values.end()-1), xAxisValueMin);
        xAxisValueMax = max(*max_element(values.begin(), values.end()-1), xAxisValueMax);
    }
}

void MainWindow::getSelectionValues(QCPDataSelection selection, int graphNum)
{
    // creates an empty QVector<QCPGraphData> array with the size of the data selection points
    QList<double> selectedKeyData; //= new QList(double);//(selection.dataPointCount());
    QList<double> selectedValueData; //= new QList(double);//(selection.dataPointCount());
    //qDebug() << xGraphSelection.dataRanges();
    QCPGraphDataContainer::const_iterator begin;
    QCPGraphDataContainer::const_iterator end;
    foreach (QCPDataRange dataRange, selection.dataRanges())
    {
        qDebug() << "Data was selected";
        QCPGraphDataContainer::const_iterator beginloop = ui->customPlot->graph(graphNum)->data()->at(dataRange.begin()); // get range begin iterator from index
        QCPGraphDataContainer::const_iterator endloop = ui->customPlot->graph(graphNum)->data()->at(dataRange.end()); // get range end iterator from index
        begin = beginloop;
        end = endloop;
        int j =0;
        selectedKeyData.clear();
        selectedValueData.clear();
        for (QCPGraphDataContainer::const_iterator it=begin; it!=end; ++it)
        {
            // iterator "it" will go through all selected data points
            selectedKeyData.append(it->key);
            selectedValueData.append(it->value);
            j++;
        }
        /// Could just hard code min and max to set parameters. But this is dynamic.
        emit setMinMax(selectedKeyData, selectedValueData);
        firstSelectionCheck = false;
    }
}

void MainWindow::viewSelection()
{
    xGraphSelection = ui->customPlot->graph(0)->selection();
    yGraphSelection = ui->customPlot->graph(1)->selection();
    zGraphSelection = ui->customPlot->graph(2)->selection();
    nGraphSelection = ui->customPlot->graph(3)->selection();

    firstSelectionCheck = true;
    // Checks for selection
    if (xGraphSelection.dataPointCount() != 0)
    {
        emit getSelectionValues(xGraphSelection, 0);
    }

    if (yGraphSelection.dataPointCount() != 0)
    {
        emit getSelectionValues(yGraphSelection, 1);
    }

    if (zGraphSelection.dataPointCount() != 0)
    {
        emit getSelectionValues(zGraphSelection, 2);
    }

    if (nGraphSelection.dataPointCount() != 0)
    {
        emit getSelectionValues(nGraphSelection, 3);
    }
    ui->customPlot->xAxis->setRange(xAxisKeyMin,xAxisKeyMax);
    ui->customPlot->yAxis->setRange(floor(xAxisValueMin), ceil(xAxisValueMax)); /// make dynamic
    ui->customPlot->replot();
    xGraphSelection.clear();
}

void MainWindow::labelSelection()
{
    xGraphSelection = ui->customPlot->graph(0)->selection();
    yGraphSelection = ui->customPlot->graph(1)->selection();
    zGraphSelection = ui->customPlot->graph(2)->selection();
    nGraphSelection = ui->customPlot->graph(3)->selection();

    firstSelectionCheck = true;
    // Checks for selection
    if (xGraphSelection.dataPointCount() != 0)
    {
        /// Possibly create enum for the graph numbers
        emit getSelectionValues(xGraphSelection, 0);
    }

    if (yGraphSelection.dataPointCount() != 0)
    {
        emit getSelectionValues(yGraphSelection, 1);
    }

    if (zGraphSelection.dataPointCount() != 0)
    {
        emit getSelectionValues(zGraphSelection, 2);
    }

    if (nGraphSelection.dataPointCount() != 0)
    {
        emit getSelectionValues(nGraphSelection, 3);
    }
    labelRect = new QCPItemRect(ui->customPlot);
    //QString redstr = popupData[0];QString greenstr = popupData[1];QString bluestr = popupData[2];
    //int red = redstr.toInt();int green = greenstr.toInt();int blue = bluestr.toInt();
    //labelRect->setBrush(QColor(red, green, blue, 75));
    //labelRect->setPen(QColor(red,green,blue, 75));
    labelRect->setBrush(QColor(225, 0, 0, 75));
    labelRect->setPen(QColor(225, 0, 0, 75));
    labelRect->setSelected(false);

    labelRect->topLeft->setCoords(xAxisKeyMin, floor(xAxisValueMin));
    labelRect->bottomRight->setCoords(xAxisKeyMax, ceil(xAxisValueMax));
    xGraphSelection.clear();
}

void MainWindow::rescaleView()
{
    /// FIGURE OUT WHY IT RESCALES IT TWICE
    ui->customPlot->rescaleAxes(true);
    ui->customPlot->replot();
    xGraphSelection.clear(); // Need this?
    qDebug() << "Rescaled View";
}

void MainWindow::showRightClickMenu(const QPoint& pos) // this is a slot
{
    QPoint globalPos = ui->customPlot->mapToGlobal(pos);

    xGraphSelection = ui->customPlot->graph(0)->selection();

    // Checks for no selection and hides options
    /// LOOK INTO STILL ENABLED WHEN NO SELECTION (MIGHT BE ONE DATA POINT SELECTED)
    if (xGraphSelection.dataPointCount() == 0) /// Maybe set to == 0 || == 1?
    {
        viewSelectionAct->setEnabled(false);
        labelSelectionAct->setEnabled(false);
    }
    else
    {
        viewSelectionAct->setEnabled(true);
        labelSelectionAct->setEnabled(true);
    }

    selectedItem = rightClickMenu->exec(globalPos);
    if (selectedItem)
    {
        if (selectedItem->text().contains("View Selection"))
        {
            emit viewSelection();
        }
        else if (selectedItem->text().contains("Label Selection"))
        {
            emit labelSelection();
        }
        else if (selectedItem->text().contains("Up Marker"))
        {

        }
        else if (selectedItem->text().contains("Down Marker"))
        {

        }
        else if (selectedItem->text().contains("P Marker"))
        {

        }
        else if (selectedItem->text().contains("R Marker"))
        {

        }
        else if (selectedItem->text().contains("K Marker"))
        {

        }
        else if (selectedItem->text().contains("I Marker"))
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
        ui->customPlot->graph(2)->setSelectable(QCP::stDataRange);
        ui->customPlot->graph(3)->setSelectable(QCP::stDataRange);//QCP::SelectionType(QCP::stDataRange)
    }
    else{
        qDebug() << "MarkerTool: un-toggled";

        ui->customPlot->setSelectionRectMode(QCP::srmNone);
        ui->customPlot->graph(0)->setSelectable(QCP::stNone);
        ui->customPlot->graph(1)->setSelectable(QCP::stNone);
        ui->customPlot->graph(2)->setSelectable(QCP::stNone);
        ui->customPlot->graph(3)->setSelectable(QCP::stNone);
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
