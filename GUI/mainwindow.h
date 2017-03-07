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

    // Michael's Added private variables
    //QToolBar *toolBar;
    QAction *handToolAct;
    QAction *markerToolAct;
    QAction *labelToolAct;
    void showRightClickMenu(const QPoint& pos);
    QMenu *rightClickMenu;
    QAction *viewSelectionAct;
    QShortcut *viewSelectionShortcut;
    QAction *undoViewSelectedAct;
    QAction *rescaleViewAct;
    QShortcut *rescaleViewShortcut;
    QAction *cancelAct;
    QCPDataSelection selection;
    QAction *selectedItem;

private slots:
    void handToolTriggered();
    void markerToolTriggered();
    void labelToolTriggered();
    void rightMousePress();
    void viewSelection();
    void rescaleView();

};

#endif // MAINWINDOW_h
