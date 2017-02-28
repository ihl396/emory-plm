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
};

#endif // MAINWINDOW_h
