#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "markerpopup.h"

#include <QLCDNumber>
#include <QObject>
#include <QTimer>

#include <QMessageBox>
#include <QTextStream>
#include <QList>
#include <QStringList>
#include <QDir>

#include <QKeyEvent>
#include <QList>
#include <QString>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QMouseEvent> /// added mouse event
#include <QCursor> /// added cursor


#include <iostream>
#include <iomanip>

const int COLUMN_NUM = 7; /// use 4 if no gyroscope data

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);// counter on UI

    editwindowpt = new editwindow(this);
    editwindowpt->show();//Launch LOGIN window
    editwindowpt->setModal(true);

    parampt = new Parameters(this);//Initialize Parameter Window

    //
    //
    //
    // generate some data:
    // set locale to english, so we get english month names:
    ui->customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    // seconds of current time, we'll use it as starting point in time for data:
    double now = QDateTime::currentDateTime().toTime_t();
    srand(8); // set the random seed, so we always get the same random data

    /// need to allow user to correctly store to filepath when using "Open"
    QString filePath = QCoreApplication::applicationDirPath() + "/A0E6F8B70300_raw_data.csv";

    QFile file(filePath); // this needs to be changed to be a more mobile handle
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
           qDebug() << file.errorString();
       }

    QStringList wordList;
    QStringList datavalue;
    while (!file.atEnd()){ //runs through the end of the .csv file
        QString line = file.readLine();

        datavalue << line.split(',', QString::SkipEmptyParts); //parses each line by omitting commas


    }
    /// NEED RAW DATA FILE (check if first datavalue is "newline char"
    int cct = 1; /// if headers use "cct = 7;", "cct = 0" if newline char, and may be reduced to only accelerometer data (4 columns)
    int ind = 0;
    int dataNum = ((datavalue.length() - cct) / 7) - 1; /// computes how many total data values
    float arr[COLUMN_NUM][dataNum];
    /// float arr[5][450]; /// 5 parameters? 450 hard coded rows of data
    QString minussign = "-";
    foreach (QString i, datavalue) //loops through the stringlist, converts each string to a float, and adds it into 2D array
    {
        if (cct%7== 1)
        {
            arr[0][ind] = i.toFloat(); /// figure out how to store timestamps
        }
        else if (cct%7== 2) //row 2 data, most likely accelerometer mag
        {
            if (i.left(1) == minussign){ /// goes through each field and removes negative sign to get magnitude
                i.remove(0,1);
            }
            i.remove(7,5);
            arr[1][ind] = i.toFloat(); /// also removes anything past 5 decimal places (why remove E-##?)
        }
        else if (cct%7== 3) // row 3, etc...
        {
            if (i.left(1) == minussign){
                i.remove(0,1);
            }
            i.remove(7,5);
            arr[2][ind] = i.toFloat();
        }
        else if (cct%7== 4)
        {
            if (i.left(1) == minussign){
                i.remove(0,1);

            }
            i.remove(7,5);
            arr[3][ind] = i.toFloat();
        }
        else if (cct%7== 5)
        {
            if (i.left(1) == minussign){
                i.remove(0,1);

            }
            i.remove(7,5);
            arr[4][ind] = i.toFloat();
        }
        else if (cct%7 == 6)
        {
            if (i.left(1) == minussign){
                i.remove(0,1);

            }
            i.remove(7,5);
            arr[5][ind] = i.toFloat();
        }
        else if ((cct > 0) && (cct%7 == 0))
        {
            if (i.left(1) == minussign){
                i.remove(0,1);

            }
            i.remove(7,5);
            arr[6][ind] = i.toFloat();
            ind++; /// increment for last column check
        }
        cct++;
    }

    file.close();

    //END of csv extractor


    //QString filePath2 = QCoreApplication::applicationDirPath() + "/testdata/test.txt";
    //this->getRawData(filePath2);




    // create multiple graphs:
    for (int gi=0; gi<COLUMN_NUM; ++gi)
    {

        ui->customPlot->addGraph();
        QColor color(10+40*gi,250-40*gi, 150, 150);
        /// QColor color(10+200/4.0*gi,70*(1.6-gi/4.0), 150, 150);
        ui->customPlot->graph()->setLineStyle(QCPGraph::lsLine);
        ui->customPlot->graph()->setPen(QPen(color.lighter(200)));
        ui->customPlot->graph()->setBrush(QBrush(color));

        /// need to use actual data with real time values
        // generate random walk data:
        QVector<QCPGraphData> timeData(450); /// hard coded with test_data.csv size, need to compute row length dynamically

        for (int i=0; i<450; ++i)
        {
          timeData[i].key = i;


          timeData[i].value = arr[2][i]; /// changed to [2] from [1]

        }
        ui->customPlot->graph()->data()->set(timeData);
    }


    //Tab2-5 code,
    //this is for the new tabs. Need to find a way on how to change the pointers via a variable. For now, Im doing this manually
    ui->customPlot_2->addGraph();
    QColor color2(55,180, 150, 150);
    ui->customPlot_2->graph()->setLineStyle(QCPGraph::lsLine);
    ui->customPlot_2->graph()->setPen(QPen(color2.lighter(200)));
    ui->customPlot_2->graph()->setBrush(QBrush(color2));

    ui->customPlot_3->addGraph();
    QColor color3(20+200/8,90, 150, 150);
    ui->customPlot_3->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot_3->graph(0)->setPen(QPen(color3.lighter(200)));
    ui->customPlot_3->graph(0)->setBrush(QBrush(color3));

    ui->customPlot_4->addGraph();
    QColor color4(20+200/12,45, 150, 150);
    ui->customPlot_4->graph()->setLineStyle(QCPGraph::lsLine);
    ui->customPlot_4->graph()->setPen(QPen(color4.lighter(200)));
    ui->customPlot_4->graph()->setBrush(QBrush(color4));

    ui->customPlot_5->addGraph();
    QColor color5(20+200/16,0 , 150, 150);
    ui->customPlot_5->graph()->setLineStyle(QCPGraph::lsLine);
    ui->customPlot_5->graph()->setPen(QPen(color5.lighter(200)));
    ui->customPlot_5->graph()->setBrush(QBrush(color5));
    QVector<QCPGraphData> timeData2(450);QVector<QCPGraphData> timeData3(450);QVector<QCPGraphData> timeData4(450);QVector<QCPGraphData> timeData5(450);

    for (int i=0; i<450; ++i)
    {

      timeData2[i].key = i; timeData3[i].key = i; timeData4[i].key = i; timeData5[i].key = i;


      timeData2[i].value = arr[2][i]; /// changed to [2]...[5] from [1]...[4]
      timeData3[i].value = arr[3][i];
      timeData4[i].value = arr[4][i];
      timeData5[i].value = arr[5][i];
    }
    ui->customPlot_2->graph()->data()->set(timeData2);
    ui->customPlot_3->graph(0)->data()->set(timeData3);
    ui->customPlot_4->graph()->data()->set(timeData4);
    ui->customPlot_5->graph()->data()->set(timeData5);
    //END of Tab2-5 code


    //add test stand up flags
    QVector<QCPGraphData> timeData6(75);
    ui->customPlot_3->addGraph();
    ui->customPlot_3->graph(1)->setPen(QPen(Qt::red));
    ui->customPlot_3->graph(1)->setBrush(QBrush(QColor(255, 0, 0, 75)));
    ui->customPlot_3->graph(1)->setName("Standing...");
    for (int i=0; i<75; ++i)
    {
        timeData6[i].key = i + 75;
        timeData6[i].value = 11;

    }
    ui->customPlot_3->graph(1)->data()->set(timeData6);
    // add the text label for standing
    QCPItemText *wavePacketText = new QCPItemText(ui->customPlot_3);
    wavePacketText->position->setCoords(112,7.5); // move 10 pixels to the top from bracket center anchor
    wavePacketText->setPositionAlignment(Qt::AlignBottom|Qt::AlignHCenter);
    wavePacketText->setText("Standing...");
    wavePacketText->setFont(QFont(font().family(), 10, QFont::Bold));
    wavePacketText->setColor(QColor(140,10,10,180));
    //END OF TEST FLAG (plot3)

    // add a phase tracer which sticks to graph data
    QCPItemTracer *phaseTracer = new QCPItemTracer(ui->customPlot_3);
    phaseTracer->setGraph(ui->customPlot_3->graph(0));
    int graphk = 200;
    phaseTracer->setGraphKey(graphk);
    phaseTracer->setInterpolating(true);
    phaseTracer->setStyle(QCPItemTracer::tsCircle);
    phaseTracer->setPen(QPen(Qt::red));
    phaseTracer->setBrush(Qt::red);
    phaseTracer->setSize(10);
    // add label for phase tracer:
    QCPItemText *phaseTracerText = new QCPItemText(ui->customPlot_3);
    phaseTracerText->position->setType(QCPItemPosition::ptPlotCoords);
    phaseTracerText->position->setCoords(graphk+25,(arr[2][graphk])-0.2);
    QString dummytext = QString("Flag - X: %1, Y: %2").arg(graphk).arg(arr[2][graphk]);
    phaseTracerText->setText(dummytext);
    phaseTracerText->setTextAlignment(Qt::AlignLeft);
    phaseTracerText->setFont(QFont(font().family(), 9));
    phaseTracerText->setPadding(QMargins(8, 0, 0, 0));



    //Axis Formatting Code
    /// need to put all of this into a function called FormatAxis(params);
    // configure bottom axis to show date instead of number:
    QSharedPointer<QCPAxisTickerTime> dateTicker(new  QCPAxisTickerTime);
    dateTicker->setTimeFormat("day %d\n%h:%m:%s"); //this sets by day # & not by date
    ui->customPlot->xAxis->setTicker(dateTicker);
    // configure left axis text labels:
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTick(2, "a bit\nlow"); /// hard coded labels
    textTicker->addTick(8, "quite\nhigh");
    ui->customPlot->yAxis->setTicker(textTicker);
    // set a more compact font size for bottom and left axis tick labels:
    ui->customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    ui->customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    // set axis labels:
    ui->customPlot->xAxis->setLabel("Date");
    ui->customPlot->yAxis->setLabel("Random wobbly lines value");
    // make top and right axes visible but without ticks and labels:
    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTicks(true);
    ui->customPlot->yAxis2->setTicks(false);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setTickLabels(false);
    // set axis ranges to show all data:
    ui->customPlot->xAxis->setRange(0, 600); /// Need Dynamic Code for ranges
    ui->customPlot->yAxis->setRange(0, 10);

    ui->customPlot_2->xAxis->setRange(0, 199);
    ui->customPlot_2->yAxis->setRange(0, 10);
    ui->customPlot_3->xAxis->setRange(0, 449);
    ui->customPlot_3->yAxis->setRange(0, 10);
    ui->customPlot_4->xAxis->setRange(0, 449);
    ui->customPlot_4->yAxis->setRange(0, 10);
    ui->customPlot_5->xAxis->setRange(0, 449);
    ui->customPlot_5->yAxis->setRange(0, 10);
    // show legend with slightly transparent background brush:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 150));
    //END of axis formatting

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                      QCP::iSelectLegend | QCP::iSelectPlottables | QCP::iMultiSelect);

    ui->customPlot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                      QCP::iSelectLegend | QCP::iSelectPlottables);
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->customPlot, SIGNAL(leftMousePress(QMouseEvent*)), this, SLOT(leftMousePress()));
    connect(ui->customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    markerPopup = new MarkerPopup(this);
    labelPopup = new LabelPopup(this);




    connect (timer, SIGNAL(timeout()), this, SLOT(myfunction())); //connected here
    timer -> start(100); //100ms watchdog

    /// disables the paint tool
    connect(this, SIGNAL(toolbutton2_trig()), this, SLOT(on_toolButton_clicked()));//this clicks the button to disable functions when another toolbutton is being pressed
    connect(this, SIGNAL(toolbutton3_trig()), this, SLOT(on_toolButton_clicked()));
    /// disables the marker tool
    connect(this, SIGNAL(toolbutton_trig()), this, SLOT(on_toolButton_2_clicked()));
    connect(this, SIGNAL(toolbutton3_trig()), this, SLOT(on_toolButton_2_clicked()));
    /// disables the hand tool
    connect(this, SIGNAL(toolbutton_trig()), this, SLOT(on_toolButton_3_clicked()));
    connect(this, SIGNAL(toolbutton2_trig()), this, SLOT(on_toolButton_3_clicked()));



    //connect(ui->customPlot_5, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(mouseRelease()));

}

int num = 0;
QVector<QCPGraphData> yeahok;





MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myfunction() //counter code thats called up when watchdog is triggered
{
    num = num + 1;
    if (num > 100)
        num = 0;
    ui->progressBar->setValue(num);
    ui->lcdNumber->display(num);

}

void MainWindow::markerfc(QStringList popupData){
    qDebug() << "Comment:" << popupData[3];
    QString comment = popupData[3];
    QCPDataSelection selection = ui->customPlot->graph(0)->selection();
    qDebug() << selection.dataRanges();
    QCPGraphDataContainer::const_iterator begin;QCPGraphDataContainer::const_iterator end;
    foreach (QCPDataRange dataRange, selection.dataRanges())
    {
        QCPGraphDataContainer::const_iterator beginloop = ui->customPlot->graph()->data()->at(dataRange.begin()); // get range begin iterator from index
        QCPGraphDataContainer::const_iterator endloop = ui->customPlot->graph()->data()->at(dataRange.end()); // get range end iterator from index
        begin = beginloop; end = endloop;
//        int j =0;
//        for (QCPGraphDataContainer::const_iterator it=begin; it!=end; ++it)
//        {
//            // iterator "it" will go through all selected data points, as an example, we calculate the value average
//            qDebug() << it->key;
//            flagdata[j].key = it->key;
//            flagdata[j].value = 11;
//            j++;

//        }
    }

    QCPItemRect *rect = new QCPItemRect(ui->customPlot);
    //ui->customPlot_5->set(rect);
    QString redstr = popupData[0];QString greenstr = popupData[1];QString bluestr = popupData[2];
    int red = redstr.toInt();int green = greenstr.toInt();int blue = bluestr.toInt();
    rect->setBrush(QColor(red, green, blue, 75));
    rect->setPen(QColor(red,green,blue, 75));
    rect->setSelected(false);
    rect->topLeft->setCoords(begin->key,11);
    rect->bottomRight->setCoords(end->key,0);
    //clear();
    selection.clear();
}

void MainWindow::labelfc(QStringList popupData){
    qDebug() << "Comment:" << popupData[1];
    QString comment = popupData[1];
    qDebug() << "Combobox: " << popupData[0];
    //ui->customPlot_5->clearItems();
    QCPItemTracer *labelTracer = new QCPItemTracer(ui->customPlot);
    labelTracer->setGraph(ui->customPlot->graph());


    QCPDataSelection selection = ui->customPlot->graph()->selection();
    qDebug() << selection.dataRanges();
    QCPGraphDataContainer::const_iterator begin;
    foreach (QCPDataRange dataRange, selection.dataRanges())
    {
        QCPGraphDataContainer::const_iterator beginloop = ui->customPlot->graph()->data()->at(dataRange.begin()); // get range begin iterator from index
        QCPGraphDataContainer::const_iterator endloop = ui->customPlot->graph()->data()->at(dataRange.end()); // get range end iterator from index
        begin = beginloop;
    }

    labelTracer->setGraphKey(begin->key);
    labelTracer->setInterpolating(false);
    if (popupData[0] == "Square"){
        labelTracer->setStyle(QCPItemTracer::tsSquare);
    }
    else if (popupData[0] == "Circle"){
        labelTracer->setStyle(QCPItemTracer::tsCircle);
    }
    labelTracer->setPen(QPen(Qt::green));
    labelTracer->setBrush(Qt::green);
    labelTracer->setSize(8);

    int j;
    QCPAbstractItem *what = ui->customPlot->item(j);
    qDebug() << "Itm lblfc1 index: "<< j;

}


void MainWindow::on_lcdNumber_overflow()
{
    num = 0;
}

void MainWindow::on_pushButton_2_clicked() // reset pushbutton
{
    num = 0;
    ui->lcdNumber->display(num);
}

/*void plotspace::ShowContextMenu(const QPoint &pos)
{
   QMenu contextMenu(tr("Context menu"), this);

   QAction action1("Remove Data Point", this);
   connect(&action1, SIGNAL(triggered()), this, SLOT(removeDataPoint()));
   contextMenu.addAction(&action1);

   contextMenu.exec(mapToGlobal(pos));
}*/

void MainWindow::ShowContextMenu(const QPoint& pos) // this is a slot
{
    // for most widgets
    QPoint globalPos = ui->customPlot->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    myMenu.addAction("View Selection");
    myMenu.addAction("Undo View Selected");
    myMenu.addAction("Cancel");
    // ...

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem == "View Selection")
    {
        // something was chosen, do stuff
        //ui->customPlot->setSelectionRectMode(QCP::srmZoom);
        //ui->customPlot->graph(0)->setSelectable(QCP::stDataRange);
    }
    else
    {
        // nothing was chosen
    }
}

void MainWindow::rightMousePress()
{
    const QPoint cursorLoc = ui->customPlot->mapFromGlobal(QCursor::pos());
    emit ShowContextMenu(cursorLoc);
}

void MainWindow::leftMousePress()
{
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

    /// Default range drag to be only horizontal
    if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->xAxis->orientation());
    else if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->xAxis->orientation());
        ///ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->yAxis->orientation());
    else
        ui->customPlot->axisRect()->setRangeDrag(Qt::Horizontal);

}

void MainWindow::mouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeZoom(ui->customPlot->xAxis->orientation());
  else if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeZoom(ui->customPlot->yAxis->orientation());
  else
    ui->customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}


void MainWindow::on_toolButton_clicked() //MARKER TOOL
{

    //shortcut = new QShortcut(QKeySequence(Qt::Key_Return),this,SLOT(markerfc())); shortcut->setAutoRepeat(false);

    if (ui->toolButton->isChecked() == true){
        emit toolbutton_trig();
        qDebug() << "MarkerTool: toggled";

        //SELECTION CODE
        //ui->customPlot_4->setInteractions(QCP::iSelectPlottables | QCP::iMultiSelect);
        //ui->customPlot_4->setMultiSelectModifier(Qt::ShiftModifier);
        //ui->customPlot_4->setSelectionRectMode(QCP::srmSelect);
        //ui->customPlot_4->graph(0)->setSelectable(QCP::stDataRange);//QCP::SelectionType(QCP::stDataRange)

        ui->customPlot->setSelectionRectMode(QCP::srmSelect);
        ui->customPlot->graph(0)->setSelectable(QCP::stDataRange);//QCP::SelectionType(QCP::stDataRange)

//        //SELECTION STYLE CODE IF NEEDED
//        QCPSelectionDecorator *selectiondec2 = new QCPSelectionDecorator();
//        QPen penstyle2; penstyle2.setWidth(10);penstyle2.setBrush(Qt::green);
//        selectiondec2->setPen(penstyle2);
//        QBrush brushstyle2; brushstyle2.setColor(Qt::green);
//        selectiondec2->setBrush(brushstyle2);
//        ui->customPlot_4->graph()->setSelectionDecorator(selectiondec2);

        connect(this, SIGNAL(EnterIsPressed()), markerPopup, SLOT(exec()));
        connect(this, SIGNAL(MarkerNameInfo(QString)), markerPopup, SLOT(setTagName(QString)));
        emit MarkerNameInfo("12345");
        connect(markerPopup, SIGNAL(markerDataSend(QStringList)), this, SLOT(markerfc(QStringList)));
        /// added connect for mouse press to be able to handle right mouse click
        connect(ui->customPlot, SIGNAL(rightMousePress(QMouseEvent*)), this, SLOT(rightMousePress()));
        ui->customPlot->setContextMenuPolicy(Qt::CustomContextMenu);

        connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ShowContextMenu(const QPoint &)));



// MIGHT FIND A USE FOR THIS IF WE NEED TO PARSE THRU SELECTION
//        while (~(ui->customPlot_4->graph(0)->selected())){
//            selection = ui->customPlot_4->graph(0)->selection();

//            int wtv = selection.dataPointCount();
//            qDebug() << wtv;
//            QVector<QCPGraphData> flagdata(wtv);
//            qDebug() << selection.dataRanges();

//            foreach (QCPDataRange dataRange, selection.dataRanges())
//            {
//                QCPGraphDataContainer::const_iterator begin = ui->customPlot_4->graph()->data()->at(dataRange.begin()); // get range begin iterator from index
//                QCPGraphDataContainer::const_iterator end = ui->customPlot_4->graph()->data()->at(dataRange.end()); // get range end iterator from index
//                int j =0;
//                for (QCPGraphDataContainer::const_iterator it=begin; it!=end; ++it)
//                {
//                    // iterator "it" will go through all selected data points, as an example, we calculate the value average
//                    qDebug() << it->key;
//                    flagdata[j].key = it->key;
//                    flagdata[j].value = 11;
//                    j++;

//                }
//            }
//            yeahok = flagdata;
//        }
    }
    else{
        qDebug() << "MarkerTool: un-toggled";
        //ui->customPlot_4->setSelectionRectMode(QCP::srmNone);
        //ui->customPlot_4->graph(0)->setSelectable(QCP::stNone);

        ui->customPlot->setSelectionRectMode(QCP::srmNone);
        ui->customPlot->graph(0)->setSelectable(QCP::stNone);
        //disconnect(this, SIGNAL(EnterIsPressed()), this, SLOT(markerfc()));
        disconnect(this, SIGNAL(EnterIsPressed()), markerPopup, SLOT(exec()));
        disconnect(this, SIGNAL(MarkerNameInfo(QString)), markerPopup, SLOT(setTagName(QString)));
        disconnect(markerPopup, SIGNAL(markerDataSend(QStringList)), this, SLOT(markerfc(QStringList)));
        /// added disconnect for mouse press to be able to handle right mouse click
        disconnect(ui->customPlot, SIGNAL(rightMousePress()), this, SLOT(rightMousePress()));
        disconnect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ShowContextMenu(const QPoint &)));


    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_Enter | Qt::Key_Return )
    {
        emit EnterIsPressed();

    }
}
void MainWindow::mouseRelease()
{
    if (ui->toolButton_2->isChecked() == true){
       emit MouseIsReleased();
       qDebug() << "Mouse has been released.";
    }

}



void MainWindow::on_toolButton_2_clicked() //LABEL TOOL
{
    labelTracerTemp = new QCPItemTracer(ui->customPlot);
    if (ui->toolButton_2->isChecked() == true){
        qDebug() << "LabelTool: toggled";
        emit toolbutton2_trig();

        //SELECTION CODE
        //ui->customPlot_5->setInteractions(QCP::iSelectPlottables | QCP::iMultiSelect);
        //ui->customPlot_5->setSelectionRectMode(QCP::srmSelect);
        //ui->customPlot_5->graph(0)->setSelectable(QCP::stSingleData);
        //connect(ui->customPlot_5->graph(), SIGNAL(selectionChanged(bool)), this, SLOT(addLabelSelection()));
        //connect(this, SIGNAL(MouseIsReleased()), this, SLOT(addLabelSelection()));


        //ui->customPlot->setInteractions(QCP::iSelectPlottables | QCP::iMultiSelect);
        //ui->customPlot_5->setSelectionRectMode(QCP::srmSelect);
        ui->customPlot->graph()->setSelectable(QCP::stSingleData);
        connect(ui->customPlot->graph(), SIGNAL(selectionChanged(bool)), this, SLOT(addLabelSelection()));

//        //SELECTION STYLE IF NEEDED
//        QCPSelectionDecorator *selectiondec2 = new QCPSelectionDecorator();
//        QPen penstyle2; penstyle2.setWidth(10);penstyle2.setBrush(Qt::green);
//        selectiondec2->setPen(penstyle2);
//        QBrush brushstyle2; brushstyle2.setColor(Qt::green);
//        selectiondec2->setBrush(brushstyle2);
//        ui->customPlot_5->graph()->setSelectionDecorator(selectiondec2);

        //QCPDataSelection selection = ui->customPlot_5->graph(0)->selection();
        //qDebug() << selection.dataRanges();

        //declaring selection tracer pointer to be able to delete after every
        //selection

        labelTracerTemp->setGraph(ui->customPlot->graph());
        labelTracerTemp->setGraphKey(5.0);
        labelTracerTemp->setInterpolating(false);
        labelTracerTemp->setStyle(QCPItemTracer::tsPlus);
        labelTracerTemp->setPen(QPen(Qt::red));
        labelTracerTemp->setBrush(Qt::red);
        labelTracerTemp->setSize(8);





        connect(this, SIGNAL(EnterIsPressed()), labelPopup, SLOT(exec()));
        connect(this, SIGNAL(LabelNameInfo(QString)), labelPopup, SLOT(setTagName(QString)));
        emit LabelNameInfo("12345");
        connect(labelPopup, SIGNAL(labelDataSend(QStringList)), this, SLOT(labelfc(QStringList)));

    }
    else {
        //ui->customPlot_5->setSelectionRectMode(QCP::srmNone);

        //ui->customPlot_5->graph(0)->setSelectable(QCP::stNone);  GRAPH1 Transfer
        ui->customPlot->graph(0)->setSelectable(QCP::stNone);
        labelTracerTemp->setGraphKey(0.0);
        //disconnect(ui->customPlot_5->graph(), SIGNAL(selectionChanged(bool)), this, SLOT(addLabelSelection()));  GRAPH 1 TRANSFER
        disconnect(ui->customPlot->graph(), SIGNAL(selectionChanged(bool)), this, SLOT(addLabelSelection()));

        disconnect(this, SIGNAL(EnterIsPressed()), labelPopup, SLOT(exec()));
        disconnect(this, SIGNAL(LabelNameInfo(QString)), labelPopup, SLOT(setTagName(QString)));
        //disconnect(this, SIGNAL(MouseIsReleased()), this, SLOT(addLabelSelection()));
        disconnect(labelPopup, SIGNAL(labelDataSend(QStringList)), this, SLOT(labelfc(QStringList)));
    }
}

void MainWindow::on_toolButton_3_clicked() //HAND TOOL
{
    if (ui->toolButton_3->isChecked() == true){
        emit toolbutton3_trig();
    }
    else{


    }
}

void MainWindow::addLabelSelection(){ //THIS NEEDS DEBUGGING TO FIND ITEM INDEX AND CORRECTLY DELETE SELECTION TRACER ITEM
//    int i;
//    i = ui->customPlot_5->itemCount();
//    qDebug() << "Itm Count: "<< i;
//    if (i > 0){
//        int j;
//        QCPAbstractItem *what = ui->customPlot_5->item(j);
//        //ui->customPlot_5->removeItem(j);
//        qDebug() << "Itm j index: "<< j;
//    }

//    QCPItemTracer *labelTracerTemp = new QCPItemTracer(ui->customPlot_5);//declaring selection tracer pointer to be able to delete after every
//    //selection
//    labelTracerTemp->setGraph(ui->customPlot_5->graph(0));





    QCPDataSelection selection = ui->customPlot->graph()->selection();
    qDebug() << selection.dataRanges();
    QCPGraphDataContainer::const_iterator begin;
    foreach (QCPDataRange dataRange, selection.dataRanges())
    {
        QCPGraphDataContainer::const_iterator beginloop = ui->customPlot_5->graph()->data()->at(dataRange.begin()); // get range begin iterator from index
        //QCPGraphDataContainer::const_iterator endloop = ui->customPlot_5->graph()->data()->at(dataRange.end()); // get range end iterator from index
        begin = beginloop;
    }

    labelTracerTemp->setGraphKey(begin->key);

    ui->customPlot->replot();

    int i;
    i = ui->customPlot->itemCount();
    qDebug() << "Itm Count: "<< i;

    int j;
    QCPAbstractItem *what = ui->customPlot->item(j);
    qDebug() << "Itm selec index: "<< j;
}

//void MainWindow::getRawData(QString filePath){

//    QFile file(filePath); // this needs to be changed to be a more mobile handle
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//           qDebug() << file.errorString();
//       }

//    QStringList wordList;
//    QStringList datavalue;
//    while (!file.atEnd()){ //runs through the end of the .csv file
//        QString line = file.readLine();

//        datavalue << line.split(',', QString::SkipEmptyParts); //parses each line by omitting commas


//    }
//    int cct = 0;
//    int cindex = 0;
//    double arr[9][506];
//    QString minussign = "-";
//    foreach (QString i, datavalue) //loops through the stringlist, converts each string to a float, and adds it into 2D array
//    {
//        qDebug() << i;
//        if (cct > 0){
//            double test = cct/11;
//            cindex = qFloor(test);
//        }
//        if (cct%11 == 0) //row 1 data, most likely time stamp
//        {
//            if (i.left(1) == minussign){
//                i.remove(0,1);
//                int tempint = i.toDouble();
//                tempint = tempint * -1;
//                arr[0][cindex] = tempint;
//            }
//            else{
//                arr[0][cindex] = i.toDouble();
//            }

//        }
//        else if (cct%11 == 1) //row 2 data, most likely raw mag x axis
//        {
//            i.remove(0,1);
//            if (i.left(1) == minussign){
//                i.remove(0,1);
//                int tempint = i.toDouble();
//                tempint = tempint * -1;
//                arr[1][cindex] = tempint;
//                qDebug() << tempint;
//            }
//            else{
//                arr[1][cindex] = i.toDouble();
//                int tempint = i.toDouble();
//                qDebug() << tempint;
//            }

//        }
//        else if (cct%11 == 2)
//        {
//            i.remove(0,1);
//            if (i.left(1) == minussign){
//                i.remove(0,1);
//                int tempint = i.toDouble();
//                tempint = tempint * -1;
//                arr[2][cindex] = tempint;
//            }
//            else{
//                arr[2][cindex] = i.toDouble();
//            }

//        }
//        else if (cct%11 == 3)
//        {
//            i.remove(0,1);
//            if (i.left(1) == minussign){
//                i.remove(0,1);
//                int tempint = i.toDouble();
//                tempint = tempint * -1;
//                arr[3][cindex] = tempint;
//            }
//            else{
//                arr[3][cindex] = i.toDouble();
//            }

//        }
//        else if (cct%11 == 4)
//        {
//            i.remove(0,1);
//            if (i.left(1) == minussign){
//                i.remove(0,1);
//                int tempint = i.toDouble();
//                tempint = tempint * -1;
//                arr[4][cindex] = tempint;
//            }
//            else{
//                arr[4][cindex] = i.toDouble();
//            }

//        }
//        else if (cct%11 == 5)
//        {
//            i.remove(0,1);
//            if (i.left(1) == minussign){
//                i.remove(0,1);
//                int tempint = i.toDouble();
//                tempint = tempint * -1;
//                arr[5][cindex] = tempint;
//            }
//            else{
//                arr[5][cindex] = i.toDouble();
//            }

//        }
//        else if (cct%11 == 6)
//        {
//            i.remove(0,1);
//            if (i.left(1) == minussign){
//                i.remove(0,1);
//                int tempint = i.toDouble();
//                tempint = tempint * -1;
//                arr[6][cindex] = tempint;
//            }
//            else{
//                arr[6][cindex] = i.toDouble();
//            }

//        }
//        else if (cct%11 == 7)
//        {
//            i.remove(0,1);
//            if (i.left(1) == minussign){
//                i.remove(0,1);
//                int tempint = i.toDouble();
//                tempint = tempint * -1;
//                arr[7][cindex] = tempint;
//            }
//            else{
//                arr[7][cindex] = i.toDouble();
//            }

//        }
//        else if (cct%11 == 8)
//        {
//            i.remove(0,1);
//            if (i.left(1) == minussign){
//                i.remove(0,1);
//                int tempint = i.toDouble();
//                tempint = tempint * -1;
//                arr[8][cindex] = tempint;
//            }
//            else{
//                arr[8][cindex] = i.toDouble();
//            }

//        }
//        else if (cct%11 == 9)
//        {
//            i.remove(0,1);
//            if (i.left(1) == minussign){
//                i.remove(0,1);
//                int tempint = i.toDouble();
//                tempint = tempint * -1;
//                arr[9][cindex] = tempint;
//            }
//            else{
//                arr[9][cindex] = i.toDouble();
//            }

//        }
//        else{

//            qDebug() << "ind:" << cindex;
//        }

//        cct++;
//        //qDebug() << "cct:" << cct;


//    }

//    file.close();
//    //emit rawDataSig(arr);
//}



void MainWindow::on_actionLogin_triggered()
{
    editwindowpt->show();//Launch LOGIN window
    editwindowpt->setModal(true);
}

void MainWindow::on_actionParameter_triggered()
{
    parampt->show();//Launch PARAMETERS window
    parampt->setModal(true);
}

void MainWindow::on_actionExit_triggered()
{
    close();
}
