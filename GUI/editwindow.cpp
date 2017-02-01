#include "editwindow.h"
#include "ui_editwindow.h"
#include <QFileDialog>
#include <QString>
#include <string>
#include <QMessageBox>
#include <iostream>

using namespace std;

editwindow::editwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editwindow)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(close()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));

//    ui->tabWidget->setStyleSheet("background:transparent");
//    ui->tabWidget->setAttribute(Qt::WA_TranslucentBackground);
//    ui->tabWidget->setWindowFlags(Qt::FramelessWindowHint);

//    ui->tab->setStyleSheet("background:transparent");
//    ui->tab->setAttribute(Qt::WA_TranslucentBackground);
//    ui->tab->setWindowFlags(Qt::FramelessWindowHint);



}

editwindow::~editwindow()
{
    delete ui;
}


void editwindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "all files (*.*)"

                );




}

void editwindow::on_pushButton_2_clicked()
{
    QString filename2 = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "Octave/MATLAB scripts (*.m);;all files (*.*)"

                );


}

void editwindow::on_pushButton_3_clicked()
{
    QString filename3 = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "CSV files (*.csv);;all files (*.*)"

                );

}

//void editwindow::on_buttonBox_accepted()
//{

//    QString octavelocation = "filename";          //need signals
//    QString mfilelocation = "filename2";
//    QString operatormfile = " -V ";
//    QString commandstr = "\"" + octavelocation + operatormfile + mfilelocation + "\"";
//    system(commandstr.c_str());
//}

void editwindow::on_pushButton_5_clicked()
{
   // QString octavelocation = "C:\\Octave\\Octave-4.2.0\\bin\\octave-cli.exe"; //need signal
   // QString mfilelocation = "C:\\Users\\seb\\Desktop\\sampleoct.m";

}
