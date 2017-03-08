#include "graphviewer.h"

GraphViewer::GraphViewer(Ui::MainWindow *input) {
    first_time = true;
    main_window_ui = input;
}

void GraphViewer::createGraph(QVector<double> time_values, QVector<double> x_acc_values, QVector<double> y_acc_values, QVector<double> z_acc_values, QVector<double> normalized_values) {

    if (first_time) {
        main_window_ui->customPlot->addGraph();
        main_window_ui->customPlot->addGraph();
        main_window_ui->customPlot->addGraph();
        main_window_ui->customPlot->addGraph();
        first_time = false;
    }

    main_window_ui->customPlot->legend->setVisible(true);
    main_window_ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);
    main_window_ui->customPlot->graph(0)->setData(time_values, x_acc_values);
    main_window_ui->customPlot->graph(0)->setPen(QPen(Qt::blue, 1, Qt::DotLine));
    main_window_ui->customPlot->graph(0)->setName("X Acceleration");
    main_window_ui->customPlot->graph(1)->setData(time_values, y_acc_values);
    main_window_ui->customPlot->graph(1)->setPen(QPen(Qt::red, 1, Qt::DotLine));
    main_window_ui->customPlot->graph(1)->setName("Y Acceleration");
    main_window_ui->customPlot->graph(2)->setData(time_values, z_acc_values);
    main_window_ui->customPlot->graph(2)->setPen(QPen(Qt::green, 1, Qt::DotLine));
    main_window_ui->customPlot->graph(2)->setName("Z Acceleration");
    main_window_ui->customPlot->graph(3)->setData(time_values, normalized_values);
    main_window_ui->customPlot->graph(3)->setPen(QPen(Qt::black, 2));
    main_window_ui->customPlot->graph(3)->setName("Normalized Acceleration");

    main_window_ui->customPlot->xAxis->setLabel("time (milliseconds)");
    main_window_ui->customPlot->yAxis->setLabel("acceleration (g's)");

    main_window_ui->customPlot->xAxis->setRange(0, time_values.back() + time_values.back()/20);
    main_window_ui->customPlot->yAxis->setRange(-2, 2);

    // Show Legend
    main_window_ui->customPlot->legend->setVisible(true);
    main_window_ui->customPlot->legend->setBrush(QColor(255, 255, 255, 150));

    // Set Interactions
    /// May not need multiselect when we have one graph
    main_window_ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                          QCP::iSelectLegend | QCP::iSelectPlottables | QCP::iMultiSelect);

    // Set Range Drag and Zoom
    main_window_ui->customPlot->axisRect()->setRangeDrag(Qt::Horizontal);
    main_window_ui->customPlot->axisRect()->setRangeZoom(Qt::Horizontal);

    // Setup right click context menu
    main_window_ui->customPlot->setContextMenuPolicy(Qt::ActionsContextMenu); /// correct placement?

    // Add Connections
    /*connect(this, SIGNAL(toolbutton2_trig()), this, SLOT(on_toolButton_clicked()));//this clicks the button to disable functions when another toolbutton is being pressed
    //connect(this, SIGNAL(toolbutton3_trig()), this, SLOT(on_toolButton_clicked()));

    connect(this, SIGNAL(toolbutton_trig()), this, SLOT(on_toolButton_2_clicked()));
    //connect(this, SIGNAL(toolbutton3_trig()), this, SLOT(on_toolButton_2_clicked()));

    //connect(this, SIGNAL(toolbutton_trig()), this, SLOT(on_toolButton_3_clicked()));
    //connect(this, SIGNAL(toolbutton2_trig()), this, SLOT(on_toolButton_3_clicked()));*/

    main_window_ui->customPlot->replot();
}

void GraphViewer::setFirstTime(bool input) {
    first_time = input;
}
/*
void GraphViewer::on_toolButton_clicked()
{
    if (main_window_ui->toolButton->isChecked() == true){
        emit toolbutton_trig();
    }
    else{


    }
}

void GraphViewer::on_toolButton_2_clicked()
{
    if (main_window_ui->toolButton->isChecked() == true){
        emit toolbutton2_trig();
        qDebug() << "MarkerTool: toggled";

        //SELECTION CODE
        //ui->customPlot_4->setInteractions(QCP::iSelectPlottables | QCP::iMultiSelect);
        //ui->customPlot_4->setMultiSelectModifier(Qt::ShiftModifier);
        //ui->customPlot_4->setSelectionRectMode(QCP::srmSelect);
        //ui->customPlot_4->graph(0)->setSelectable(QCP::stDataRange);//QCP::SelectionType(QCP::stDataRange)

        main_window_ui->customPlot->setSelectionRectMode(QCP::srmSelect);
        main_window_ui->customPlot->graph(0)->setSelectable(QCP::stDataRange);//QCP::SelectionType(QCP::stDataRange)

//        //SELECTION STYLE CODE IF NEEDED
//        QCPSelectionDecorator *selectiondec2 = new QCPSelectionDecorator();
//        QPen penstyle2; penstyle2.setWidth(10);penstyle2.setBrush(Qt::green);
//        selectiondec2->setPen(penstyle2);
//        QBrush brushstyle2; brushstyle2.setColor(Qt::green);
//        selectiondec2->setBrush(brushstyle2);
//        ui->customPlot_4->graph()->setSelectionDecorator(selectiondec2);

        //connect(this, SIGNAL(EnterIsPressed()), markerPopup, SLOT(exec()));
        //connect(this, SIGNAL(MarkerNameInfo(QString)), markerPopup, SLOT(setTagName(QString)));
        //emit MarkerNameInfo("12345");
        //connect(markerPopup, SIGNAL(markerDataSend(QStringList)), this, SLOT(markerfc(QStringList)));
    }
    else{
        qDebug() << "MarkerTool: un-toggled";
        //ui->customPlot_4->setSelectionRectMode(QCP::srmNone);
        //ui->customPlot_4->graph(0)->setSelectable(QCP::stNone);

        main_window_ui->customPlot->setSelectionRectMode(QCP::srmNone);
        main_window_ui->customPlot->graph(0)->setSelectable(QCP::stNone);
        //disconnect(this, SIGNAL(EnterIsPressed()), this, SLOT(markerfc()));
        //disconnect(this, SIGNAL(EnterIsPressed()), markerPopup, SLOT(exec()));
        //disconnect(this, SIGNAL(MarkerNameInfo(QString)), markerPopup, SLOT(setTagName(QString)));
        //disconnect(markerPopup, SIGNAL(markerDataSend(QStringList)), this, SLOT(markerfc(QStringList)));


    }
}*/
