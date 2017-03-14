#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QStandardItemModel>
#include <QTableView>
#include <vector>
#include <QMainWindow>
#include "graphviewer.h"
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
    void save();
    void handToolTriggered();
    void markerToolTriggered();
    void labelToolTriggered();
    void rightMousePress();
    void viewSelection();
    void labelSelection();
    void rescaleView();

protected:

private:
    GraphViewer graphViewer(Ui::MainWindow);
    void createActions();
    void createMenus();
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    bool firstRun;
    QMenu *fileMenu;
    QAction *openAct;
    QAction *saveAct;

    // Michael's Added private variables
    void showRightClickMenu(const QPoint& pos);
    void enableToolBar();
    void disableToolBar();
    QAction *handToolAct;
    QAction *markerToolAct;
    QAction *labelToolAct;
    QMenu *rightClickMenu;

    QMenu *addMarkerMenu;
    QAction *addUpMarker;
    QAction *addDownMarker;
    //QAction *addButtonMarker;
    //QAction *addManual;
    QAction *addPMarker;
    QAction *addRMarker;
    QAction *addKMarker;
    QAction *addIMarker;

    void getSelectionValues(QCPDataSelection selection, int graphNum);
    void setMinMax(QList<double> keys, QList<double> values);
    bool firstSelectionCheck;
    double xAxisKeyMin;
    double xAxisKeyMax;
    double xAxisValueMin;
    double xAxisValueMax;
    QAction *viewSelectionAct;
    QShortcut *viewSelectionShortcut;
    QAction *labelSelectionAct;
    QShortcut *labelSelectionShortcut;
    QCPItemRect *labelRect;
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
