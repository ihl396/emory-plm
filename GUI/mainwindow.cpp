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
    addMarkerClicked = false;

    createActions();
    createMenus();
    createMarkerPixmaps();
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
    connect(labelSelectionAct, &QAction::triggered, this, &MainWindow::labelSelection);
    connect(labelSelectionShortcut, &QShortcut::activated, this, &MainWindow::labelSelection);

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

void MainWindow::createMarkerPixmaps()
{
    // Add Marker Pixmaps
    //const QPoint cursorLoc = ui->customPlot->mapFromGlobal(QCursor::pos());
    //QPoint globalPos = ui->customPlot->mapToGlobal(cursorLoc);
    upPix = new QPixmap(":/resources/toolbar/UPMarker.png");
    /// Still need to find a way to make transparent
    //upPix->fill(Qt::transparent);
    //QPainter painter(upPix);
    //painter.drawPixmap(globalPos, upPix->scaled(50,50,Qt::KeepAspectRatio));

    downPix = new QPixmap(":/resources/toolbar/DMarker.png");

    pPix = new QPixmap(":/resources/toolbar/PMarker.png");

    rPix = new QPixmap(":/resources/toolbar/RMarker.png");

    kPix = new QPixmap(":/resources/toolbar/KMarker.png");

    iPix = new QPixmap(":/resources/toolbar/IMarker.png");
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
    labelSelectionShortcut->setEnabled(true);
    rescaleViewShortcut->setEnabled(true);
}

void MainWindow::disableToolBar()
{
    handToolAct->setEnabled(false);
    markerToolAct->setEnabled(false);
    labelToolAct->setEnabled(false);
    viewSelectionShortcut->setEnabled(false);
    labelSelectionShortcut->setEnabled(false);
    rescaleViewShortcut->setEnabled(false);
}

/* RIGHT CLICK EVENT and RECTANGLE SCALING*/
void MainWindow::rightMousePress()
{
    if (!firstRun)
    {
        const QPoint cursorLoc = ui->customPlot->mapFromGlobal(QCursor::pos());
        qDebug() << cursorLoc;
        qDebug() << cursorLoc.x();
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

void MainWindow::getSelectionValues()//QCPDataSelection selection, int graphNum)
{
    xGraphSelection = ui->customPlot->graph(0)->selection();
    yGraphSelection = ui->customPlot->graph(1)->selection();
    zGraphSelection = ui->customPlot->graph(2)->selection();
    nGraphSelection = ui->customPlot->graph(3)->selection();
    QVector<QCPDataSelection> selectionArray(4);
    selectionArray[0] = xGraphSelection;
    selectionArray[1] = yGraphSelection;
    selectionArray[2] = zGraphSelection;
    selectionArray[3] = nGraphSelection;
    firstSelectionCheck = true;
    for (int i = 0; i < selectionArray.length(); i++)
    {
        // Checks for selection
        if (selectionArray[i].dataPointCount() != 0)
        {
            // creates an empty QVector<QCPGraphData> array with the size of the data selection points
            QList<double> selectedKeyData; //= new QList(double);//(selection.dataPointCount());
            QList<double> selectedValueData; //= new QList(double);//(selection.dataPointCount());
            //qDebug() << xGraphSelection.dataRanges();
            QCPGraphDataContainer::const_iterator begin;
            QCPGraphDataContainer::const_iterator end;
            foreach (QCPDataRange dataRange, selectionArray[i].dataRanges())
            {
                qDebug() << "Data was selected";
                QCPGraphDataContainer::const_iterator beginloop = ui->customPlot->graph(i)->data()->at(dataRange.begin()); // get range begin iterator from index
                QCPGraphDataContainer::const_iterator endloop = ui->customPlot->graph(i)->data()->at(dataRange.end()); // get range end iterator from index
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
                /// Could just hard code min and max to set axis range parameters. But this is dynamic.
                emit setMinMax(selectedKeyData, selectedValueData);
                firstSelectionCheck = false;
            }
        }
    }
    selectionArray[0].clear();
    selectionArray[1].clear();
    selectionArray[2].clear();
    selectionArray[3].clear();
}

void MainWindow::viewSelection()
{
    emit getSelectionValues();
    ui->customPlot->xAxis->setRange(xAxisKeyMin,xAxisKeyMax);
    ui->customPlot->yAxis->setRange(floor(xAxisValueMin), ceil(xAxisValueMax)); /// make dynamic
    ui->customPlot->replot();
    xGraphSelection.dataRanges().clear();
    xGraphSelection.clear();
    yGraphSelection.clear();
    zGraphSelection.clear();
    nGraphSelection.clear();
}

void MainWindow::labelSelection()
{
    emit getSelectionValues();
    labelRect = new QCPItemRect(ui->customPlot);
    //QString redstr = popupData[0];QString greenstr = popupData[1];QString bluestr = popupData[2];
    //int red = redstr.toInt();int green = greenstr.toInt();int blue = bluestr.toInt();
    //labelRect->setBrush(QColor(red, green, blue, 75));
    //labelRect->setPen(QColor(red,green,blue, 75));
    labelRect->setBrush(QColor(225, 0, 0, 30));
    labelRect->setPen(QColor(225, 0, 0, 30));
    labelRect->setSelected(false);
    labelText = new QCPItemText(ui->customPlot);
    labelText->setText("Leg Up");
    labelText->setPositionAlignment(Qt::AlignHCenter | Qt::AlignTop);
    labelText->position->setCoords((xAxisKeyMin+xAxisKeyMax)/2, 1.9);
    /// NEED TO SAVE THESE COORDINATES SOMEWHERE TO SAVE
    labelRect->topLeft->setCoords(xAxisKeyMin, floor(xAxisValueMin));
    labelRect->bottomRight->setCoords(xAxisKeyMax, ceil(xAxisValueMax));
    /// DO WE NEED TO LABEL THESE SECTIONS?
    ui->customPlot->replot();
    xGraphSelection.clear();
    yGraphSelection.clear();
    zGraphSelection.clear();
    nGraphSelection.clear();
}

void MainWindow::rescaleView()
{
    ui->customPlot->rescaleAxes(true);
    ui->customPlot->replot();
    xGraphSelection.clear();
    yGraphSelection.clear();
    zGraphSelection.clear();
    nGraphSelection.clear();
    qDebug() << "Rescaled View";
}

void MainWindow::clickedGraph(QMouseEvent *event)
{
    QPoint p = event->pos();
    xKeyPos = ui->customPlot->xAxis->pixelToCoord(p.x());
    emit placeMarker(markerID);
    ui->customPlot->replot();
    if (addMarkerClicked)
    {
        addMarkerClicked = false;
        disconnect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(clickedGraph(QMouseEvent*)));
    }
}

/// COULD CHANGE markerID TO BE AN ENUM
void MainWindow::placeMarker(int ID)
{
    switch(ID)
    {
        case 0: markerUP = new QCPItemPixmap(ui->customPlot);
                markerUP->topLeft->setType(QCPItemPosition::ptPlotCoords);
                markerUP->bottomRight->setType(QCPItemPosition::ptPlotCoords);
                markerUP->topLeft->setCoords(xKeyPos, 0);
                /// Hard coded to be size 50x50, can make it constant
                markerUP->setPixmap(upPix->scaled(50,50,Qt::KeepAspectRatio));
                /// This could be used for setting label and view y-axis to the graph axis ranges
                //mImage->topLeft->setCoords(mCusPlot->xAxis->range().lower, mCusPlot->yAxis->range().upper);
                //mImage->bottomRight->setCoords(mCusPlot->xAxis->range().upper, mCusPlot->yAxis->range().lower);
                /// Not sure why the y-coordinates don't change the location. (might be because scaling is set to false, uses topleft only)
                markerUP->setScaled(false);
                markerUP->setSelectable(true);
                break;
        case 1: markerD = new QCPItemPixmap(ui->customPlot);
                markerD->topLeft->setType(QCPItemPosition::ptPlotCoords);
                markerD->bottomRight->setType(QCPItemPosition::ptPlotCoords);
                markerD->topLeft->setCoords(xKeyPos, 0);
                markerD->setPixmap(downPix->scaled(50,50,Qt::KeepAspectRatio));
                markerD->setScaled(false);
                markerD->setSelectable(true);
                break;
        case 2: markerP = new QCPItemPixmap(ui->customPlot);
                markerP->topLeft->setType(QCPItemPosition::ptPlotCoords);
                markerP->bottomRight->setType(QCPItemPosition::ptPlotCoords);
                markerP->topLeft->setCoords(xKeyPos, 0);
                markerP->setPixmap(pPix->scaled(50,50,Qt::KeepAspectRatio));
                markerP->setScaled(false);
                markerP->setSelectable(true);
                break;
        case 3: markerR = new QCPItemPixmap(ui->customPlot);
                markerR->topLeft->setType(QCPItemPosition::ptPlotCoords);
                markerR->bottomRight->setType(QCPItemPosition::ptPlotCoords);
                markerR->topLeft->setCoords(xKeyPos, 0);
                markerR->setPixmap(rPix->scaled(50,50,Qt::KeepAspectRatio));
                markerR->setScaled(false);
                markerR->setSelectable(true);
                break;
        case 4: markerK = new QCPItemPixmap(ui->customPlot);
                markerK->topLeft->setType(QCPItemPosition::ptPlotCoords);
                markerK->bottomRight->setType(QCPItemPosition::ptPlotCoords);
                markerK->topLeft->setCoords(xKeyPos, 0);
                markerK->setPixmap(kPix->scaled(50,50,Qt::KeepAspectRatio));
                markerK->setScaled(false);
                markerK->setSelectable(true);
                break;
        case 5: markerI = new QCPItemPixmap(ui->customPlot);
                markerI->topLeft->setType(QCPItemPosition::ptPlotCoords);
                markerI->bottomRight->setType(QCPItemPosition::ptPlotCoords);
                markerI->topLeft->setCoords(xKeyPos, 0);
                markerI->setPixmap(iPix->scaled(50,50,Qt::KeepAspectRatio));
                markerI->setScaled(false);
                markerI->setSelectable(true);
                break;
        default:
                break;
    }
}

void MainWindow::showRightClickMenu(const QPoint& pos) // this is a slot
{
    QPoint globalPos = ui->customPlot->mapToGlobal(pos);

    xGraphSelection = ui->customPlot->graph(0)->selection();
    yGraphSelection = ui->customPlot->graph(1)->selection();
    zGraphSelection = ui->customPlot->graph(2)->selection();
    nGraphSelection = ui->customPlot->graph(3)->selection();

    // Checks for no selection and hides options
    /// LOOK INTO STILL ENABLED WHEN NO SELECTION (MIGHT BE ONE DATA POINT SELECTED)
    if (xGraphSelection.dataPointCount() != 0 || yGraphSelection.dataPointCount() != 0
            || zGraphSelection.dataPointCount() != 0 || nGraphSelection.dataPointCount() != 0) /// Maybe set to != 0 or != 1?
    {
        viewSelectionAct->setEnabled(true);
        labelSelectionAct->setEnabled(true);
    }
    else
    {
        viewSelectionAct->setEnabled(false);
        labelSelectionAct->setEnabled(false);
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
            addMarkerClicked = true;
            markerID = 0;
            connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(clickedGraph(QMouseEvent*)));
        }
        else if (selectedItem->text().contains("Down Marker"))
        {
            addMarkerClicked = true;
            markerID = 1;
            connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(clickedGraph(QMouseEvent*)));
        }
        else if (selectedItem->text().contains("P Marker"))
        {
            addMarkerClicked = true;
            markerID = 2;
            connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(clickedGraph(QMouseEvent*)));
        }
        else if (selectedItem->text().contains("R Marker"))
        {
            addMarkerClicked = true;
            markerID = 3;
            connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(clickedGraph(QMouseEvent*)));
        }
        else if (selectedItem->text().contains("K Marker"))
        {
            addMarkerClicked = true;
            markerID = 4;
            connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(clickedGraph(QMouseEvent*)));
        }
        else if (selectedItem->text().contains("I Marker"))
        {
            addMarkerClicked = true;
            markerID = 5;
            connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(clickedGraph(QMouseEvent*)));
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
