#ifndef BLUETOOTHWINDOW_H
#define BLUETOOTHWINDOW_H

#include <QDialog>

namespace Ui {
class BluetoothWindow;
}

class BluetoothWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BluetoothWindow(QWidget *parent = 0);
    ~BluetoothWindow();

private:
    Ui::BluetoothWindow *ui;
    void setupBluetoothWindow();
};

#endif // BLUETOOTHWINDOW_H
