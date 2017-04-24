/********************************************************************************
** Form generated from reading UI file 'bluetoothwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLUETOOTHWINDOW_H
#define UI_BLUETOOTHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_BluetoothWindow
{
public:
    QPushButton *connectBluetoothButton;
    QPushButton *cancelBluetoothWindow;
    QGroupBox *commPortGroupBox;
    QRadioButton *commPortRadioButton_1;
    QRadioButton *commPortRadioButton_2;
    QRadioButton *commPortRadioButton_4;
    QRadioButton *commPortRadioButton_3;

    void setupUi(QDialog *BluetoothWindow)
    {
        if (BluetoothWindow->objectName().isEmpty())
            BluetoothWindow->setObjectName(QStringLiteral("BluetoothWindow"));
        BluetoothWindow->resize(172, 161);
        connectBluetoothButton = new QPushButton(BluetoothWindow);
        connectBluetoothButton->setObjectName(QStringLiteral("connectBluetoothButton"));
        connectBluetoothButton->setGeometry(QRect(10, 130, 75, 23));
        cancelBluetoothWindow = new QPushButton(BluetoothWindow);
        cancelBluetoothWindow->setObjectName(QStringLiteral("cancelBluetoothWindow"));
        cancelBluetoothWindow->setGeometry(QRect(90, 130, 75, 23));
        commPortGroupBox = new QGroupBox(BluetoothWindow);
        commPortGroupBox->setObjectName(QStringLiteral("commPortGroupBox"));
        commPortGroupBox->setGeometry(QRect(40, 10, 91, 101));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        commPortGroupBox->setFont(font);
        commPortRadioButton_1 = new QRadioButton(commPortGroupBox);
        commPortRadioButton_1->setObjectName(QStringLiteral("commPortRadioButton_1"));
        commPortRadioButton_1->setGeometry(QRect(20, 20, 51, 17));
        QFont font1;
        font1.setPointSize(8);
        font1.setBold(false);
        font1.setUnderline(false);
        font1.setWeight(50);
        commPortRadioButton_1->setFont(font1);
        commPortRadioButton_2 = new QRadioButton(commPortGroupBox);
        commPortRadioButton_2->setObjectName(QStringLiteral("commPortRadioButton_2"));
        commPortRadioButton_2->setGeometry(QRect(20, 40, 51, 17));
        commPortRadioButton_2->setFont(font1);
        commPortRadioButton_4 = new QRadioButton(commPortGroupBox);
        commPortRadioButton_4->setObjectName(QStringLiteral("commPortRadioButton_4"));
        commPortRadioButton_4->setGeometry(QRect(20, 80, 51, 17));
        commPortRadioButton_4->setFont(font1);
        commPortRadioButton_3 = new QRadioButton(commPortGroupBox);
        commPortRadioButton_3->setObjectName(QStringLiteral("commPortRadioButton_3"));
        commPortRadioButton_3->setGeometry(QRect(20, 60, 51, 17));
        commPortRadioButton_3->setFont(font1);

        retranslateUi(BluetoothWindow);

        QMetaObject::connectSlotsByName(BluetoothWindow);
    } // setupUi

    void retranslateUi(QDialog *BluetoothWindow)
    {
        BluetoothWindow->setWindowTitle(QApplication::translate("BluetoothWindow", "Bluetooth", Q_NULLPTR));
        connectBluetoothButton->setText(QApplication::translate("BluetoothWindow", "Connect", Q_NULLPTR));
        cancelBluetoothWindow->setText(QApplication::translate("BluetoothWindow", "Cancel", Q_NULLPTR));
        commPortGroupBox->setTitle(QApplication::translate("BluetoothWindow", "Comm Ports", Q_NULLPTR));
        commPortRadioButton_1->setText(QApplication::translate("BluetoothWindow", "Port 1", Q_NULLPTR));
        commPortRadioButton_2->setText(QApplication::translate("BluetoothWindow", "Port 2", Q_NULLPTR));
        commPortRadioButton_4->setText(QApplication::translate("BluetoothWindow", "Port 4", Q_NULLPTR));
        commPortRadioButton_3->setText(QApplication::translate("BluetoothWindow", "Port 3", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BluetoothWindow: public Ui_BluetoothWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLUETOOTHWINDOW_H
