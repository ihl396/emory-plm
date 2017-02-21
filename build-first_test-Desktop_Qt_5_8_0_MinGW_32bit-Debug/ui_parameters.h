/********************************************************************************
** Form generated from reading UI file 'parameters.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETERS_H
#define UI_PARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Parameters
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QSlider *onset_slider;
    QSlider *decay_slider;
    QSlider *mintime_slider;
    QSlider *maxtime_slider;
    QSlider *minbetween_slider;
    QSlider *maxbetween_slider;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox_4;
    QSpinBox *spinBox_5;
    QSpinBox *spinBox_6;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;

    void setupUi(QDialog *Parameters)
    {
        if (Parameters->objectName().isEmpty())
            Parameters->setObjectName(QStringLiteral("Parameters"));
        Parameters->resize(493, 300);
        buttonBox = new QDialogButtonBox(Parameters);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(3, 250, 491, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);
        layoutWidget = new QWidget(Parameters);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 40, 221, 196));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        onset_slider = new QSlider(layoutWidget);
        onset_slider->setObjectName(QStringLiteral("onset_slider"));
        onset_slider->setMaximum(10);
        onset_slider->setSingleStep(1);
        onset_slider->setPageStep(10);
        onset_slider->setValue(10);
        onset_slider->setSliderPosition(10);
        onset_slider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(onset_slider);

        decay_slider = new QSlider(layoutWidget);
        decay_slider->setObjectName(QStringLiteral("decay_slider"));
        decay_slider->setMaximum(10);
        decay_slider->setValue(7);
        decay_slider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(decay_slider);

        mintime_slider = new QSlider(layoutWidget);
        mintime_slider->setObjectName(QStringLiteral("mintime_slider"));
        mintime_slider->setMaximum(10);
        mintime_slider->setValue(5);
        mintime_slider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(mintime_slider);

        maxtime_slider = new QSlider(layoutWidget);
        maxtime_slider->setObjectName(QStringLiteral("maxtime_slider"));
        maxtime_slider->setMaximum(120);
        maxtime_slider->setValue(100);
        maxtime_slider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(maxtime_slider);

        minbetween_slider = new QSlider(layoutWidget);
        minbetween_slider->setObjectName(QStringLiteral("minbetween_slider"));
        minbetween_slider->setMaximum(10);
        minbetween_slider->setValue(1);
        minbetween_slider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(minbetween_slider);


        verticalLayout_2->addLayout(verticalLayout);

        maxbetween_slider = new QSlider(layoutWidget);
        maxbetween_slider->setObjectName(QStringLiteral("maxbetween_slider"));
        maxbetween_slider->setMaximum(10);
        maxbetween_slider->setValue(9);
        maxbetween_slider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(maxbetween_slider);

        layoutWidget1 = new QWidget(Parameters);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(250, 40, 231, 198));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        spinBox = new QSpinBox(layoutWidget1);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMaximum(10);
        spinBox->setValue(10);
        spinBox->setDisplayIntegerBase(10);

        verticalLayout_4->addWidget(spinBox);

        spinBox_2 = new QSpinBox(layoutWidget1);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMaximum(10);
        spinBox_2->setValue(7);

        verticalLayout_4->addWidget(spinBox_2);

        spinBox_3 = new QSpinBox(layoutWidget1);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setMaximum(10);
        spinBox_3->setValue(5);

        verticalLayout_4->addWidget(spinBox_3);

        spinBox_4 = new QSpinBox(layoutWidget1);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));
        spinBox_4->setAccelerated(true);
        spinBox_4->setMaximum(120);
        spinBox_4->setValue(100);

        verticalLayout_4->addWidget(spinBox_4);

        spinBox_5 = new QSpinBox(layoutWidget1);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));
        spinBox_5->setMaximum(10);
        spinBox_5->setValue(1);

        verticalLayout_4->addWidget(spinBox_5);

        spinBox_6 = new QSpinBox(layoutWidget1);
        spinBox_6->setObjectName(QStringLiteral("spinBox_6"));
        spinBox_6->setMaximum(10);
        spinBox_6->setValue(9);

        verticalLayout_4->addWidget(spinBox_6);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_3->addWidget(label);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_3->addWidget(label_2);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_3->addWidget(label_3);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_3->addWidget(label_4);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_3->addWidget(label_5);

        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_3->addWidget(label_6);


        horizontalLayout->addLayout(verticalLayout_3);

        label_7 = new QLabel(Parameters);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 10, 371, 21));
        label_7->setStyleSheet(QLatin1String("font: 75 12pt \"MS Shell Dlg 2\";\n"
"text-decoration: underline;"));
        layoutWidget->raise();
        buttonBox->raise();
        layoutWidget->raise();
        label_7->raise();

        retranslateUi(Parameters);
        QObject::connect(buttonBox, SIGNAL(accepted()), Parameters, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Parameters, SLOT(reject()));
        QObject::connect(onset_slider, SIGNAL(sliderMoved(int)), spinBox, SLOT(setValue(int)));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), onset_slider, SLOT(setValue(int)));
        QObject::connect(decay_slider, SIGNAL(valueChanged(int)), spinBox_2, SLOT(setValue(int)));
        QObject::connect(mintime_slider, SIGNAL(valueChanged(int)), spinBox_3, SLOT(setValue(int)));
        QObject::connect(maxtime_slider, SIGNAL(valueChanged(int)), spinBox_4, SLOT(setValue(int)));
        QObject::connect(minbetween_slider, SIGNAL(valueChanged(int)), spinBox_5, SLOT(setValue(int)));
        QObject::connect(maxbetween_slider, SIGNAL(valueChanged(int)), spinBox_6, SLOT(setValue(int)));
        QObject::connect(spinBox_2, SIGNAL(valueChanged(int)), decay_slider, SLOT(setValue(int)));
        QObject::connect(spinBox_3, SIGNAL(valueChanged(int)), mintime_slider, SLOT(setValue(int)));
        QObject::connect(spinBox_4, SIGNAL(valueChanged(int)), maxtime_slider, SLOT(setValue(int)));
        QObject::connect(spinBox_5, SIGNAL(valueChanged(int)), minbetween_slider, SLOT(setValue(int)));
        QObject::connect(spinBox_6, SIGNAL(valueChanged(int)), maxbetween_slider, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(Parameters);
    } // setupUi

    void retranslateUi(QDialog *Parameters)
    {
        Parameters->setWindowTitle(QApplication::translate("Parameters", "Parameters", Q_NULLPTR));
        label->setText(QApplication::translate("Parameters", "Onset (g)", Q_NULLPTR));
        label_2->setText(QApplication::translate("Parameters", "Decay (g)", Q_NULLPTR));
        label_3->setText(QApplication::translate("Parameters", "Min Time (s)", Q_NULLPTR));
        label_4->setText(QApplication::translate("Parameters", "Max Time (s)", Q_NULLPTR));
        label_5->setText(QApplication::translate("Parameters", "Min Time Between PLMs (s)", Q_NULLPTR));
        label_6->setText(QApplication::translate("Parameters", "Max Time Between PLMs(s)", Q_NULLPTR));
        label_7->setText(QApplication::translate("Parameters", "Parameter Settings", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Parameters: public Ui_Parameters {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETERS_H
