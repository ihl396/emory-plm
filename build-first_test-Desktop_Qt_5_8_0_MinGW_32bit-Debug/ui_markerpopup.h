/********************************************************************************
** Form generated from reading UI file 'markerpopup.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MARKERPOPUP_H
#define UI_MARKERPOPUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MarkerPopup
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLabel *com_tag;
    QLabel *mark_tag;
    QLabel *marker_name;
    QLabel *col_tag;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QWidget *color_disp;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QDialog *MarkerPopup)
    {
        if (MarkerPopup->objectName().isEmpty())
            MarkerPopup->setObjectName(QStringLiteral("MarkerPopup"));
        MarkerPopup->resize(381, 240);
        buttonBox = new QDialogButtonBox(MarkerPopup);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(10, 200, 351, 32));
        buttonBox->setLayoutDirection(Qt::LeftToRight);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);
        lineEdit = new QLineEdit(MarkerPopup);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(80, 150, 271, 20));
        lineEdit->setReadOnly(false);
        lineEdit->setClearButtonEnabled(false);
        com_tag = new QLabel(MarkerPopup);
        com_tag->setObjectName(QStringLiteral("com_tag"));
        com_tag->setGeometry(QRect(6, 150, 61, 21));
        mark_tag = new QLabel(MarkerPopup);
        mark_tag->setObjectName(QStringLiteral("mark_tag"));
        mark_tag->setGeometry(QRect(16, 30, 71, 16));
        marker_name = new QLabel(MarkerPopup);
        marker_name->setObjectName(QStringLiteral("marker_name"));
        marker_name->setGeometry(QRect(100, 30, 141, 16));
        col_tag = new QLabel(MarkerPopup);
        col_tag->setObjectName(QStringLiteral("col_tag"));
        col_tag->setGeometry(QRect(20, 82, 47, 21));
        spinBox = new QSpinBox(MarkerPopup);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(150, 80, 42, 22));
        spinBox->setAccelerated(true);
        spinBox->setMaximum(255);
        spinBox_2 = new QSpinBox(MarkerPopup);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(220, 80, 42, 22));
        spinBox_2->setAccelerated(true);
        spinBox_2->setMaximum(255);
        spinBox_3 = new QSpinBox(MarkerPopup);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setGeometry(QRect(290, 80, 42, 22));
        spinBox_3->setAccelerated(true);
        spinBox_3->setMaximum(255);
        color_disp = new QWidget(MarkerPopup);
        color_disp->setObjectName(QStringLiteral("color_disp"));
        color_disp->setGeometry(QRect(60, 80, 51, 21));
        color_disp->setAutoFillBackground(true);
        label = new QLabel(MarkerPopup);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(160, 60, 47, 13));
        label_2 = new QLabel(MarkerPopup);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(230, 60, 29, 13));
        label_3 = new QLabel(MarkerPopup);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(300, 60, 29, 13));

        retranslateUi(MarkerPopup);
        QObject::connect(buttonBox, SIGNAL(accepted()), MarkerPopup, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), MarkerPopup, SLOT(reject()));

        QMetaObject::connectSlotsByName(MarkerPopup);
    } // setupUi

    void retranslateUi(QDialog *MarkerPopup)
    {
        MarkerPopup->setWindowTitle(QApplication::translate("MarkerPopup", "Dialog", Q_NULLPTR));
        com_tag->setText(QApplication::translate("MarkerPopup", "Comment:", Q_NULLPTR));
        mark_tag->setText(QApplication::translate("MarkerPopup", "Marker Tag:", Q_NULLPTR));
        marker_name->setText(QApplication::translate("MarkerPopup", "TextLabel", Q_NULLPTR));
        col_tag->setText(QApplication::translate("MarkerPopup", "Color:", Q_NULLPTR));
        label->setText(QApplication::translate("MarkerPopup", "Red", Q_NULLPTR));
        label_2->setText(QApplication::translate("MarkerPopup", "Green", Q_NULLPTR));
        label_3->setText(QApplication::translate("MarkerPopup", "Blue", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MarkerPopup: public Ui_MarkerPopup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MARKERPOPUP_H
