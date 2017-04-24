/********************************************************************************
** Form generated from reading UI file 'setupwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUPWINDOW_H
#define UI_SETUPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetupWindow
{
public:
    QTabWidget *preferencesTabWidget;
    QWidget *graphViewPreferenceTab;
    QPushButton *defaultGraphViewButton;
    QGroupBox *graphArrowMovementScaleGroupBox;
    QSlider *arrowMSHorizontalSlider;
    QSpinBox *arrowMSSpinBox;
    QGroupBox *graphViewGroupBox;
    QGroupBox *xAxisGroupBox;
    QLabel *keyViewScalingLabel;
    QSlider *keyScalingSlider;
    QSpinBox *keyScalingSpinBox;
    QGroupBox *yAxisGroupBox;
    QSlider *valueMaxSlider;
    QSpinBox *valueMaxSpinBox;
    QLabel *valueMaxLabel;
    QLabel *valueMinLabel;
    QSlider *valueMinSlider;
    QSpinBox *valueMinSpinBox;
    QPushButton *okGraphViewButton;
    QPushButton *cancelGraphViewButton;
    QWidget *labelPreferencesTab;
    QGroupBox *labelGroupBox;
    QGroupBox *labelTextGroupBox;
    QLineEdit *labelTextLineEdit;
    QGroupBox *labelColorGroupBox;
    QComboBox *labelColorComboBox;
    QPushButton *okLabelButton;
    QPushButton *cancelLabelButton;

    void setupUi(QDialog *SetupWindow)
    {
        if (SetupWindow->objectName().isEmpty())
            SetupWindow->setObjectName(QStringLiteral("SetupWindow"));
        SetupWindow->resize(552, 455);
        preferencesTabWidget = new QTabWidget(SetupWindow);
        preferencesTabWidget->setObjectName(QStringLiteral("preferencesTabWidget"));
        preferencesTabWidget->setGeometry(QRect(0, 0, 551, 451));
        graphViewPreferenceTab = new QWidget();
        graphViewPreferenceTab->setObjectName(QStringLiteral("graphViewPreferenceTab"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        graphViewPreferenceTab->setFont(font);
        defaultGraphViewButton = new QPushButton(graphViewPreferenceTab);
        defaultGraphViewButton->setObjectName(QStringLiteral("defaultGraphViewButton"));
        defaultGraphViewButton->setGeometry(QRect(20, 380, 141, 23));
        graphArrowMovementScaleGroupBox = new QGroupBox(graphViewPreferenceTab);
        graphArrowMovementScaleGroupBox->setObjectName(QStringLiteral("graphArrowMovementScaleGroupBox"));
        graphArrowMovementScaleGroupBox->setGeometry(QRect(10, 10, 521, 51));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setUnderline(true);
        font1.setWeight(75);
        graphArrowMovementScaleGroupBox->setFont(font1);
        arrowMSHorizontalSlider = new QSlider(graphArrowMovementScaleGroupBox);
        arrowMSHorizontalSlider->setObjectName(QStringLiteral("arrowMSHorizontalSlider"));
        arrowMSHorizontalSlider->setGeometry(QRect(60, 20, 451, 22));
        arrowMSHorizontalSlider->setInputMethodHints(Qt::ImhNone);
        arrowMSHorizontalSlider->setMinimum(1);
        arrowMSHorizontalSlider->setMaximum(10);
        arrowMSHorizontalSlider->setPageStep(1);
        arrowMSHorizontalSlider->setValue(5);
        arrowMSHorizontalSlider->setSliderPosition(5);
        arrowMSHorizontalSlider->setOrientation(Qt::Horizontal);
        arrowMSHorizontalSlider->setTickPosition(QSlider::TicksBelow);
        arrowMSHorizontalSlider->setTickInterval(1);
        arrowMSSpinBox = new QSpinBox(graphArrowMovementScaleGroupBox);
        arrowMSSpinBox->setObjectName(QStringLiteral("arrowMSSpinBox"));
        arrowMSSpinBox->setGeometry(QRect(10, 20, 42, 22));
        QFont font2;
        font2.setPointSize(8);
        font2.setBold(false);
        font2.setUnderline(false);
        font2.setWeight(50);
        arrowMSSpinBox->setFont(font2);
        arrowMSSpinBox->setMinimum(1);
        arrowMSSpinBox->setMaximum(10);
        arrowMSSpinBox->setValue(5);
        graphViewGroupBox = new QGroupBox(graphViewPreferenceTab);
        graphViewGroupBox->setObjectName(QStringLiteral("graphViewGroupBox"));
        graphViewGroupBox->setGeometry(QRect(10, 80, 521, 281));
        graphViewGroupBox->setFont(font1);
        xAxisGroupBox = new QGroupBox(graphViewGroupBox);
        xAxisGroupBox->setObjectName(QStringLiteral("xAxisGroupBox"));
        xAxisGroupBox->setGeometry(QRect(10, 30, 501, 81));
        QFont font3;
        font3.setPointSize(8);
        font3.setBold(false);
        font3.setItalic(true);
        font3.setUnderline(false);
        font3.setWeight(50);
        xAxisGroupBox->setFont(font3);
        keyViewScalingLabel = new QLabel(xAxisGroupBox);
        keyViewScalingLabel->setObjectName(QStringLiteral("keyViewScalingLabel"));
        keyViewScalingLabel->setGeometry(QRect(10, 20, 61, 16));
        QFont font4;
        font4.setItalic(false);
        font4.setKerning(true);
        keyViewScalingLabel->setFont(font4);
        keyScalingSlider = new QSlider(xAxisGroupBox);
        keyScalingSlider->setObjectName(QStringLiteral("keyScalingSlider"));
        keyScalingSlider->setGeometry(QRect(70, 40, 421, 22));
        keyScalingSlider->setFont(font4);
        keyScalingSlider->setMinimum(1);
        keyScalingSlider->setMaximum(10);
        keyScalingSlider->setPageStep(1);
        keyScalingSlider->setValue(5);
        keyScalingSlider->setOrientation(Qt::Horizontal);
        keyScalingSlider->setTickPosition(QSlider::TicksBelow);
        keyScalingSlider->setTickInterval(1);
        keyScalingSpinBox = new QSpinBox(xAxisGroupBox);
        keyScalingSpinBox->setObjectName(QStringLiteral("keyScalingSpinBox"));
        keyScalingSpinBox->setGeometry(QRect(10, 40, 51, 22));
        keyScalingSpinBox->setFont(font4);
        keyScalingSpinBox->setMinimum(1);
        keyScalingSpinBox->setMaximum(10);
        keyScalingSpinBox->setValue(5);
        yAxisGroupBox = new QGroupBox(graphViewGroupBox);
        yAxisGroupBox->setObjectName(QStringLiteral("yAxisGroupBox"));
        yAxisGroupBox->setGeometry(QRect(10, 120, 501, 141));
        yAxisGroupBox->setFont(font3);
        valueMaxSlider = new QSlider(yAxisGroupBox);
        valueMaxSlider->setObjectName(QStringLiteral("valueMaxSlider"));
        valueMaxSlider->setGeometry(QRect(90, 100, 401, 22));
        valueMaxSlider->setFont(font4);
        valueMaxSlider->setMinimum(1);
        valueMaxSlider->setMaximum(7);
        valueMaxSlider->setSingleStep(1);
        valueMaxSlider->setPageStep(1);
        valueMaxSlider->setValue(7);
        valueMaxSlider->setOrientation(Qt::Horizontal);
        valueMaxSlider->setTickPosition(QSlider::TicksBelow);
        valueMaxSlider->setTickInterval(1);
        valueMaxSpinBox = new QSpinBox(yAxisGroupBox);
        valueMaxSpinBox->setObjectName(QStringLiteral("valueMaxSpinBox"));
        valueMaxSpinBox->setGeometry(QRect(10, 100, 61, 22));
        valueMaxSpinBox->setFont(font4);
        valueMaxSpinBox->setMinimum(1);
        valueMaxSpinBox->setMaximum(7);
        valueMaxSpinBox->setValue(7);
        valueMaxLabel = new QLabel(yAxisGroupBox);
        valueMaxLabel->setObjectName(QStringLiteral("valueMaxLabel"));
        valueMaxLabel->setGeometry(QRect(10, 80, 81, 16));
        valueMaxLabel->setFont(font4);
        valueMinLabel = new QLabel(yAxisGroupBox);
        valueMinLabel->setObjectName(QStringLiteral("valueMinLabel"));
        valueMinLabel->setGeometry(QRect(10, 20, 71, 16));
        valueMinLabel->setFont(font4);
        valueMinSlider = new QSlider(yAxisGroupBox);
        valueMinSlider->setObjectName(QStringLiteral("valueMinSlider"));
        valueMinSlider->setGeometry(QRect(90, 40, 401, 22));
        valueMinSlider->setFont(font4);
        valueMinSlider->setMinimum(-7);
        valueMinSlider->setMaximum(1);
        valueMinSlider->setPageStep(1);
        valueMinSlider->setValue(-7);
        valueMinSlider->setOrientation(Qt::Horizontal);
        valueMinSlider->setTickPosition(QSlider::TicksBelow);
        valueMinSlider->setTickInterval(1);
        valueMinSpinBox = new QSpinBox(yAxisGroupBox);
        valueMinSpinBox->setObjectName(QStringLiteral("valueMinSpinBox"));
        valueMinSpinBox->setGeometry(QRect(10, 40, 61, 22));
        valueMinSpinBox->setFont(font4);
        valueMinSpinBox->setMinimum(-7);
        valueMinSpinBox->setMaximum(1);
        valueMinSpinBox->setValue(-7);
        okGraphViewButton = new QPushButton(graphViewPreferenceTab);
        okGraphViewButton->setObjectName(QStringLiteral("okGraphViewButton"));
        okGraphViewButton->setGeometry(QRect(360, 380, 75, 23));
        cancelGraphViewButton = new QPushButton(graphViewPreferenceTab);
        cancelGraphViewButton->setObjectName(QStringLiteral("cancelGraphViewButton"));
        cancelGraphViewButton->setGeometry(QRect(450, 380, 75, 23));
        preferencesTabWidget->addTab(graphViewPreferenceTab, QString());
        labelPreferencesTab = new QWidget();
        labelPreferencesTab->setObjectName(QStringLiteral("labelPreferencesTab"));
        labelGroupBox = new QGroupBox(labelPreferencesTab);
        labelGroupBox->setObjectName(QStringLiteral("labelGroupBox"));
        labelGroupBox->setGeometry(QRect(10, 20, 521, 341));
        labelGroupBox->setFont(font1);
        labelTextGroupBox = new QGroupBox(labelGroupBox);
        labelTextGroupBox->setObjectName(QStringLiteral("labelTextGroupBox"));
        labelTextGroupBox->setGeometry(QRect(10, 30, 481, 61));
        labelTextGroupBox->setFont(font3);
        labelTextLineEdit = new QLineEdit(labelTextGroupBox);
        labelTextLineEdit->setObjectName(QStringLiteral("labelTextLineEdit"));
        labelTextLineEdit->setGeometry(QRect(10, 20, 141, 20));
        QFont font5;
        font5.setItalic(false);
        labelTextLineEdit->setFont(font5);
        labelColorGroupBox = new QGroupBox(labelGroupBox);
        labelColorGroupBox->setObjectName(QStringLiteral("labelColorGroupBox"));
        labelColorGroupBox->setGeometry(QRect(10, 100, 481, 231));
        labelColorGroupBox->setFont(font3);
        labelColorComboBox = new QComboBox(labelColorGroupBox);
        labelColorComboBox->setObjectName(QStringLiteral("labelColorComboBox"));
        labelColorComboBox->setEnabled(true);
        labelColorComboBox->setGeometry(QRect(10, 20, 141, 22));
        labelColorComboBox->setFont(font5);
        labelColorComboBox->setEditable(true);
        okLabelButton = new QPushButton(labelPreferencesTab);
        okLabelButton->setObjectName(QStringLiteral("okLabelButton"));
        okLabelButton->setGeometry(QRect(360, 380, 75, 23));
        cancelLabelButton = new QPushButton(labelPreferencesTab);
        cancelLabelButton->setObjectName(QStringLiteral("cancelLabelButton"));
        cancelLabelButton->setGeometry(QRect(450, 380, 75, 23));
        preferencesTabWidget->addTab(labelPreferencesTab, QString());

        retranslateUi(SetupWindow);

        preferencesTabWidget->setCurrentIndex(0);
        labelColorComboBox->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(SetupWindow);
    } // setupUi

    void retranslateUi(QDialog *SetupWindow)
    {
        SetupWindow->setWindowTitle(QApplication::translate("SetupWindow", "Setup", Q_NULLPTR));
        defaultGraphViewButton->setText(QApplication::translate("SetupWindow", "Reset Graph View Settings", Q_NULLPTR));
        graphArrowMovementScaleGroupBox->setTitle(QApplication::translate("SetupWindow", "Graph Arrow Movement Scale", Q_NULLPTR));
        graphViewGroupBox->setTitle(QApplication::translate("SetupWindow", "Graph View Parameters", Q_NULLPTR));
        xAxisGroupBox->setTitle(QApplication::translate("SetupWindow", "X-Axis View", Q_NULLPTR));
        keyViewScalingLabel->setText(QApplication::translate("SetupWindow", "View Scaling: ", Q_NULLPTR));
        keyScalingSpinBox->setSuffix(QApplication::translate("SetupWindow", "0%", Q_NULLPTR));
        yAxisGroupBox->setTitle(QApplication::translate("SetupWindow", "Y-Axis View", Q_NULLPTR));
        valueMaxSpinBox->setSuffix(QApplication::translate("SetupWindow", " (g's)", Q_NULLPTR));
        valueMaxLabel->setText(QApplication::translate("SetupWindow", "Maximum Value:", Q_NULLPTR));
        valueMinLabel->setText(QApplication::translate("SetupWindow", "Minimum Value:", Q_NULLPTR));
        valueMinSpinBox->setSuffix(QApplication::translate("SetupWindow", " (g's)", Q_NULLPTR));
        okGraphViewButton->setText(QApplication::translate("SetupWindow", "Ok", Q_NULLPTR));
        cancelGraphViewButton->setText(QApplication::translate("SetupWindow", "Cancel", Q_NULLPTR));
        preferencesTabWidget->setTabText(preferencesTabWidget->indexOf(graphViewPreferenceTab), QApplication::translate("SetupWindow", "Graph View Preferences", Q_NULLPTR));
        labelGroupBox->setTitle(QApplication::translate("SetupWindow", "Label Parameters", Q_NULLPTR));
        labelTextGroupBox->setTitle(QApplication::translate("SetupWindow", "Label Text", Q_NULLPTR));
        labelTextLineEdit->setText(QApplication::translate("SetupWindow", "Leg Up", Q_NULLPTR));
        labelColorGroupBox->setTitle(QApplication::translate("SetupWindow", "Label Color", Q_NULLPTR));
        labelColorComboBox->setCurrentText(QString());
        okLabelButton->setText(QApplication::translate("SetupWindow", "Ok", Q_NULLPTR));
        cancelLabelButton->setText(QApplication::translate("SetupWindow", "Cancel", Q_NULLPTR));
        preferencesTabWidget->setTabText(preferencesTabWidget->indexOf(labelPreferencesTab), QApplication::translate("SetupWindow", "Label Preferences", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SetupWindow: public Ui_SetupWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUPWINDOW_H
