#include "setupwindow.h"
#include "ui_setupwindow.h"
#include "graphviewer.h"

#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>

SetupWindow::SetupWindow(QWidget *parent) : //, GraphViewer *gViewer) ://Ui::MainWindow *main_ui) :
    QDialog(parent),
    ui(new Ui::SetupWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    //graphViewer = gViewer;
    setupGraphViewPreferencesTab();

    setupLabelPreferencesTab();
}

SetupWindow::~SetupWindow()
{
    delete ui;
}

void SetupWindow::getGraphViewer(GraphViewer *gViewer)
{
    graphViewer = gViewer;
}

void SetupWindow::setupGraphViewPreferencesTab()
{
    setupGraphViewSliders();
    setupGraphViewSpinBoxes();
    connect(ui->defaultGraphViewButton, SIGNAL(clicked(bool)), this, SLOT(resetDefaultGraphViewPreferences()));
    connect(ui->okGraphViewButton, SIGNAL(clicked(bool)), this, SLOT(okGraphViewButtonClicked()));
    connect(ui->cancelGraphViewButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(this, SIGNAL(rejected()), this, SLOT(close()));
}

void SetupWindow::setupGraphViewSliders()
{
    ui->arrowMSHorizontalSlider->setMinimum(1);
    ui->arrowMSHorizontalSlider->setMaximum(10);
    ui->arrowMSHorizontalSlider->setValue(ARROW_MOVEMENT_DEFAULT_VALUE);
    ui->arrowMSHorizontalSlider->setSingleStep(1);

    ui->keyScalingSlider->setMinimum(1);
    ui->keyScalingSlider->setMaximum(10);
    ui->keyScalingSlider->setValue(KEY_SCALING_DEFAULT_VALUE);

    ui->valueMinSlider->setMinimum(-7);
    ui->valueMinSlider->setMaximum(-1);
    ui->valueMinSlider->setValue(VALUE_MIN_DEFAULT_VALUE);

    ui->valueMaxSlider->setMinimum(1);
    ui->valueMaxSlider->setMaximum(7);
    ui->valueMaxSlider->setValue(VALUE_MAX_DEFAULT_VALUE);

    connect(ui->arrowMSHorizontalSlider, SIGNAL(valueChanged(int)), ui->arrowMSSpinBox, SLOT(setValue(int)));
    connect(ui->keyScalingSlider, SIGNAL(valueChanged(int)), ui->keyScalingSpinBox, SLOT(setValue(int)));
    connect(ui->valueMinSlider, SIGNAL(valueChanged(int)), ui->valueMinSpinBox, SLOT(setValue(int)));
    connect(ui->valueMaxSlider, SIGNAL(valueChanged(int)), ui->valueMaxSpinBox, SLOT(setValue(int)));
}

void SetupWindow::setupGraphViewSpinBoxes()
{
    ui->arrowMSSpinBox->setMinimum(1);
    ui->arrowMSSpinBox->setMaximum(10);
    ui->arrowMSSpinBox->setValue(ARROW_MOVEMENT_DEFAULT_VALUE);
    initArrowMovementValue = ARROW_MOVEMENT_DEFAULT_VALUE;
    currentArrowMovementValue = ARROW_MOVEMENT_DEFAULT_VALUE;

    ui->keyScalingSpinBox->setMinimum(1);
    ui->keyScalingSpinBox->setMaximum(10);
    ui->keyScalingSpinBox->setValue(KEY_SCALING_DEFAULT_VALUE);
    initKeyScalingValue = KEY_SCALING_DEFAULT_VALUE;
    currentKeyScalingValue = KEY_SCALING_DEFAULT_VALUE;

    ui->valueMinSpinBox->setMinimum(-7);
    ui->valueMinSpinBox->setMaximum(-1);
    ui->valueMinSpinBox->setValue(VALUE_MIN_DEFAULT_VALUE);
    initValueMinValue = VALUE_MIN_DEFAULT_VALUE;
    currentValueMinValue = VALUE_MIN_DEFAULT_VALUE;

    ui->valueMaxSpinBox->setMinimum(1);
    ui->valueMaxSpinBox->setMaximum(7);
    ui->valueMaxSpinBox->setValue(VALUE_MAX_DEFAULT_VALUE);
    initValueMaxValue = VALUE_MAX_DEFAULT_VALUE;
    currentValueMaxValue = VALUE_MAX_DEFAULT_VALUE;

    connect(ui->arrowMSSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setSliderScaledMovement(int)));
    connect(ui->keyScalingSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setSliderKeyScale(int)));
    connect(ui->valueMinSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setSliderValueMin(int)));
    connect(ui->valueMaxSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setSliderValueMax(int)));
}

void SetupWindow::okGraphViewButtonClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm", "Are you sure you want to confirm your changes?", QMessageBox::Yes|QMessageBox::No);

    //isOkButton = true;
    //isCancelButton = false;
    if (reply == QMessageBox::Yes)
    {
        qDebug() << "YES";
        // need to set the graph view ranges
        //graphViewPreferencesChanged = true;
        //setGraphViewChanges();
        graphViewer->setGraphRanges(getSliderKeyScale(), getSliderValueMin(), getSliderValueMax());
        isOkButton = true;
        closeSetupWindow = true;
        SetupWindow::close();
    }
    else
    {
        isOkButton = false;
        //graphViewPreferencesChanged = false;
    }
}

/*void SetupWindow::setGraphViewChanges()
{
    graphViewer->setGraphRanges(getSliderKeyScale(), getSliderValueMin(), getSliderValueMax()); //setCustomPlotChanges();
}*/

/*void SetupWindow::cancelGraphViewButtonClicked()
{
    isOkButton = false;
    if (ui->okGraphViewButton->isEnabled())
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Cancel", "Are you sure you want to cancel your changes? Your changes will not be saved.", QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            qDebug() << "YES";
            setInitialGraphViewConditions();
            closeSetupWindow = true;
            //isOkButton = true;
            ui->okGraphViewButton->setEnabled(false);
            SetupWindow::close();
        }
        //else
        //{
            //closeSetupWindow = false;
        //}
    }
    else
    {
        closeSetupWindow = true;
        //isOkButton = true; // to get out of close loop
        SetupWindow::close();
    }
}*/

void SetupWindow::setupLabelPreferencesTab()
{
    setupLabelTextLineEdit();
    setupLabelColorComboBox();
    //connect(ui->defaultLabelButton, SIGNAL(clicked(bool)), this, SLOT(resetDefaultLabelPreferences()));
    connect(ui->okLabelButton, SIGNAL(clicked(bool)), this, SLOT(okLabelButtonClicked()));
    connect(ui->cancelLabelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
    connect(this, SIGNAL(rejected()), this, SLOT(close()));
}

void SetupWindow::setupLabelTextLineEdit()
{
    ui->labelTextLineEdit->setText("Leg Up");
    initLabelText = ui->labelTextLineEdit->text();
    currentLabelText = ui->labelTextLineEdit->text();

    connect(ui->labelTextLineEdit, SIGNAL(textChanged(QString)), this, SLOT(setLabelText(QString)));
}

void SetupWindow::setupLabelColorComboBox()
{
    ui->labelColorComboBox->addItem("Red");
    ui->labelColorComboBox->addItem("Orange");
    ui->labelColorComboBox->addItem("Yellow");
    ui->labelColorComboBox->addItem("Green");
    ui->labelColorComboBox->addItem("Blue");
    ui->labelColorComboBox->addItem("Violet");
    ui->labelColorComboBox->setCurrentIndex(0);
    initLabelColorIndex = ui->labelColorComboBox->currentIndex();
    currentLabelColorIndex = ui->labelColorComboBox->currentIndex();

    connect(ui->labelColorComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setLabelColorIndex(int)));
}

void SetupWindow::okLabelButtonClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm", "Are you sure you want to confirm your changes?", QMessageBox::Yes|QMessageBox::No);

    //isOkButton = true;
    //isCancelButton = false;
    if (reply == QMessageBox::Yes)
    {
        qDebug() << "YES";
        //graphViewer->setLabelPreferences(getLabelText(), getLabelColorText());
        isOkButton = true;
        SetupWindow::close();
    }
    else
    {
        isOkButton = false;
        //graphViewPreferencesChanged = false;
    }
}

void SetupWindow::cancelBothTabs()
{
    isOkButton = false;
    if (ui->okGraphViewButton->isEnabled() || ui->okLabelButton->isEnabled())
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Cancel", "Are you sure you want to cancel your changes? Your changes will not be saved.", QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            qDebug() << "YES";
            setInitialGraphViewConditions();
            setInitialLabelConditions();
            closeSetupWindow = true;
            //isOkButton = true;
            ui->okGraphViewButton->setEnabled(false);
            ui->okLabelButton->setEnabled(false);
            SetupWindow::close();
        }
        //else
        //{
            //closeSetupWindow = false;
        //}
    }
    else
    {
        closeSetupWindow = true;
        //isOkButton = true; // to get out of close loop
        SetupWindow::close();
    }
}

/*void SetupWindow::cancelLabelButtonClicked()
{
    isOkButton = false;
    if (ui->okLabelButton->isEnabled())
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Cancel", "Are you sure you want to cancel your changes? Your changes will not be saved.", QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            qDebug() << "YES";
            setInitialLabelConditions();
            closeSetupWindow = true;
            //isOkButton = true;
            ui->okLabelButton->setEnabled(false);
            SetupWindow::close();
        }
        //else
        //{
            //closeSetupWindow = false;
        //}
    }
    else
    {
        closeSetupWindow = true;
        //isOkButton = true; // to get out of close loop
        SetupWindow::close();
    }
}*/

void SetupWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << sender();
    if (!isOkButton)// && !closeSetupWindow)
    {
        event->ignore();
        //if (sender() == QObject)
        //{
        emit cancelBothTabs();
        //}
        /*else if (ui->preferencesTabWidget->currentIndex() == 0)
        {
            emit cancelGraphViewButtonClicked();
        }
        else if (ui->preferencesTabWidget->currentIndex() == 1)
        {
            emit cancelLabelButtonClicked();
        }*/
    }

    if (closeSetupWindow)
    {
        closeSetupWindow = false;
        isOkButton = false;
        event->accept();
    }
}

int SetupWindow::getSliderScaledMovement()
{
    return ui->arrowMSHorizontalSlider->value();
}

int SetupWindow::getSliderKeyScale()
{
    return ui->keyScalingSlider->value();
}

int SetupWindow::getSliderValueMin()
{
    return ui->valueMinSlider->value();
}

int SetupWindow::getSliderValueMax()
{
    return ui->valueMaxSlider->value();
}

int SetupWindow::getSpinBoxScaledMovement()
{
    return ui->arrowMSSpinBox->value();
}

int SetupWindow::getSpinBoxKeyScale()
{
    return ui->keyScalingSpinBox->value();
}


int SetupWindow::getSpinBoxValueMin()
{
    return ui->valueMinSpinBox->value();
}


int SetupWindow::getSpinBoxValueMax()
{
    return ui->valueMaxSpinBox->value();
}

void SetupWindow::setSliderScaledMovement(int scaleMovement)
{
    ui->arrowMSHorizontalSlider->setValue(scaleMovement);
    currentArrowMovementValue = ui->arrowMSHorizontalSlider->value();
    ui->okGraphViewButton->setEnabled(true);
    ui->okLabelButton->setEnabled(true);
}

void SetupWindow::setSliderKeyScale(int keyScale)
{
    ui->keyScalingSlider->setValue(keyScale);
    currentKeyScalingValue = ui->keyScalingSlider->value();
    ui->okGraphViewButton->setEnabled(true);
    ui->okLabelButton->setEnabled(true);
}

void SetupWindow::setSliderValueMin(int valueMin)
{
    ui->valueMinSlider->setValue(valueMin);
    currentValueMinValue = ui->valueMinSlider->value();
    ui->okGraphViewButton->setEnabled(true);
    ui->okLabelButton->setEnabled(true);
}

void SetupWindow::setSliderValueMax(int valueMax)
{
    ui->valueMaxSlider->setValue(valueMax);
    currentValueMaxValue = ui->valueMaxSlider->value();
    ui->okGraphViewButton->setEnabled(true);
    ui->okLabelButton->setEnabled(true);
}

/*void SetupWindow::setSpinBoxScaledMovement(int scaleMovement)
{
    ui->arrowMSSpinBox->setValue(scaleMovement);
}

void SetupWindow::setSpinBoxKeyScale(int keyScale)
{
    ui->keyScalingSpinBox->setValue(keyScale);
}

void SetupWindow::setSpinBoxValueMin(int valueMin)
{
    ui->valueMinSpinBox->setValue(valueMin);
}

void SetupWindow::setSpinBoxValueMax(int valueMax)
{
    ui->valueMaxSpinBox->setValue(valueMax);
}*/

void SetupWindow::setLabelText(QString labelText)
{
    ui->labelTextLineEdit->setText(labelText);
    currentLabelText = ui->labelTextLineEdit->text();
    ui->okGraphViewButton->setEnabled(true);
    ui->okLabelButton->setEnabled(true);
}

void SetupWindow::setLabelColorIndex(int index)
{
    ui->labelColorComboBox->setCurrentIndex(index);
    currentLabelColorIndex = ui->labelColorComboBox->currentIndex();
    ui->okGraphViewButton->setEnabled(true);
    ui->okLabelButton->setEnabled(true);
}

QString SetupWindow::getLabelText()
{
    return ui->labelTextLineEdit->text();
}

QColor SetupWindow::getLabelColor()
{
   switch (ui->labelColorComboBox->currentIndex())
   {
   case RED:
       labelColor = QColor(225, 0, 0, 30);
       break;
   case ORANGE:
       labelColor = QColor(225, 153, 51, 30);
       break;
   case YELLOW:
       labelColor = QColor(225, 255, 0, 30);
       break;
   case GREEN:
       labelColor = QColor(0, 255, 0, 30);
       break;
   case BLUE:
       labelColor = QColor(0, 0, 255, 30);
       break;
   case VIOLET:
       labelColor = QColor(153, 51, 255, 30);
       break;
   }
   return labelColor;
}

void SetupWindow::setCurrentTabIndex(int index)
{
    ui->preferencesTabWidget->setCurrentIndex(index);
}

/*void SetupWindow::setCurrentConditions()
{
    //graphViewPreferencesChanged = false;
    ui->arrowMSHorizontalSlider->setValue(initArrowMovementValue);
    ui->keyScalingSlider->setValue(initKeyScalingValue);
    ui->valueMinSlider->setValue(initValueMinValue);
    ui->valueMaxSlider->setValue(initValueMaxValue);
    ui->okGrapheViewButton->setEnabled(false);
}*/

void SetupWindow::setInitialGraphViewConditions()
{
    //graphViewPreferencesChanged = false;
    ui->arrowMSHorizontalSlider->setValue(initArrowMovementValue);
    ui->keyScalingSlider->setValue(initKeyScalingValue);
    ui->valueMinSlider->setValue(initValueMinValue);
    ui->valueMaxSlider->setValue(initValueMaxValue);
    ui->okGraphViewButton->setEnabled(false);
}

void SetupWindow::setInitialLabelConditions()
{
    ui->labelTextLineEdit->setText(initLabelText);
    ui->labelColorComboBox->setCurrentIndex(initLabelColorIndex);
}

void SetupWindow::setOkGraphViewButtonEnabled()
{
    ui->okGraphViewButton->setEnabled(false);
}

void SetupWindow::setOkLabelButtonEnabled()
{
    ui->okLabelButton->setEnabled(false);
}

void SetupWindow::resetDefaultGraphViewPreferences()
{
    ui->arrowMSHorizontalSlider->setValue(ARROW_MOVEMENT_DEFAULT_VALUE);
    ui->keyScalingSlider->setValue(KEY_SCALING_DEFAULT_VALUE);
    ui->valueMinSlider->setValue(VALUE_MIN_DEFAULT_VALUE);
    ui->valueMaxSlider->setValue(VALUE_MAX_DEFAULT_VALUE);
}

/*void SetupWindow::resetDefaultLabelPreferences()
{
    ui->labelTextLineEdit->setText();
}*/
