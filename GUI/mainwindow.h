#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QStandardItemModel>
#include <QTableView>
#include <vector>
#include <QMainWindow>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString getCSVFile();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void createGraph(QVector<double>, QVector<double>, QVector<double>, QVector<double>, bool);


private:
    Ui::MainWindow *ui;
    QString csvFile;
    QList<QStringList> csv;
    QStandardItemModel *model;
    QList<QStandardItem*> standardItemList;
    QVector<QVector<double>> dataArray;
    bool firstRun;
};

#endif // MAINWINDOW_h
