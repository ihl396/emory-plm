/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLogin;
    QAction *actionExit;
    QAction *actionParameter;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionDownload;
    QAction *actionInitialize;
    QAction *actionBluetooth_Test;
    QAction *actionCom_Settings;
    QAction *actionWindow_View_Tool;
    QAction *actionMarker_Tool;
    QAction *actionLabel_Tool;
    QWidget *centralWidget;
    QLCDNumber *lcdNumber;
    QProgressBar *progressBar;
    QPushButton *pushButton_2;
    QTabWidget *tabWidget;
    QWidget *Tab1;
    QCustomPlot *customPlot;
    QWidget *Tab2;
    QCustomPlot *customPlot_2;
    QWidget *Tab3;
    QCustomPlot *customPlot_3;
    QWidget *Tab4;
    QCustomPlot *customPlot_4;
    QWidget *Tab5;
    QCustomPlot *customPlot_5;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QMenu *menuOption;
    QMenu *menuOption_2;
    QMenu *menuDevice;
    QMenu *menuAbout;
    QMenu *menuView;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1240, 571);
        MainWindow->setTabShape(QTabWidget::Rounded);
        actionLogin = new QAction(MainWindow);
        actionLogin->setObjectName(QStringLiteral("actionLogin"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionParameter = new QAction(MainWindow);
        actionParameter->setObjectName(QStringLiteral("actionParameter"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionDownload = new QAction(MainWindow);
        actionDownload->setObjectName(QStringLiteral("actionDownload"));
        actionInitialize = new QAction(MainWindow);
        actionInitialize->setObjectName(QStringLiteral("actionInitialize"));
        actionBluetooth_Test = new QAction(MainWindow);
        actionBluetooth_Test->setObjectName(QStringLiteral("actionBluetooth_Test"));
        actionCom_Settings = new QAction(MainWindow);
        actionCom_Settings->setObjectName(QStringLiteral("actionCom_Settings"));
        actionWindow_View_Tool = new QAction(MainWindow);
        actionWindow_View_Tool->setObjectName(QStringLiteral("actionWindow_View_Tool"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Icons/testdata/mouse-pointer-png-cursor-mouse-icon-0.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionWindow_View_Tool->setIcon(icon);
        actionMarker_Tool = new QAction(MainWindow);
        actionMarker_Tool->setObjectName(QStringLiteral("actionMarker_Tool"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Icons/testdata/6075-200.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMarker_Tool->setIcon(icon1);
        actionLabel_Tool = new QAction(MainWindow);
        actionLabel_Tool->setObjectName(QStringLiteral("actionLabel_Tool"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Icons/testdata/label.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLabel_Tool->setIcon(icon2);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(10, 461, 131, 20));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 490, 201, 23));
        progressBar->setValue(24);
        progressBar->setTextVisible(false);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(150, 460, 51, 21));
        pushButton_2->setAutoFillBackground(true);
        pushButton_2->setAutoRepeat(true);
        pushButton_2->setAutoRepeatDelay(100);
        pushButton_2->setAutoRepeatInterval(10);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(390, 40, 841, 451));
        Tab1 = new QWidget();
        Tab1->setObjectName(QStringLiteral("Tab1"));
        customPlot = new QCustomPlot(Tab1);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(0, 20, 831, 421));
        tabWidget->addTab(Tab1, QString());
        Tab2 = new QWidget();
        Tab2->setObjectName(QStringLiteral("Tab2"));
        customPlot_2 = new QCustomPlot(Tab2);
        customPlot_2->setObjectName(QStringLiteral("customPlot_2"));
        customPlot_2->setGeometry(QRect(0, 0, 831, 421));
        tabWidget->addTab(Tab2, QString());
        Tab3 = new QWidget();
        Tab3->setObjectName(QStringLiteral("Tab3"));
        customPlot_3 = new QCustomPlot(Tab3);
        customPlot_3->setObjectName(QStringLiteral("customPlot_3"));
        customPlot_3->setGeometry(QRect(0, 0, 831, 421));
        tabWidget->addTab(Tab3, QString());
        Tab4 = new QWidget();
        Tab4->setObjectName(QStringLiteral("Tab4"));
        customPlot_4 = new QCustomPlot(Tab4);
        customPlot_4->setObjectName(QStringLiteral("customPlot_4"));
        customPlot_4->setGeometry(QRect(0, 0, 831, 421));
        tabWidget->addTab(Tab4, QString());
        Tab5 = new QWidget();
        Tab5->setObjectName(QStringLiteral("Tab5"));
        Tab5->setMouseTracking(true);
        customPlot_5 = new QCustomPlot(Tab5);
        customPlot_5->setObjectName(QStringLiteral("customPlot_5"));
        customPlot_5->setGeometry(QRect(0, 0, 831, 421));
        customPlot_5->setMouseTracking(true);
        tabWidget->addTab(Tab5, QString());
        toolButton = new QToolButton(centralWidget);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(420, 0, 31, 31));
        toolButton->setIcon(icon1);
        toolButton->setCheckable(true);
        toolButton->setAutoExclusive(true);
        toolButton_2 = new QToolButton(centralWidget);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        toolButton_2->setGeometry(QRect(450, 0, 31, 31));
        toolButton_2->setCursor(QCursor(Qt::ArrowCursor));
        toolButton_2->setIcon(icon2);
        toolButton_2->setCheckable(true);
        toolButton_2->setAutoExclusive(true);
        toolButton_3 = new QToolButton(centralWidget);
        toolButton_3->setObjectName(QStringLiteral("toolButton_3"));
        toolButton_3->setGeometry(QRect(390, 0, 31, 31));
        toolButton_3->setIcon(icon);
        toolButton_3->setCheckable(true);
        toolButton_3->setAutoExclusive(true);
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        if (tableWidget->rowCount() < 4)
            tableWidget->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setCheckState(Qt::Checked);
        __qtablewidgetitem8->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem8->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        tableWidget->setItem(0, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setItem(0, 3, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        __qtablewidgetitem12->setCheckState(Qt::Checked);
        __qtablewidgetitem12->setTextAlignment(Qt::AlignCenter);
        tableWidget->setItem(1, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setItem(1, 1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setItem(1, 2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setItem(1, 3, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        __qtablewidgetitem16->setCheckState(Qt::Checked);
        __qtablewidgetitem16->setTextAlignment(Qt::AlignCenter);
        tableWidget->setItem(2, 0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setItem(2, 1, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setItem(2, 2, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setItem(2, 3, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        __qtablewidgetitem20->setCheckState(Qt::Checked);
        __qtablewidgetitem20->setTextAlignment(Qt::AlignCenter);
        tableWidget->setItem(3, 0, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setItem(3, 1, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setItem(3, 2, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setItem(3, 3, __qtablewidgetitem23);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 70, 371, 371));
        tableWidget->setFrameShape(QFrame::StyledPanel);
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tableWidget->setGridStyle(Qt::SolidLine);
        tableWidget->setSortingEnabled(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(46);
        tableWidget->horizontalHeader()->setHighlightSections(true);
        tableWidget->horizontalHeader()->setMinimumSectionSize(40);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setCascadingSectionResizes(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(20);
        tableWidget->verticalHeader()->setMinimumSectionSize(15);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1240, 21));
        menuOption = new QMenu(menuBar);
        menuOption->setObjectName(QStringLiteral("menuOption"));
        menuOption_2 = new QMenu(menuBar);
        menuOption_2->setObjectName(QStringLiteral("menuOption_2"));
        menuDevice = new QMenu(menuBar);
        menuDevice->setObjectName(QStringLiteral("menuDevice"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuOption->menuAction());
        menuBar->addAction(menuDevice->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuOption_2->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuOption->addAction(actionLogin);
        menuOption->addAction(actionOpen);
        menuOption->addAction(actionSave);
        menuOption->addAction(actionSave_As);
        menuOption->addAction(actionExit);
        menuOption_2->addAction(actionParameter);
        menuDevice->addAction(actionDownload);
        menuDevice->addAction(actionInitialize);
        menuDevice->addAction(actionBluetooth_Test);
        menuDevice->addAction(actionCom_Settings);
        menuView->addAction(actionWindow_View_Tool);
        menuView->addAction(actionMarker_Tool);
        menuView->addAction(actionLabel_Tool);

        retranslateUi(MainWindow);
        QObject::connect(pushButton_2, SIGNAL(clicked()), lcdNumber, SLOT(update()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "PLM Analyzer by Carpe Noctem", Q_NULLPTR));
        actionLogin->setText(QApplication::translate("MainWindow", "New", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        actionParameter->setText(QApplication::translate("MainWindow", "Parameter", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("MainWindow", "Open...", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save As...", Q_NULLPTR));
        actionDownload->setText(QApplication::translate("MainWindow", "Download", Q_NULLPTR));
        actionInitialize->setText(QApplication::translate("MainWindow", "Initialize...", Q_NULLPTR));
        actionBluetooth_Test->setText(QApplication::translate("MainWindow", "Bluetooth Test", Q_NULLPTR));
        actionCom_Settings->setText(QApplication::translate("MainWindow", "Com Settings...", Q_NULLPTR));
        actionWindow_View_Tool->setText(QApplication::translate("MainWindow", "Window View Tool", Q_NULLPTR));
        actionMarker_Tool->setText(QApplication::translate("MainWindow", "Marker Tool", Q_NULLPTR));
        actionLabel_Tool->setText(QApplication::translate("MainWindow", "Label Tool", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Reset", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Tab1), QApplication::translate("MainWindow", "Tab 1", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Tab2), QApplication::translate("MainWindow", "Tab 2", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Tab3), QApplication::translate("MainWindow", "Tab 3", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Tab4), QApplication::translate("MainWindow", "Tab 4", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Tab5), QApplication::translate("MainWindow", "Tab 5", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolButton->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Paint Tool: Press ENTER to paint</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        toolButton_2->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        toolButton_3->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "State", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "#", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Status", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Comment", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Marker 12", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Marker 65", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "Label 132", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "Label 245", Q_NULLPTR));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->item(0, 1);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "&1543", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->item(0, 2);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "None", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->item(0, 3);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "Offset needs to be readjusted", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->item(1, 1);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "&1564", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->item(1, 2);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "None", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->item(1, 3);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "N/A", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->item(2, 1);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "&6432", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->item(2, 2);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "P", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->item(2, 3);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "Occurence of P too frequent", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->item(3, 1);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "&6809", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->item(3, 2);
        ___qtablewidgetitem18->setText(QApplication::translate("MainWindow", "P", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->item(3, 3);
        ___qtablewidgetitem19->setText(QApplication::translate("MainWindow", "N/A", Q_NULLPTR));
        tableWidget->setSortingEnabled(__sortingEnabled);

        menuOption->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuOption_2->setTitle(QApplication::translate("MainWindow", "Option", Q_NULLPTR));
        menuDevice->setTitle(QApplication::translate("MainWindow", "Device", Q_NULLPTR));
        menuAbout->setTitle(QApplication::translate("MainWindow", "About", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("MainWindow", "Tools", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
