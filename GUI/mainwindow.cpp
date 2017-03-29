#include "mainwindow.h"
#include "datastructure.h"
#include "csvreader.h"
#include "graphviewer.h"

//#include <QDRuler>
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

    /*QGraphicsView *s = new QGraphicsView(this);
    s->setViewportMargins(RULER_BREADTH,RULER_BREADTH,0,0);
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setSpacing(0);
    gridLayout->setMargin(0);

    QWidget* fake = new QWidget();
    QDRuler *mHorzRuler = new QDRuler(QDRuler::Horizontal,fake);
    QDRuler *mVertRuler = new QDRuler(QDRuler::Vertical, fake);
    fake->setBackgroundRole(QPalette::Window);
    fake->setFixedSize(RULER_BREADTH,RULER_BREADTH);
    ui->gridLayout->addWidget(fake,0,0);
    ui->gridLayout->addWidget(mHorzRuler,0,1);
    ui->gridLayout->addWidget(mVertRuler,1,0);
    ui->gridLayout->addWidget(fake,1,1);

    this->setLayout(gridLayout);*/


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
    addUpMarker = new QAction(tr("&Up Marker"), this);
    addUpMarker->setShortcut(QKeySequence("CTRL+U"));
    addUpMarker->setStatusTip(tr("Up Marker"));
    addUpMarkerShortcut = new QShortcut(QKeySequence("CTRL+U"),this); /// Couldn't get the action shortcut to work, this works
    //connect(addUpMarker, &QAction::triggered, this, &MainWindow::addMarkerUp);
    connect(addUpMarkerShortcut, &QShortcut::activated, this, &MainWindow::addMarkerUp);

    addDownMarker = new QAction(tr("&Down Marker"), this);
    addDownMarker->setShortcut(QKeySequence("CTRL+D"));
    addDownMarker->setStatusTip(tr("Down Marker"));
    addDownMarkerShortcut = new QShortcut(QKeySequence("CTRL+D"),this); /// Couldn't get the action shortcut to work, this works
    //connect(addDownMarker, &QAction::triggered, this, &MainWindow::addMarkerDown);
    connect(addDownMarkerShortcut, &QShortcut::activated, this, &MainWindow::addMarkerDown);

    addPMarker = new QAction(tr("&P Marker"), this);
    addPMarker->setShortcut(QKeySequence("CTRL+P"));
    addPMarker->setStatusTip(tr("P Marker"));
    addPMarkerShortcut = new QShortcut(QKeySequence("CTRL+P"),this); /// Couldn't get the action shortcut to work, this works
    //connect(addPMarker, &QAction::triggered, this, &MainWindow::addMarkerP);
    connect(addPMarkerShortcut, &QShortcut::activated, this, &MainWindow::addMarkerP);

    addRMarker = new QAction(tr("&R Marker"), this);
    addRMarker->setShortcut(QKeySequence("CTRL+R"));
    addRMarker->setStatusTip(tr("R Marker"));
    addRMarkerShortcut = new QShortcut(QKeySequence("CTRL+R"),this); /// Couldn't get the action shortcut to work, this works
    //connect(addRMarker, &QAction::triggered, this, &MainWindow::addMarkerR);
    connect(addRMarkerShortcut, &QShortcut::activated, this, &MainWindow::addMarkerR);

    addKMarker = new QAction(tr("&K Marker"), this);
    addKMarker->setShortcut(QKeySequence("CTRL+K"));
    addKMarker->setStatusTip(tr("K Marker"));
    addKMarkerShortcut = new QShortcut(QKeySequence("CTRL+K"),this); /// Couldn't get the action shortcut to work, this works
    //connect(addKMarker, &QAction::triggered, this, &MainWindow::addMarkerK);
    connect(addKMarkerShortcut, &QShortcut::activated, this, &MainWindow::addMarkerK);

    addIMarker = new QAction(tr("&I Marker"), this);
    addIMarker->setShortcut(QKeySequence("CTRL+I"));
    addIMarker->setStatusTip(tr("I Marker"));
    addIMarkerShortcut = new QShortcut(QKeySequence("CTRL+I"),this); /// Couldn't get the action shortcut to work, this works
    //connect(addIMarker, &QAction::triggered, this, &MainWindow::addMarkerI);
    connect(addIMarkerShortcut, &QShortcut::activated, this, &MainWindow::addMarkerI);

    deleteMarker = new QAction(tr("&Delete Marker(s)"), this);
    deleteMarker->setShortcut(QKeySequence::Delete);
    deleteMarker->setStatusTip(tr("Delete Marker(s)"));
    deleteMarkerShortcut = new QShortcut(QKeySequence::Delete, this);
    //connect(deleteMarker, &QAction::triggered, this, &MainWindow::markerDelete);
    connect(deleteMarkerShortcut, &QShortcut::activated, this, &MainWindow::markerDelete);

    rescaleViewAct = new QAction(tr("&Rescale View"), this);
    rescaleViewAct->setShortcut(QKeySequence("CTRL+SHIFT+R"));
    rescaleViewAct->setStatusTip(tr("Rescale View"));
    rescaleViewShortcut = new QShortcut(QKeySequence("CTRL+SHIFT+R"),this); /// Couldn't get the action shortcut to work, this works
    //connect(rescaleViewAct, &QAction::triggered, this, &MainWindow::rescaleView);
    connect(rescaleViewShortcut, &QShortcut::activated, this, &MainWindow::rescaleView);

    /// Currently does nothing
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
    rightClickMenu->addAction(deleteMarker);
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
    //painter.drawPixmap(globalPos, upPix->scaled(32,32,Qt::KeepAspectRatio));

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
    file = QFileDialog::getOpenFileName(this,tr("Open File"),QDir::currentPath(),"CSV files, txt files (*.csv *.txt);;all files (*.*)");

    struct DataStructure data_structure;

    if (!file.isEmpty()) {
        CsvReader csvReader(model);
        csvReader.importCSV(file);
        data_structure = csvReader.exportData(data_structure);

        GraphViewer graphViewer(ui);

        graphViewer.setFirstTime(firstRun);
        graphViewer.createGraph(data_structure.time_values, data_structure.x_acc_values, data_structure.y_acc_values, data_structure.z_acc_values, data_structure.magnitude_values);
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
    }
}

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

            stream << marker_structure.keyPosition[marker_structure.keyPosition.length()-1] << "," << marker_structure.id[marker_structure.id.length()-1];
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

            stream << selection_structure.xAxisKeyMin[selection_structure.xAxisKeyMin.length()-1] << "," << selection_structure.xAxisKeyMax[selection_structure.xAxisKeyMin.length()-1] << "," << selection_structure.xAxisValueMin[selection_structure.xAxisKeyMin.length()-1] << "," << selection_structure.xAxisValueMax[selection_structure.xAxisKeyMin.length()-1];
        }
    }
    //qDebug() << path;
}

void MainWindow::loadMarkers() {
    for (int i = 0; i < marker_structure.keyPosition.length(); i++) {
        xKeyPos = marker_structure.keyPosition[i];
        emit placeMarker(marker_structure.id[i]);
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
        labelText = new QCPItemText(ui->customPlot);
        labelText->setText("Leg Up");
        labelText->setPositionAlignment(Qt::AlignHCenter | Qt::AlignTop);
        labelText->position->setCoords((selection_structure.xAxisKeyMin[i]+selection_structure.xAxisKeyMax[i])/2, 1.9);
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
        rect->setBrush(QColor(225, 0, 0, 30));
        rect->setPen(QColor(225, 0, 0, 30));
        rect->setSelected(false);
        /// NEED TO SAVE THESE COORDINATES SOMEWHERE TO SAVE
        rect->topLeft->setCoords(xAxisKeyMin, floor(xAxisValueMin));
        rect->bottomRight->setCoords(xAxisKeyMax, ceil(xAxisValueMax));
        selection_structure.xAxisKeyMin.append(xAxisKeyMin);
        selection_structure.xAxisKeyMax.append(xAxisKeyMax);
        selection_structure.xAxisValueMin.append(xAxisValueMin);
        selection_structure.xAxisValueMax.append(xAxisValueMax);
        labelText = new QCPItemText(ui->customPlot);
        /// Allows deletion of label when rect is deleted. But causes Segmentation Fault. Fix.
        //labelText->setParent(rect);
        //labelText->setSelectable(false);
        labelText->setText("Leg Up");
        labelText->setPositionAlignment(Qt::AlignHCenter | Qt::AlignTop);
        labelText->position->setCoords((xAxisKeyMin+xAxisKeyMax)/2, 1.9);
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
    ui->customPlot->rescaleAxes(true);
    /// Hard coded y range
    ui->customPlot->yAxis->setRange(3,-3);
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
void MainWindow::placeMarker(double ID)
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

void MainWindow::markerDelete()
{
    // ItemClick?
    // selectTest?
    itemsSelected = ui->customPlot->selectedItems().count();
    for (int i = 0; i < itemsSelected; i++)
    {
        //delete ui->customPlot->selectedItems().at(0);
        //ui->customPlot->mItems.removeOne(item);
        //qDebug() << (ui->customPlot->selectedItems().at(0))->metaObject()->className();
        /// Might be a better way to do this, but for now it can delete the child Text connected to the Rect
        /*if (strcmp((ui->customPlot->selectedItems().at(0))->metaObject()->className(), "QCPItemRect") == 0)
        {
            ui->customPlot->removeItem(ui->customPlot->selectedItems().at(0)->findChild<QCPItemText*>("lText"));
        }*/
        //ui->customPlot->item()
        ui->customPlot->removeItem(ui->customPlot->selectedItems().at(0));
        //delete ui->customPlot->selectedItems().at(0);
    }
    //ui->customPlot->clearItems();
    ui->customPlot->replot();
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
        deleteMarker->setEnabled(true);
    }
    else
    {
        deleteMarker->setEnabled(false);
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
        else if (selectedItem->text().contains("Delete Marker(s)"))
        {
            emit markerDelete();
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

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "CLOSING";
    QMainWindow::closeEvent(event);
    emit saveMarkers();
    emit saveSelections();
}
