#include "mainwindow.h"
#include "datastructure.h"
#include "csvreader.h"
#include "graphviewer.h"
#include "setupwindow.h"
#include "bluetoothwindow.h"

#include <QDir>
#include <QFileDialog>

#include <QString>
#include <QDebug>
#include <QKeyEvent>

#include <QScrollBar>
#include <iostream>
#include <iomanip>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    ui->setupUi(this);
    firstRun = true;
    addMarkerClicked = false;

    bTWindow = new BluetoothWindow(ui->customPlot);

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
    // File Menu Actions
    openAct = new QAction(QIcon(":/resources/toolbar/openRawDataFile.png"), tr("&Open Raw Data File"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open a file"));
    saveAct = new QAction(QIcon(":/resources/toolbar/saveFile.png"), tr("&Save File"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save a file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    /// connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    // Edit Menu Actions
    graphViewPreferencesAct = new QAction(tr("Graph View Preferences"));
    labelPreferencesAct = new QAction(tr("Label Preferences"));
    connect(graphViewPreferencesAct, &QAction::triggered, this, &MainWindow::openSetupWindow);
    connect(labelPreferencesAct, &QAction::triggered, this, &MainWindow::openSetupWindow);

    // Bluetooth Menu Actions
    setupBluetoothAct = new QAction(QIcon(":/resources/toolbar/bluetooth.png"), tr("Setup Bluetooth"));
    connect(setupBluetoothAct, &QAction::triggered, this, &MainWindow::openBluetoothWindow);


    // Tool Button Actions
    handToolAct = new QAction(QIcon(":/resources/toolbar/handTool.png"), tr("Hand Tool"), this);
    selectToolAct = new QAction(QIcon(":/resources/toolbar/selectTool.png"), tr("Select Tool"), this);
    //labelToolAct = new QAction(QIcon(":/resources/toolbar/labelTool.png"), tr("Label Tool"), this);
    rulerToolAct = new QAction(QIcon(":/resources/toolbar/rulerTool.png"), tr("Ruler Tool"), this);
    bluetoothToolAct = new QAction(QIcon(":/resources/toolbar/bluetooth.png"), tr("Setup Bluetooth"), this);
    handToolAct->setCheckable(true);
    selectToolAct->setCheckable(true);
    //labelToolAct->setCheckable(true);
    rulerToolAct->setCheckable(true);
    bluetoothToolAct->setCheckable(true);
    handToolAct->setShortcut(QKeySequence("H"));
    selectToolAct->setShortcut(QKeySequence("S"));
    //labelToolAct->setShortcut(QKeySequence("L"));
    rulerToolAct->setShortcut(QKeySequence("R"));
    bluetoothToolAct->setShortcut(QKeySequence("B"));
    handToolAct->setStatusTip(tr("Hand Tool"));
    selectToolAct->setStatusTip(tr("Marker Tool"));
    //labelToolAct->setStatusTip(tr("Label Tool"));
    rulerToolAct->setStatusTip(tr("Ruler Tool"));
    bluetoothToolAct->setStatusTip(tr("Bluetooth Tool"));
    connect(bluetoothToolAct, &QAction::triggered, this, &MainWindow::openBluetoothWindow);

    // Right Click Actions
    viewSelectionAct = new QAction(tr("&View Selection"), this);
    viewSelectionAct->setShortcut(QKeySequence("CTRL+V"));
    viewSelectionAct->setStatusTip(tr("View Selection"));
    viewSelectionShortcut = new QShortcut(QKeySequence("CTRL+V"),this); /// Couldn't get the action shortcut to work, this works
    /// don't need this connection or don't need rightclick selection check
    //connect(viewSelectionAct, &QAction::triggered, this, &MainWindow::viewSelection);
    connect(viewSelectionShortcut, &QShortcut::activated, this, &MainWindow::viewSelection);

    labelSelectionAct = new QAction(tr("&Label Selection"), this);
    labelSelectionAct->setShortcut(QKeySequence("CTRL+L"));
    labelSelectionAct->setStatusTip(tr("Label Selection"));
    labelSelectionShortcut = new QShortcut(QKeySequence("CTRL+L"),this); /// Couldn't get the action shortcut to work, this works
    //connect(labelSelectionAct, &QAction::triggered, this, &MainWindow::labelSelection);
    connect(labelSelectionShortcut, &QShortcut::activated, this, &MainWindow::labelSelection);

    // Add Marker Actions
    addUpMarkerAct = new QAction(tr("&Up Marker"), this);
    addUpMarkerAct->setShortcut(QKeySequence("CTRL+U"));
    addUpMarkerAct->setStatusTip(tr("Up Marker"));
    addUpMarkerActShortcut = new QShortcut(QKeySequence("CTRL+U"),this); /// Couldn't get the action shortcut to work, this works
    //connect(addUpMarker, &QAction::triggered, this, &MainWindow::addMarkerUp);
    connect(addUpMarkerActShortcut, &QShortcut::activated, this, &MainWindow::addMarkerUp);

    addDownMarkerAct = new QAction(tr("&Down Marker"), this);
    addDownMarkerAct->setShortcut(QKeySequence("CTRL+D"));
    addDownMarkerAct->setStatusTip(tr("Down Marker"));
    addDownMarkerActShortcut = new QShortcut(QKeySequence("CTRL+D"),this); /// Couldn't get the action shortcut to work, this works
    //connect(addDownMarker, &QAction::triggered, this, &MainWindow::addMarkerDown);
    connect(addDownMarkerActShortcut, &QShortcut::activated, this, &MainWindow::addMarkerDown);

    addPMarkerAct = new QAction(tr("&P Marker"), this);
    addPMarkerAct->setShortcut(QKeySequence("CTRL+P"));
    addPMarkerAct->setStatusTip(tr("P Marker"));
    addPMarkerActShortcut = new QShortcut(QKeySequence("CTRL+P"),this); /// Couldn't get the action shortcut to work, this works
    //connect(addPMarker, &QAction::triggered, this, &MainWindow::addMarkerP);
    connect(addPMarkerActShortcut, &QShortcut::activated, this, &MainWindow::addMarkerP);

    addRMarkerAct = new QAction(tr("&R Marker"), this);
    addRMarkerAct->setShortcut(QKeySequence("CTRL+R"));
    addRMarkerAct->setStatusTip(tr("R Marker"));
    addRMarkerActShortcut = new QShortcut(QKeySequence("CTRL+R"),this); /// Couldn't get the action shortcut to work, this works
    //connect(addRMarker, &QAction::triggered, this, &MainWindow::addMarkerR);
    connect(addRMarkerActShortcut, &QShortcut::activated, this, &MainWindow::addMarkerR);

    addKMarkerAct = new QAction(tr("&K Marker"), this);
    addKMarkerAct->setShortcut(QKeySequence("CTRL+K"));
    addKMarkerAct->setStatusTip(tr("K Marker"));
    addKMarkerActShortcut = new QShortcut(QKeySequence("CTRL+K"),this); /// Couldn't get the action shortcut to work, this works
    //connect(addKMarker, &QAction::triggered, this, &MainWindow::addMarkerK);
    connect(addKMarkerActShortcut, &QShortcut::activated, this, &MainWindow::addMarkerK);

    addIMarkerAct = new QAction(tr("&I Marker"), this);
    addIMarkerAct->setShortcut(QKeySequence("CTRL+I"));
    addIMarkerAct->setStatusTip(tr("I Marker"));
    addIMarkerActShortcut = new QShortcut(QKeySequence("CTRL+I"),this); /// Couldn't get the action shortcut to work, this works
    //connect(addIMarker, &QAction::triggered, this, &MainWindow::addMarkerI);
    connect(addIMarkerActShortcut, &QShortcut::activated, this, &MainWindow::addMarkerI);

    deleteAct = new QAction(tr("&Delete Marker/Selection(s)"), this);
    deleteAct->setShortcut(QKeySequence::Delete);
    deleteAct->setStatusTip(tr("Delete Marker/Selection(s)"));
    deleteActShortcut = new QShortcut(QKeySequence::Delete, this);
    //connect(deleteMarker, &QAction::triggered, this, &MainWindow::markerDelete);
    connect(deleteActShortcut, &QShortcut::activated, this, &MainWindow::deleteMS);

    /*deleteSelectionAct = new QAction(tr("&Delete Selection(s)"), this);
    deleteSelectionAct->setShortcut(QKeySequence(Qt::CTRL) + QKeySequence::Delete);
    deleteSelectionAct->setStatusTip(tr("Delete Selection(s)"));
    deleteSelectionActShortcut = new QShortcut(QKeySequence(Qt::CTRL + QKeySequence::Delete), this);
    //connect(deleteMarker, &QAction::triggered, this, &MainWindow::markerDelete);
    connect(deleteSelectionActShortcut, &QShortcut::activated, this, &MainWindow::deleteSelection);*/

    rescaleViewAct = new QAction(tr("&Rescale View"), this);
    rescaleViewAct->setShortcut(QKeySequence("CTRL+SHIFT+R"));
    rescaleViewAct->setStatusTip(tr("Rescale View"));
    rescaleViewShortcut = new QShortcut(QKeySequence("CTRL+SHIFT+R"),this); /// Couldn't get the action shortcut to work, this works
    //connect(rescaleViewAct, &QAction::triggered, this, &MainWindow::rescaleView);
    connect(rescaleViewShortcut, &QShortcut::activated, this, &MainWindow::rescaleView);

    /// Currently does nothing
    hideGraphAct = new QAction("Hide X, Y, Z Graphs");
    hideGraphAct->setCheckable(true);
    hideGraphAct->setChecked(false);
    hideGraphAct->setShortcut(QKeySequence("CTRL+H"));
    hideGraphAct->setStatusTip(tr("Hide X, Y, Z Graphs"));
    hideGraphShortcut = new QShortcut(QKeySequence("CTRL+H"), this);
    //connect(hideGraphAct, &QAction::changed, this, &MainWindow::hideXYZGraphs);
    connect(hideGraphShortcut, &QShortcut::activated, this, &MainWindow::hideXYZGraphs);

    /// Connects Scrollbar to Customplot
    connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(graphViewPreferencesAct);
    editMenu->addAction(labelPreferencesAct);

    bluetoothMenu = menuBar()->addMenu(tr("&Bluetooth"));
    bluetoothMenu->addAction(setupBluetoothAct);


    // Toolbar Menu
    ui->toolBar->addAction(openAct);
    ui->toolBar->addAction(saveAct);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(handToolAct);//, "Hand Tool");
    ui->toolBar->addAction(selectToolAct);//, "Select Tool");
    //ui->toolBar->addAction(labelToolAct);//, "Label Tool");
    ui->toolBar->addAction(rulerToolAct);
    ui->toolBar->addAction(bluetoothToolAct);
    connect(handToolAct, &QAction::triggered, this, &MainWindow::handToolTriggered);
    connect(selectToolAct, &QAction::triggered, this, &MainWindow::markerToolTriggered);
    connect(rulerToolAct, &QAction::triggered, this, &MainWindow::rulerToolTriggered);
    //connect(bluetoothToolAct, &QAction::triggered, this, &MainWindow::bluetoothToolTriggered);

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
    addMarkerMenu->addAction(addUpMarkerAct);
    addMarkerMenu->addAction(addDownMarkerAct);
    addMarkerMenu->addAction(addPMarkerAct);
    addMarkerMenu->addAction(addRMarkerAct);
    addMarkerMenu->addAction(addKMarkerAct);
    addMarkerMenu->addAction(addIMarkerAct);
    rightClickMenu->addAction(deleteAct);
    //rightClickMenu->addAction(deleteSelectionAct);
    rightClickMenu->addAction(rescaleViewAct);
    rightClickMenu->addAction(hideGraphAct);

    emit disableToolBar();
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
    //painter.drawPixmap(globalPos, upPix->scaled(32,32,Qt::KeepAspectRatio));

    downPix = new QPixmap(":/resources/toolbar/DMarker.png");

    pPix = new QPixmap(":/resources/toolbar/PMarker.png");

    rPix = new QPixmap(":/resources/toolbar/RMarker.png");

    kPix = new QPixmap(":/resources/toolbar/KMarker.png");

    iPix = new QPixmap(":/resources/toolbar/IMarker.png");
}

/*void MainWindow::createRuler()
{
    //ICSRulerWidget.createMarker(false);

}*/

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress )
    {
        QKeyEvent* keyEvent = (QKeyEvent*)event;
        double move = ui->customPlot->xAxis->range().size()*(sWindow->getSliderScaledMovement()/10.0);
        qDebug() << "move = " << move;
        if (keyEvent->key() == Qt::Key_Left)
        {
            //qDebug() << "move slider left";
            ui->horizontalScrollBar->setSliderPosition(ui->horizontalScrollBar->sliderPosition()-move);
        }
        else if (keyEvent->key()== Qt::Key_Right)
        {
            //qDebug() << "move slider right";
            ui->horizontalScrollBar->setSliderPosition(ui->horizontalScrollBar->sliderPosition()+move);
        }

    }
    else if (event->type() == QEvent::FocusOut)
    {
        emit focusChanged();
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::focusChanged()
{
    ui->horizontalScrollBar->setFocus(Qt::OtherFocusReason);
}

void MainWindow::horzScrollBarChanged(int value)
{
    //qDebug() << "Lower: " << ui->customPlot->xAxis->range().lower;
    //qDebug() << qAbs(ui->customPlot->xAxis->range().center()-value);
    if (qAbs(ui->customPlot->xAxis->range().center()-value) > 1) // if user is dragging plot, we don't want to replot twice
    {
        //qDebug() << "Range(" << value << "," << ui->customPlot->xAxis->range().size() << ")";
        //ui->customPlot->xAxis->setRange(ui->customPlot->xAxis->range().lower+value, ui->customPlot->xAxis->range().upper+value, Qt::AlignCenter);
        ui->customPlot->xAxis->setRange(value, ui->customPlot->xAxis->range().size(), Qt::AlignCenter);
        ui->customPlot->replot();
    }
}

void MainWindow::xAxisChanged(QCPRange range)
{
    //qDebug() << "range.center" << qRound(range.center());
    if (!firstRun)
    {
        ui->horizontalScrollBar->setValue(qRound(range.center()));//center())); // adjust position of scroll bar slider
    }
    ui->horizontalScrollBar->setPageStep(qRound(range.size())); // adjust size of scroll bar slider
}

void MainWindow::open()
{
    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);
    file = QFileDialog::getOpenFileName(this,tr("Open File"),QDir::currentPath(),"CSV files, txt files (*.csv *.txt);;all files (*.*)");

    //struct DataStructure data_structure;

    if (!file.isEmpty()) {
        CsvReader csvReader(model);
        csvReader.importCSV(file);
        data_structure = csvReader.exportData(data_structure);


        sWindow = new SetupWindow(ui->customPlot); //, graphViewer);
        graphViewer = new GraphViewer(ui, sWindow);

        graphViewer->setFirstTime(firstRun);
        qDebug() << "data_structure.time_values = " << data_structure.time_values;
        graphViewer->createGraph(data_structure.time_values, data_structure.x_acc_values, data_structure.y_acc_values, data_structure.z_acc_values, data_structure.magnitude_values);

        ui->horizontalScrollBar->setRange(graphViewer->getGraphKeyMin(), graphViewer->getGraphKeyUpper());
        qDebug() << "xAxis center" << ui->customPlot->xAxis->range().center();
        qDebug() << "xAxis lower" << ui->customPlot->xAxis->range().lower;
        qDebug() << "xAxis upper" << ui->customPlot->xAxis->range().upper;
        ui->horizontalScrollBar->setValue(ui->customPlot->xAxis->range().center());
        qDebug() << sWindow->getSliderScaledMovement();
        scaledMovement = sWindow->getSliderScaledMovement();
        sWindow->getGraphViewer(graphViewer);

        firstRun = false;
        // Defaults to Hand Tool when file is opened
        emit enableToolBar();
        emit handToolAct->trigger();

        if (fileExists(file.left(file.length() - 4) + "_markers.txt")) {
            csvReader.importMarkers(file.left(file.length() - 4) + "_markers.txt");
            marker_structure = csvReader.exportMarkers(marker_structure);
            emit loadMarkers();
        }

        if (fileExists(file.left(file.length() - 4) + "_selections.txt")) {
            csvReader.importSelections(file.left(file.length() - 4) + "_selections.txt");
            selection_structure = csvReader.exportSelections(selection_structure);
            emit loadSelections();
        }

        phaseTracer = new QCPItemTracer(ui->customPlot);
        phaseTracer->setGraph(ui->customPlot->graph(3));
        phaseTracer->setInterpolating(false);
        phaseTracer->setStyle(QCPItemTracer::tsCircle);
        phaseTracer->setPen(QPen(Qt::red));
        phaseTracer->setBrush(Qt::red);
        phaseTracer->setSize(7);

        phaseTracerItemText = new QCPItemText(ui->customPlot);
        phaseTracerItemText->setPositionAlignment(Qt::AlignHCenter | Qt::AlignTop);

        phaseTracer->setVisible(false);
        phaseTracerItemText->setVisible(false);

        ui->horizontalScrollBar->installEventFilter(this);
        ui->horizontalScrollBar->setFocus(Qt::OtherFocusReason);
    }
}

void MainWindow::openSetupWindow()
{
    qDebug() << sender();
    // figure out "OK" and "Cancel" saving method
    sWindow->setOkGraphViewButtonEnabled();
    sWindow->setOkLabelButtonEnabled();
    sWindow->initArrowMovementValue = sWindow->currentArrowMovementValue;
    sWindow->initKeyScalingValue = sWindow->currentKeyScalingValue;
    sWindow->initValueMinValue = sWindow->currentValueMinValue;
    sWindow->initValueMaxValue = sWindow->currentValueMaxValue;
    if (sender() == graphViewPreferencesAct)
    {
        sWindow->setCurrentTabIndex(0); // Make Constant index values
    }
    else if (sender() == labelPreferencesAct)
    {
        sWindow->setCurrentTabIndex(1);
    }
    sWindow->exec();
}

void MainWindow::openBluetoothWindow()
{
    bTWindow->exec();
}

/*void MainWindow::setCustomPlotChanges()
{
    scaledMovement = sWindow->getSliderScaledMovement();
    graphViewer->setGraphRanges(sWindow->getSliderKeyScale(), sWindow->getSliderValueMin(), sWindow->getSliderValueMax());
    //graphViwerkeyMax*(sWindow->getSliderKeyScale()/10.0) + (keyMax*(sWindow->getSliderKeyScale()/10.0))/20;
}*/



void MainWindow::saveMarkers()
{
    if (!file.isEmpty()) {
        QString path = file.left(file.length() - 4) + "_markers.txt";
        QFile outputFile(path);
        outputFile.resize(0);

        if (outputFile.open(QIODevice::ReadWrite)) {

            QTextStream stream( &outputFile );
            for (int i = 0; i < marker_structure.keyPosition.length()-1; i++) {
                stream << marker_structure.keyPosition[i] << "," << marker_structure.id[i] << ",";
                qDebug() << marker_structure.keyPosition[i] << "," << marker_structure.id[i];
            }

            if (!marker_structure.keyPosition.isEmpty()) {
                stream << marker_structure.keyPosition[marker_structure.keyPosition.length()-1] << "," << marker_structure.id[marker_structure.id.length()-1];
            }
        }
    }
    //qDebug() << path;
}

void MainWindow::saveSelections()
{
    if (!file.isEmpty()) {
        QString path = file.left(file.length() - 4) + "_selections.txt";
        QFile outputFile(path);
        outputFile.resize(0);

        if (outputFile.open(QIODevice::ReadWrite)) {

            QTextStream stream( &outputFile );
            for (int i = 0; i < selection_structure.xAxisKeyMin.length()-1; i++) {
                stream << selection_structure.xAxisKeyMin[i] << "," << selection_structure.xAxisKeyMax[i] << "," << selection_structure.xAxisValueMin[i] << "," << selection_structure.xAxisValueMax[i] << ",";
                //qDebug() << marker_structure.keyPosition[i] << "," << marker_structure.id[i];
            }

            if (!selection_structure.xAxisKeyMax.isEmpty()) {
                stream << selection_structure.xAxisKeyMin[selection_structure.xAxisKeyMin.length()-1] << "," << selection_structure.xAxisKeyMax[selection_structure.xAxisKeyMin.length()-1] << "," << selection_structure.xAxisValueMin[selection_structure.xAxisKeyMin.length()-1] << "," << selection_structure.xAxisValueMax[selection_structure.xAxisKeyMin.length()-1];
            }
        }
    }
    //qDebug() << path;
}

void MainWindow::loadMarkers() {
    for (int i = 0; i < marker_structure.keyPosition.length(); i++) {
        xKeyPos = marker_structure.keyPosition[i];
        emit createMarker(marker_structure.id[i]);
    }
    ui->customPlot->replot();
}

void MainWindow::loadSelections() {
    for (int i = 0; i < selection_structure.xAxisKeyMax.length(); i++) {
        rect = new QCPItemRect(ui->customPlot);
        rect->setBrush(QColor(225, 0, 0, 30));
        rect->setPen(QColor(225, 0, 0, 30));
        rect->setSelected(false);
        rect->topLeft->setCoords(selection_structure.xAxisKeyMin[i], floor(selection_structure.xAxisValueMin[i]));
        rect->bottomRight->setCoords(selection_structure.xAxisKeyMax[i], ceil(selection_structure.xAxisValueMax[i]));
        rect->setXKeyMin(selection_structure.xAxisKeyMin[i]);
        rect->setXKeyMax(selection_structure.xAxisKeyMax[i]);
        rect->setXValueMin(selection_structure.xAxisValueMin[i]);
        rect->setXValueMax(selection_structure.xAxisValueMax[i]);
        labelText = new QCPItemText(ui->customPlot);
        labelText->setParent(rect);
        labelText->setSelectable(false);
        labelText->setObjectName("lText");
        labelText->setText("Leg Up");
        labelText->setPositionAlignment(Qt::AlignHCenter | Qt::AlignTop);
        labelText->position->setCoords((selection_structure.xAxisKeyMin[i]+selection_structure.xAxisKeyMax[i])/2, selection_structure.xAxisValueMax[i]);
        ui->customPlot->replot();
    }
    ui->customPlot->replot();
}

bool MainWindow::fileExists(QString path) {
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}

void MainWindow::enableToolBar()
{
    graphViewPreferencesAct->setEnabled(true);
    labelPreferencesAct->setEnabled(true);
    handToolAct->setEnabled(true);
    selectToolAct->setEnabled(true);
    //labelToolAct->setEnabled(true);
    rulerToolAct->setEnabled(true);
    bluetoothToolAct->setEnabled(true);
    viewSelectionShortcut->setEnabled(true);
    labelSelectionShortcut->setEnabled(true);
    rescaleViewShortcut->setEnabled(true);
    addMarkerMenu->setEnabled(true);
    addUpMarkerActShortcut->setEnabled(true);
    addDownMarkerActShortcut->setEnabled(true);
    addPMarkerActShortcut->setEnabled(true);
    addRMarkerActShortcut->setEnabled(true);
    addKMarkerActShortcut->setEnabled(true);
    addIMarkerActShortcut->setEnabled(true);
    ui->horizontalScrollBar->setEnabled(true);
}

void MainWindow::disableToolBar()
{
    graphViewPreferencesAct->setEnabled(false);
    labelPreferencesAct->setEnabled(false);
    handToolAct->setEnabled(false);
    selectToolAct->setEnabled(false);
    //labelToolAct->setEnabled(false);
    rulerToolAct->setEnabled(false);
    viewSelectionShortcut->setEnabled(false);
    labelSelectionShortcut->setEnabled(false);
    rescaleViewShortcut->setEnabled(false);
    addMarkerMenu->setEnabled(false);
    addUpMarkerActShortcut->setEnabled(false);
    addDownMarkerActShortcut->setEnabled(false);
    addPMarkerActShortcut->setEnabled(false);
    addRMarkerActShortcut->setEnabled(false);
    addKMarkerActShortcut->setEnabled(false);
    addIMarkerActShortcut->setEnabled(false);
    ui->horizontalScrollBar->setEnabled(false);
}

/* RIGHT CLICK EVENT and RECTANGLE SCALING*/
void MainWindow::rightMousePress()
{
    if (!firstRun)
    {
        const QPoint cursorLoc = ui->customPlot->mapFromGlobal(QCursor::pos());
        qDebug() << cursorLoc;
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
}

void MainWindow::viewSelection()
{
    xGraphSelection = ui->customPlot->graph(0)->selection();
    yGraphSelection = ui->customPlot->graph(1)->selection();
    zGraphSelection = ui->customPlot->graph(2)->selection();
    nGraphSelection = ui->customPlot->graph(3)->selection();
    if (xGraphSelection.dataPointCount() != 0 || yGraphSelection.dataPointCount() != 0
            || zGraphSelection.dataPointCount() !=0 || nGraphSelection.dataPointCount() !=0)
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
}

void MainWindow::labelSelection()
{
    xGraphSelection = ui->customPlot->graph(0)->selection();
    yGraphSelection = ui->customPlot->graph(1)->selection();
    zGraphSelection = ui->customPlot->graph(2)->selection();
    nGraphSelection = ui->customPlot->graph(3)->selection();
    if (xGraphSelection.dataPointCount() != 0 || yGraphSelection.dataPointCount() != 0
            || zGraphSelection.dataPointCount() !=0 || nGraphSelection.dataPointCount() !=0)
    {
        emit getSelectionValues();
        rect = new QCPItemRect(ui->customPlot);
        //QString redstr = popupData[0];QString greenstr = popupData[1];QString bluestr = popupData[2];
        //int red = redstr.toInt();int green = greenstr.toInt();int blue = bluestr.toInt();
        //labelRect->setBrush(QColor(red, green, blue, 75));
        //labelRect->setPen(QColor(red,green,blue, 75));
        rect->setBrush(sWindow->getLabelColor());
        rect->setPen(sWindow->getLabelColor());
        rect->setSelected(false);
        /// NEED TO SAVE THESE COORDINATES SOMEWHERE TO SAVE
        rect->topLeft->setCoords(xAxisKeyMin, floor(xAxisValueMin));
        rect->bottomRight->setCoords(xAxisKeyMax, ceil(xAxisValueMax));
        selection_structure.xAxisKeyMin.append(xAxisKeyMin);
        selection_structure.xAxisKeyMax.append(xAxisKeyMax);
        selection_structure.xAxisValueMin.append(xAxisValueMin);
        selection_structure.xAxisValueMax.append(xAxisValueMax);
        rect->setXKeyMin(xAxisKeyMin);
        rect->setXKeyMax(xAxisKeyMax);
        rect->setXValueMin(xAxisValueMin);
        rect->setXValueMax(xAxisValueMax);
        labelText = new QCPItemText(ui->customPlot);
        /// Allows deletion of label when rect is deleted. But causes Segmentation Fault. Fix.
        labelText->setParent(rect);
        labelText->setSelectable(false);
        labelText->setObjectName("lText");
        labelText->setText(sWindow->getLabelText());
        labelText->setPositionAlignment(Qt::AlignHCenter | Qt::AlignTop);
        labelText->position->setCoords((xAxisKeyMin+xAxisKeyMax)/2, xAxisValueMax);
        /// DO WE NEED TO LABEL THESE SECTIONS?
        ui->customPlot->replot();
        xGraphSelection.clear();
        yGraphSelection.clear();
        zGraphSelection.clear();
        nGraphSelection.clear();
    }
}

void MainWindow::rescaleView()
{
    //ui->customPlot->axisRect()->setMargins(QMargins(0,50,0,0));
    /// This is auto rescaling based on plottables
    //ui->customPlot->rescaleAxes(true);
    /// Hard coded y range
    //ui->customPlot->yAxis->setRange(8,-2);
    //ui->customPlot->yAxis->setRange(3,-3);
    graphViewer->setGraphRanges(sWindow->getSliderKeyScale(), sWindow->getSliderValueMin(), sWindow->getSliderValueMax());

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
    emit createMarker(markerID);
    marker_structure.keyPosition.append(xKeyPos);
    marker_structure.id.append(markerID);
    //qDebug() << xKeyPos << "," << markerID;
    ui->customPlot->replot();
    if (addMarkerClicked)
    {
        addMarkerClicked = false;
        this->setCursor(Qt::ArrowCursor);
        disconnect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(clickedGraph(QMouseEvent*)));
    }
}

/// COULD CHANGE markerID TO BE AN ENUM
void MainWindow::createMarker(double ID)
{
    switch((int)ID)
    {
        case 0: markerUP = new QCPItemPixmap(ui->customPlot);
                /// Slow function, but hides background white
                upPix->setMask(pPix->createHeuristicMask(true));
                markerUP->topLeft->setType(QCPItemPosition::ptPlotCoords);
                markerUP->bottomRight->setType(QCPItemPosition::ptPlotCoords);
                markerUP->selectable();
                /// Hard coded to be size 32x32, can make it constant
                markerUP->setPixmap(upPix->scaled(32,32,Qt::KeepAspectRatio));
                /// FIND A WAY TO SET top to the anchor or move pixmap over to center placement position.
                markerUP->topLeft->setCoords(xKeyPos, 0);
                markerUP->setXPosition(xKeyPos);
                /// This could be used for setting label and view y-axis to the graph axis ranges
                //mImage->topLeft->setCoords(mCusPlot->xAxis->range().lower, mCusPlot->yAxis->range().upper);
                //mImage->bottomRight->setCoords(mCusPlot->xAxis->range().upper, mCusPlot->yAxis->range().lower);
                /// Not sure why the y-coordinates don't change the location. (might be because scaling is set to false, uses topleft only)
                markerUP->setScaled(false);
                markerUP->setSelectable(true);
                break;
        case 1: markerD = new QCPItemPixmap(ui->customPlot);
                /// Slow function, but hides background white
                downPix->setMask(pPix->createHeuristicMask(true));
                markerD->topLeft->setType(QCPItemPosition::ptPlotCoords);
                markerD->bottomRight->setType(QCPItemPosition::ptPlotCoords);
                markerD->topLeft->setCoords(xKeyPos, 0);
                markerD->setXPosition(xKeyPos);
                markerD->setPixmap(downPix->scaled(32,32,Qt::KeepAspectRatio));
                markerD->setScaled(false);
                markerD->setSelectable(true);
                break;
        case 2: markerP = new QCPItemPixmap(ui->customPlot);
                /// Slow function, but hides background white
                pPix->setMask(pPix->createHeuristicMask(true));
                markerP->topLeft->setType(QCPItemPosition::ptPlotCoords);
                markerP->bottomRight->setType(QCPItemPosition::ptPlotCoords);
                markerP->topLeft->setCoords(xKeyPos, 0);
                markerP->setXPosition(xKeyPos);
                markerP->setPixmap(pPix->scaled(32,32,Qt::KeepAspectRatio));
                markerP->setScaled(false);
                markerP->setSelectable(true);
                break;
        case 3: markerR = new QCPItemPixmap(ui->customPlot);
                /// Slow function, but hides background white
                rPix->setMask(pPix->createHeuristicMask(true));
                markerR->topLeft->setType(QCPItemPosition::ptPlotCoords);
                markerR->bottomRight->setType(QCPItemPosition::ptPlotCoords);
                markerR->topLeft->setCoords(xKeyPos, 0);
                markerR->setXPosition(xKeyPos);
                markerR->setPixmap(rPix->scaled(32,32,Qt::KeepAspectRatio));
                markerR->setScaled(false);
                markerR->setSelectable(true);
                break;
        case 4: markerK = new QCPItemPixmap(ui->customPlot);
                /// Slow function, but hides background white
                kPix->setMask(pPix->createHeuristicMask(true));
                markerK->topLeft->setType(QCPItemPosition::ptPlotCoords);
                markerK->bottomRight->setType(QCPItemPosition::ptPlotCoords);
                markerK->topLeft->setCoords(xKeyPos, 0);
                markerK->setXPosition(xKeyPos);
                markerK->setPixmap(kPix->scaled(32,32,Qt::KeepAspectRatio));
                markerK->setScaled(false);
                markerK->setSelectable(true);
                break;
        case 5: markerI = new QCPItemPixmap(ui->customPlot);
                /// Slow function, but hides background white
                iPix->setMask(pPix->createHeuristicMask(true));
                markerI->topLeft->setType(QCPItemPosition::ptPlotCoords);
                markerI->bottomRight->setType(QCPItemPosition::ptPlotCoords);
                markerI->topLeft->setCoords(xKeyPos, 0);
                markerI->setXPosition(xKeyPos);
                markerI->setPixmap(iPix->scaled(32,32,Qt::KeepAspectRatio));
                markerI->setScaled(false);
                markerI->setSelectable(true);
                break;
        default:
                break;
    }
}

void MainWindow::addMarkerUp()
{
    addMarkerClicked = true;
    markerID = 0;
    /// CAN CHANGE TO PIXMAP IMAGE
    this->setCursor(Qt::CrossCursor);
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(clickedGraph(QMouseEvent*)));
}

void MainWindow::addMarkerDown()
{
    addMarkerClicked = true;
    markerID = 1;
    this->setCursor(Qt::CrossCursor);
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(clickedGraph(QMouseEvent*)));
}

void MainWindow::addMarkerP()
{
    addMarkerClicked = true;
    markerID = 2;
    this->setCursor(Qt::CrossCursor);
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(clickedGraph(QMouseEvent*)));
}

void MainWindow::addMarkerR()
{
    addMarkerClicked = true;
    markerID = 3;
    this->setCursor(Qt::CrossCursor);
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(clickedGraph(QMouseEvent*)));
}

void MainWindow::addMarkerK()
{
    addMarkerClicked = true;
    markerID = 4;
    this->setCursor(Qt::CrossCursor);
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(clickedGraph(QMouseEvent*)));
}

void MainWindow::addMarkerI()
{
    addMarkerClicked = true;
    markerID = 5;
    this->setCursor(Qt::CrossCursor);
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(clickedGraph(QMouseEvent*)));
}

void MainWindow::deleteMS()
{
    // ItemClick?
    // selectTest?
    itemsSelected = ui->customPlot->selectedItems().count();
    for (int i = 0; i < itemsSelected; i++)
    {
        if (strcmp((ui->customPlot->selectedItems().at(0))->metaObject()->className(), "QCPItemPixmap") == 0)
        {
            QCPAbstractItem* item =ui->customPlot->selectedItems().at(0);
            qDebug() << "HERE:" << item->getXPosition();

            int index = marker_structure.keyPosition.indexOf(item->getXPosition());
            marker_structure.keyPosition.remove(index);
            marker_structure.id.remove(index);
            ui->customPlot->removeItem(ui->customPlot->selectedItems().at(0));
            //delete ui->customPlot->selectedItems().at(0);
        }
        else if (strcmp((ui->customPlot->selectedItems().at(0))->metaObject()->className(), "QCPItemRect") == 0)
        {
            ui->customPlot->removeItem(ui->customPlot->selectedItems().at(0)->findChild<QCPItemText*>("lText"));

            QCPAbstractItem* item =ui->customPlot->selectedItems().at(0);
            qDebug() << "HERE:" << item->getXKeyMin();

            int index = selection_structure.xAxisKeyMin.indexOf(item->getXKeyMin());
            selection_structure.xAxisKeyMin.remove(index);
            selection_structure.xAxisKeyMax.remove(index);
            selection_structure.xAxisValueMin.remove(index);
            selection_structure.xAxisValueMax.remove(index);

            ui->customPlot->removeItem(ui->customPlot->selectedItems().at(0));
            //delete ui->customPlot->selectedItems().at(0);
        }
    }
    //ui->customPlot->clearItems();
    ui->customPlot->replot();
}

void MainWindow::hideXYZGraphs()
{
    if (hideGraphAct->isChecked())
    {
        ui->customPlot->graph(0)->setVisible(false);
        ui->customPlot->graph(1)->setVisible(false);
        ui->customPlot->graph(2)->setVisible(false);
        ui->customPlot->graph(0)->removeFromLegend();
        ui->customPlot->graph(1)->removeFromLegend();
        ui->customPlot->graph(2)->removeFromLegend();
        ui->customPlot->graph(0)->setSelectable(QCP::stNone);
        ui->customPlot->graph(1)->setSelectable(QCP::stNone);
        ui->customPlot->graph(2)->setSelectable(QCP::stNone);
        ui->customPlot->replot();
    }
    else
    {
        ui->customPlot->graph(0)->addToLegend();
        ui->customPlot->graph(1)->addToLegend();
        ui->customPlot->graph(2)->addToLegend();
        ui->customPlot->graph(0)->setVisible(true);
        ui->customPlot->graph(1)->setVisible(true);
        ui->customPlot->graph(2)->setVisible(true);
        ui->customPlot->graph(0)->setSelectable(QCP::stDataRange);
        ui->customPlot->graph(1)->setSelectable(QCP::stDataRange);
        ui->customPlot->graph(2)->setSelectable(QCP::stDataRange);
        ui->customPlot->replot();
    }
}

void MainWindow::toggleHide()
{
    hideGraphAct->toggle();
}

void MainWindow::showRightClickMenu(const QPoint& pos) // this is a slot
{
    QPoint globalPos = ui->customPlot->mapToGlobal(pos);

    xGraphSelection = ui->customPlot->graph(0)->selection();
    yGraphSelection = ui->customPlot->graph(1)->selection();
    zGraphSelection = ui->customPlot->graph(2)->selection();
    nGraphSelection = ui->customPlot->graph(3)->selection();

    itemsSelected = ui->customPlot->selectedItems().count();
    if (itemsSelected != 0)
    {
        deleteAct->setEnabled(true);
    }
    else
    {
        deleteAct->setEnabled(false);
    }

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
            emit addMarkerUp();
        }
        else if (selectedItem->text().contains("Down Marker"))
        {
            emit addMarkerDown();
        }
        else if (selectedItem->text().contains("P Marker"))
        {
            emit addMarkerP();
        }
        else if (selectedItem->text().contains("R Marker"))
        {
            emit addMarkerR();
        }
        else if (selectedItem->text().contains("K Marker"))
        {
            emit addMarkerK();
        }
        else if (selectedItem->text().contains("I Marker"))
        {
            emit addMarkerI();
        }
        else if (selectedItem->text().contains("Delete Marker/Selection(s)"))
        {
            emit deleteMS();
        }
        else if (selectedItem->text().contains("Rescale View"))
        {
            emit rescaleView();
        }
        else if (selectedItem->text().contains("Hide X, Y, Z Graphs"))
        {
            emit hideXYZGraphs();
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
        selectToolAct->setChecked(false);
        rulerToolAct->setChecked(false);
        //bluetoothToolAct->setChecked(false);
        emit markerToolTriggered();
        emit rulerToolTriggered();
        //emit bluetoothToolTriggered();
        qDebug() << "HandTool: toggled";
    }
    else{
        qDebug() << "HandTool: un-toggled";
    }
}

void MainWindow::markerToolTriggered()
{
    if (selectToolAct->isChecked() == true){
        handToolAct->setChecked(false);
        rulerToolAct->setChecked(false);
        //bluetoothToolAct->setChecked(false);
        emit handToolTriggered();
        emit rulerToolTriggered();
        //emit bluetoothToolTriggered();
        qDebug() << "Select Tool: toggled";

        ui->customPlot->setSelectionRectMode(QCP::srmSelect);
        ui->customPlot->graph(0)->setSelectable(QCP::stDataRange);
        ui->customPlot->graph(1)->setSelectable(QCP::stDataRange);
        ui->customPlot->graph(2)->setSelectable(QCP::stDataRange);
        ui->customPlot->graph(3)->setSelectable(QCP::stDataRange);//QCP::SelectionType(QCP::stDataRange)
    }
    else{
        qDebug() << "Select Tool: un-toggled";

        ui->customPlot->setSelectionRectMode(QCP::srmNone);
        ui->customPlot->graph(0)->setSelectable(QCP::stNone);
        ui->customPlot->graph(1)->setSelectable(QCP::stNone);
        ui->customPlot->graph(2)->setSelectable(QCP::stNone);
        ui->customPlot->graph(3)->setSelectable(QCP::stNone);
    }
}

void MainWindow::updatePhaseTracer(QMouseEvent *event)
{
    QPoint p = event->pos();
    phaseTracerKeyPos = ui->customPlot->xAxis->pixelToCoord(p.x());
    qDebug() << "PhaseTracerKeyPos" << phaseTracerKeyPos;
    phaseTracer->setGraphKey(phaseTracerKeyPos);
    phaseTracerValuePos = phaseTracer->position->value();
    qDebug() << "PhaseTracerValuePos" << phaseTracerValuePos;

    phaseTracerItemText->setText(QString("Time: %1\nG: %2").arg(phaseTracerKeyPos).arg(phaseTracerValuePos));
    double scale = ui->customPlot->yAxis->range().size()*0.133;
    if (phaseTracerValuePos+scale < ui->customPlot->yAxis->range().upper)
    {
        phaseTracerItemText->position->setCoords(phaseTracerKeyPos, phaseTracerValuePos+scale);
    }
    else
    {
        phaseTracerItemText->position->setCoords(phaseTracerKeyPos, ui->customPlot->yAxis->range().upper);
    }

    //ui->customPlot->setStatusTip(QString("Time: %1, G: %2").arg(phaseTracerKeyPos).arg(phaseTracerValuePos));
    ui->customPlot->replot();
}

void MainWindow::createRuler(QMouseEvent *event)
{
    //QPoint p = event->pos();

}

void MainWindow::rulerToolTriggered()
{
    if (rulerToolAct->isChecked() == true){
        handToolAct->setChecked(false);
        selectToolAct->setChecked(false);
        emit handToolTriggered();
        emit markerToolTriggered();
        qDebug() << "Ruler Tool: toggled";

        // add the phase tracer (red circle) which sticks to the graph data (and gets updated in bracketDataSlot by timer event):
        phaseTracer->setVisible(true);
        phaseTracerItemText->setVisible(true);


        ui->customPlot->replot();
        connect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(updatePhaseTracer(QMouseEvent*)));
        connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(createRuler(QMouseEvent*)));
    }
    else{
        qDebug() << "Ruler Tool: un-toggled";
        phaseTracer->setVisible(false);
        phaseTracerItemText->setVisible(false);
        ui->customPlot->replot();
        disconnect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(updatePhaseTracer(QMouseEvent*)));
        disconnect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(createRuler(QMouseEvent*)));
    }
}

/*void MainWindow::bluetoothToolTriggered() {
    if (bluetoothToolAct->isChecked() == true){
        handToolAct->setChecked(false);
        selectToolAct->setChecked(false);
        rulerToolAct->setChecked(false);
        qDebug() << "Bluetooth Tool: toggled";

        QProcess p;
        p.setProcessChannelMode(QProcess::MergedChannels);
        QStringList params;
        QString exe = "python C:/Users/Asussy/Desktop/EmoryPLM/bluetooth/test.py";
        p.start(exe);
        p.waitForReadyRead();

        QString p_stdout = p.readAllStandardOutput();
        qDebug() << p_stdout << endl;

    }
    else{
        qDebug() << "Bluetooth tool: un-toggled";
    }
}*/

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "CLOSING";
    QMainWindow::closeEvent(event);
    emit saveMarkers();
    emit saveSelections();
}
