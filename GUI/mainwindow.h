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

private slots:
    void open();
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
    void markerDelete();
    void viewSelection();
    void labelSelection();
    void rescaleView();

protected:

private:
    GraphViewer graphViewer(Ui::MainWindow);
    void createActions();
    void createMenus();
    void createMarkerPixmaps();
    void createRuler(); // Temporary
    void closeEvent(QCloseEvent *event);
    bool fileExists(QString);
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    bool firstRun;
    QMenu *fileMenu;
    QAction *openAct;
    QAction *saveAct;
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

    void placeMarker(double ID);
    bool addMarkerClicked;
    double markerID;
    QMenu *addMarkerMenu;
    QAction *addUpMarker;
    QShortcut *addUpMarkerShortcut;
    QAction *addDownMarker;
    QShortcut *addDownMarkerShortcut;
    //QAction *addButtonMarker;
    //QAction *addManual;
    QAction *addPMarker;
    QShortcut *addPMarkerShortcut;
    QAction *addRMarker;
    QShortcut *addRMarkerShortcut;
    QAction *addKMarker;
    QShortcut *addKMarkerShortcut;
    QAction *addIMarker;
    QShortcut *addIMarkerShortcut;
    QAction *deleteMarker;
    QShortcut *deleteMarkerShortcut;
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
    QAction *cancelAct;
    QCPDataSelection xGraphSelection;
    QCPDataSelection yGraphSelection;
    QCPDataSelection zGraphSelection;
    QCPDataSelection nGraphSelection;
    QAction *selectedItem;
};

#endif // MAINWINDOW_h
