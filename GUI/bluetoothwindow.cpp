#include "bluetoothwindow.h"
#include "ui_bluetoothwindow.h"

BluetoothWindow::BluetoothWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BluetoothWindow)
{
    ui->setupUi(this);

    setupBluetoothWindow();
}

BluetoothWindow::~BluetoothWindow()
{
    delete ui;
}

void BluetoothWindow::setupBluetoothWindow()
{
    ui->commPortRadioButton_1->setChecked(true);

    //connect(ui->commPortRadioButton_1, SIGNAL())
}
