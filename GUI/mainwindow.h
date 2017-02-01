#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "markerpopup.h"
#include "labelpopup.h"
#include "qcustomplot.h"
#include "editwindow.h"
#include "parameters.h"

#include <QMainWindow>
#include <QTimer>
#include <QShortcut>
#include <QtMath>
#include <QPen>
#include <QBrush>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void getRawData(QString);

public slots:
    void myfunction();

    void markerfc(QStringList);

    void labelfc(QStringList);

    void  mousePress();

    void mouseWheel();

    void keyPressEvent(QKeyEvent *event);

    void mouseRelease();

    void addLabelSelection();



private slots:

    void on_lcdNumber_overflow();

    void on_pushButton_2_clicked();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

    void on_actionLogin_triggered();

    void on_actionParameter_triggered();

    void on_actionExit_triggered();

signals:
    void EnterIsPressed();

    void MouseIsReleased();

    void MarkerNameInfo(QString);

    void LabelNameInfo(QString);

    void toolbutton_trig();

    void toolbutton2_trig();

    void toolbutton3_trig();

//    void rawDataSig(int);


private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QShortcut * shortcut;
    MarkerPopup *markerPopup;
    LabelPopup *labelPopup;
    QCPItemTracer *labelTracerTemp;
    editwindow *editwindowpt;
    Parameters *parampt;

};

#endif // MAINWINDOW_H
