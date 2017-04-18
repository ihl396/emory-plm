#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QStandardItemModel>
#include <QTableView>
#include <vector>
#include <QMainWindow>
#include <QCloseEvent>
#include "setupwindow.h"
#include "graphviewer.h"
#include "datastructure.h"
#include <iostream>
#include <fstream>
#include <QFileInfo>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setGraphRanges();

private slots:
    void open();
    void openSetupWindow();
    void saveMarkers();
    void saveSelections();
    void loadMarkers();
    void loadSelections();
    void handToolTriggered();
    void markerToolTriggered();
    void rulerToolTriggered();
    void rightMousePress();
    void clickedGraph(QMouseEvent*);
    void addMarkerUp();
    void addMarkerDown();
    void addMarkerP();
    void addMarkerR();
    void addMarkerK();
    void addMarkerI();
    void deleteMS();
    //void deleteSelection();
    void viewSelection();
    void labelSelection();
    void rescaleView();
    void hideXYZGraphs();
    void toggleHide();
    void updatePhaseTracer(QMouseEvent *event);
    void createRuler(QMouseEvent *event);
    void horzScrollBarChanged(int);
    void xAxisChanged(QCPRange);
    bool eventFilter(QObject *watched, QEvent *event);
    void focusChanged();

protected:

private:
    //GraphViewer graphViewer(Ui::MainWindow, Ui::SetupWindow);
    class SetupWindow *sWindow;
    class GraphViewer *graphViewer;
    void createActions();
    void createMenus();
    void createMarkerPixmaps();
    void closeEvent(QCloseEvent *event);
    bool fileExists(QString);
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    bool firstRun;
    QMenu *fileMenu;
    QAction *openAct;
    QAction *saveAct;
    QMenu *editMenu;
    QAction *graphViewPreferencesAct;
    QAction *labelPreferencesAct;
    markerStructure marker_structure;
    selectionStructure selection_structure;
    QString file;

    // Michael's Added private variables
    void showRightClickMenu(const QPoint& pos);
    void enableToolBar();
    void disableToolBar();
    QAction *handToolAct;
    QAction *selectToolAct;
    QAction *labelToolAct;
    QAction *rulerToolAct;
    QMenu *rightClickMenu;
    double xKeyPos;

    void createMarker(double ID);
    bool addMarkerClicked;
    double markerID;
    QMenu *addMarkerMenu;
    QAction *addUpMarkerAct;
    QShortcut *addUpMarkerActShortcut;
    QAction *addDownMarkerAct;
    QShortcut *addDownMarkerActShortcut;
    //QAction *addButtonMarker;
    //QAction *addManual;
    QAction *addPMarkerAct;
    QShortcut *addPMarkerActShortcut;
    QAction *addRMarkerAct;
    QShortcut *addRMarkerActShortcut;
    QAction *addKMarkerAct;
    QShortcut *addKMarkerActShortcut;
    QAction *addIMarkerAct;
    QShortcut *addIMarkerActShortcut;
    QAction *deleteAct;
    QShortcut *deleteActShortcut;
    //QAction *deleteSelectionAct;
    //QShortcut *deleteSelectionActShortcut;
    int itemsSelected;

    QCPItemPixmap *markerUP;
    QPixmap *upPix;
    QCPItemPixmap *markerD;
    QPixmap *downPix;
    QCPItemPixmap *markerP;
    QPixmap *pPix;
    QCPItemPixmap *markerR;
    QPixmap *rPix;
    QCPItemPixmap *markerK;
    QPixmap *kPix;
    QCPItemPixmap *markerI;
    QPixmap *iPix;

    void getSelectionValues();//QCPDataSelection selection, int graphNum);
    void setMinMax(QList<double> keys, QList<double> values);
    bool firstSelectionCheck;
    double xAxisKeyMin;
    double xAxisKeyMax;
    double xAxisValueMin;
    double xAxisValueMax;
    QAction *viewSelectionAct;
    QShortcut *viewSelectionShortcut;
    QCPItemText *labelText;
    QAction *labelSelectionAct;
    QShortcut *labelSelectionShortcut;
    QCPItemRect *rect;
    QAction *rescaleViewAct;
    QShortcut *rescaleViewShortcut;
    QAction *hideGraphAct;
    QShortcut *hideGraphShortcut;
    QCPDataSelection xGraphSelection;
    QCPDataSelection yGraphSelection;
    QCPDataSelection zGraphSelection;
    QCPDataSelection nGraphSelection;
    QAction *selectedItem;

    int scaledMovement;
    double phaseTracerKeyPos;
    double phaseTracerValuePos;
    QCPItemTracer *phaseTracer;
    QCPItemText *phaseTracerItemText;
};

#endif // MAINWINDOW_h
