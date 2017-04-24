#ifndef BLUETOOTHWINDOW_H
#define BLUETOOTHWINDOW_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class BluetoothWindow;
}

class BluetoothWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BluetoothWindow(QWidget *parent = 0);
    ~BluetoothWindow();

private slots:
    void updateCommPort();
    void runBluetooth();
    void connectButtonClicked();
    void cancelButtonClicked();

private:
    Ui::BluetoothWindow *ui;
    void setupBluetoothWindow();
    QProcess *process;

};

#endif // BLUETOOTHWINDOW_H
