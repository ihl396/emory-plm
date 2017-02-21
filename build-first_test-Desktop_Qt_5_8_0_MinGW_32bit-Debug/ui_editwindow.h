/********************************************************************************
** Form generated from reading UI file 'editwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITWINDOW_H
#define UI_EDITWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_editwindow
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QLineEdit *lineEdit;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *pushButton_5;
    QWidget *tab_2;
    QPushButton *pushButton_4;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *editwindow)
    {
        if (editwindow->objectName().isEmpty())
            editwindow->setObjectName(QStringLiteral("editwindow"));
        editwindow->setEnabled(true);
        editwindow->resize(534, 408);
        editwindow->setAutoFillBackground(true);
        editwindow->setStyleSheet(QStringLiteral(""));
        tabWidget = new QTabWidget(editwindow);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 536, 351));
        tabWidget->setAutoFillBackground(false);
        tabWidget->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tab->setEnabled(true);
        tab->setAutoFillBackground(false);
        tab->setStyleSheet(QLatin1String("QTabWidget{\n"
"background-color: rgb(14, 30, 255);\n"
"}"));
        pushButton_2 = new QPushButton(tab);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(50, 170, 101, 28));
        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(50, 130, 101, 28));
        pushButton_3 = new QPushButton(tab);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(50, 210, 101, 28));
        lineEdit = new QLineEdit(tab);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(320, 110, 171, 20));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(250, 110, 61, 20));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(250, 140, 71, 16));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(240, 170, 81, 16));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(270, 200, 41, 16));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(250, 230, 51, 16));
        lineEdit_2 = new QLineEdit(tab);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(320, 140, 171, 20));
        lineEdit_3 = new QLineEdit(tab);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(320, 170, 171, 20));
        lineEdit_4 = new QLineEdit(tab);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(320, 200, 171, 20));
        lineEdit_5 = new QLineEdit(tab);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(320, 230, 171, 81));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(320, 80, 111, 20));
        label_6->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 0);"));
        label_7 = new QLabel(tab);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(60, 100, 111, 16));
        label_8 = new QLabel(tab);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(180, 30, 151, 31));
        QFont font;
        font.setPointSize(14);
        label_8->setFont(font);
        label_8->setTextFormat(Qt::AutoText);
        pushButton_5 = new QPushButton(tab);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(50, 270, 101, 31));
        pushButton_5->setAutoFillBackground(false);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tab_2->setAutoFillBackground(true);
        pushButton_4 = new QPushButton(tab_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(140, 140, 251, 61));
        tabWidget->addTab(tab_2, QString());
        buttonBox = new QDialogButtonBox(editwindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setEnabled(true);
        buttonBox->setGeometry(QRect(10, 360, 521, 41));
        buttonBox->setMouseTracking(true);
        buttonBox->setLayoutDirection(Qt::LeftToRight);
        buttonBox->setAutoFillBackground(false);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        retranslateUi(editwindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(editwindow);
    } // setupUi

    void retranslateUi(QDialog *editwindow)
    {
        editwindow->setWindowTitle(QApplication::translate("editwindow", "Login", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("editwindow", ".m file", Q_NULLPTR));
        pushButton->setText(QApplication::translate("editwindow", "Octave location", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("editwindow", "Raw data file ", Q_NULLPTR));
        lineEdit->setText(QString());
        label->setText(QApplication::translate("editwindow", "First Name:", Q_NULLPTR));
        label_2->setText(QApplication::translate("editwindow", "Last Name:", Q_NULLPTR));
        label_3->setText(QApplication::translate("editwindow", "Condition(s):", Q_NULLPTR));
        label_4->setText(QApplication::translate("editwindow", "Doctor:", Q_NULLPTR));
        label_5->setText(QApplication::translate("editwindow", "Comments:", Q_NULLPTR));
        lineEdit_2->setText(QString());
        lineEdit_3->setText(QString());
        lineEdit_4->setText(QString());
        lineEdit_5->setText(QString());
        label_6->setText(QApplication::translate("editwindow", "Patient Information", Q_NULLPTR));
        label_7->setText(QApplication::translate("editwindow", "File Locations", Q_NULLPTR));
        label_8->setText(QApplication::translate("editwindow", "The PLM Analyser", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("editwindow", "Use Default", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("editwindow", "New Patient", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("editwindow", "Locate file of existing patient", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("editwindow", "Existing Patient", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class editwindow: public Ui_editwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITWINDOW_H
