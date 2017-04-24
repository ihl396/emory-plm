#include "bluetoothwindow.h"
#include "ui_bluetoothwindow.h"

#include <QMessageBox>
#include <QProcess>
#include <QDebug>

BluetoothWindow::BluetoothWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BluetoothWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    setupBluetoothWindow();
}

BluetoothWindow::~BluetoothWindow()
{
    delete ui;
}

void BluetoothWindow::setupBluetoothWindow()
{
    ui->commPortRadioButton_1->setChecked(true);

    connect(ui->commPortRadioButton_1, SIGNAL(clicked(bool)), this, SLOT(updateCommPort()));
    connect(ui->commPortRadioButton_2, SIGNAL(clicked(bool)), this, SLOT(updateCommPort()));
    connect(ui->commPortRadioButton_3, SIGNAL(clicked(bool)), this, SLOT(updateCommPort()));
    connect(ui->commPortRadioButton_4, SIGNAL(clicked(bool)), this, SLOT(updateCommPort()));

    connect(ui->connectBluetoothButton, SIGNAL(clicked(bool)), this, SLOT(connectButtonClicked()));
    connect(ui->cancelBluetoothWindow, SIGNAL(clicked(bool)), this, SLOT(cancelButtonClicked()));
}

void BluetoothWindow::updateCommPort()
{
    if (sender() == ui->commPortRadioButton_1)
    {
        ui->commPortRadioButton_2->setChecked(false);
        ui->commPortRadioButton_3->setChecked(false);
        ui->commPortRadioButton_4->setChecked(false);
    }
    else if (sender() == ui->commPortRadioButton_2)
    {
        ui->commPortRadioButton_1->setChecked(false);
        ui->commPortRadioButton_3->setChecked(false);
        ui->commPortRadioButton_4->setChecked(false);
    }
    else if (sender() == ui->commPortRadioButton_3)
    {
        ui->commPortRadioButton_1->setChecked(false);
        ui->commPortRadioButton_2->setChecked(false);
        ui->commPortRadioButton_4->setChecked(false);
    }
    else if (sender() == ui->commPortRadioButton_4)
    {
        ui->commPortRadioButton_1->setChecked(false);
        ui->commPortRadioButton_2->setChecked(false);
        ui->commPortRadioButton_3->setChecked(false);
    }

}

void BluetoothWindow::runBluetooth()
{
    qDebug() << "runBluetooth";
}

void BluetoothWindow::connectButtonClicked()
{
    //QMessageBox::StandardButton reply;
    //reply = QMessageBox::information(this, "Bluetooth", "Are you sure you want to confirm your changes?", QMessageBox::Yes|QMessageBox::No);
    /*process = new QProcess();
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(runBluetooth()));
    connect(process, SIGNAL(readyReadStandardError()), this, SLOT(runBluetooth()));
    //p.readyReadStandardOutput();
    process->setProcessChannelMode(QProcess::MergedChannels);
    QString exe = QCoreApplication::applicationDirPath() + "/bluetooth_code.py";
    QString test = QCoreApplication::applicationDirPath() + "/test.py";
    QString pyserial = "pip install pyserial";
    QString progress = "pip install progress";
    QStringList pyserialCommand = QStringList() << "-m" << pyserial;
    QStringList progressCommand = QStringList() << "-m" << progress;
    QStringList params = QStringList() << exe;
    //qDebug() << "params = " << params;
    //QString temp = QString("C://Users//Michael Son//Desktop//test.py");
    process->start("python", pyserialCommand, QProcess::ReadWrite);
    process->waitForReadyRead();
    qDebug() << process->readAllStandardOutput();
    if (process->waitForFinished() == false)
    {
        qDebug() << "Unable to finish";
    }
    else
    {
        qDebug() << "Command finished";
    }
    process->start("python", progressCommand, QProcess::ReadWrite);
    process->waitForReadyRead();
    qDebug() << process->readAllStandardOutput();
    if (process->waitForFinished() == false)
    {
        qDebug() << "Unable to finish";
    }
    else
    {
        qDebug() << "Command finished";
    }
    process->start("python", params, QProcess::ReadWrite);
    qDebug() << "start";
    if (process->waitForStarted(1000) == false)
    {
        qDebug() << "Error starting external program";
    }
    else
    {
        qDebug() << "External program running";
    }
    process->waitForReadyRead();

    QString p_stdout = process->readAllStandardOutput();
    qDebug() << "p_stdout = " << p_stdout << endl;*/


    /*QStringList tList = QStringList() << test;

    const char* cmd = test.toLocal8Bit().constData();
    //qDebug() << cmd;
    system(cmd);*/
}

void BluetoothWindow::cancelButtonClicked()
{
    BluetoothWindow::close();
}
