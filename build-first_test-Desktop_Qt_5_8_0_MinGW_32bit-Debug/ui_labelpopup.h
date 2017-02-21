/********************************************************************************
** Form generated from reading UI file 'labelpopup.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LABELPOPUP_H
#define UI_LABELPOPUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_LabelPopup
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLabel *com_tag;
    QLabel *label;
    QLabel *label_name;
    QComboBox *comboBox;
    QLabel *label_2;

    void setupUi(QDialog *LabelPopup)
    {
        if (LabelPopup->objectName().isEmpty())
            LabelPopup->setObjectName(QStringLiteral("LabelPopup"));
        LabelPopup->resize(400, 300);
        buttonBox = new QDialogButtonBox(LabelPopup);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 251, 32));
        buttonBox->setLayoutDirection(Qt::LeftToRight);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(LabelPopup);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(80, 190, 291, 21));
        com_tag = new QLabel(LabelPopup);
        com_tag->setObjectName(QStringLiteral("com_tag"));
        com_tag->setGeometry(QRect(10, 190, 71, 16));
        label = new QLabel(LabelPopup);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 50, 81, 16));
        label_name = new QLabel(LabelPopup);
        label_name->setObjectName(QStringLiteral("label_name"));
        label_name->setGeometry(QRect(90, 50, 191, 16));
        comboBox = new QComboBox(LabelPopup);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(90, 100, 191, 26));
        label_2 = new QLabel(LabelPopup);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 110, 71, 16));

        retranslateUi(LabelPopup);
        QObject::connect(buttonBox, SIGNAL(accepted()), LabelPopup, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), LabelPopup, SLOT(reject()));

        comboBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LabelPopup);
    } // setupUi

    void retranslateUi(QDialog *LabelPopup)
    {
        LabelPopup->setWindowTitle(QApplication::translate("LabelPopup", "Dialog", Q_NULLPTR));
        com_tag->setText(QApplication::translate("LabelPopup", "Comment:", Q_NULLPTR));
        label->setText(QApplication::translate("LabelPopup", "Label Name:", Q_NULLPTR));
        label_name->setText(QApplication::translate("LabelPopup", "TextLabel", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("LabelPopup", "Square", Q_NULLPTR)
         << QApplication::translate("LabelPopup", "Circle", Q_NULLPTR)
        );
        label_2->setText(QApplication::translate("LabelPopup", "Label Type:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LabelPopup: public Ui_LabelPopup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABELPOPUP_H
