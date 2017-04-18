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
    connect(ui->okGrapheViewButton, SIGNAL(clicked(bool)), this, SLOT(okButtonClicked()));
    connect(ui->cancelGraphViewButton, SIGNAL(clicked(bool)), this, SLOT(close()));
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

void SetupWindow::okButtonClicked()
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

void SetupWindow::cancelButtonClicked()
{
    isOkButton = false;
    if (ui->okGrapheViewButton->isEnabled())
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Cancel", "Are you sure you want to cancel your changes? Your changes will not be saved.", QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            qDebug() << "YES";
            setInitialConditions();
            closeSetupWindow = true;
            ui->defaultGraphViewButton->setEnabled(false);
            SetupWindow::close();
        }
        else
        {
            closeSetupWindow = false;
        }
    }
    else
    {
        closeSetupWindow = true;
        SetupWindow::close();
    }
}

void SetupWindow::setupLabelPreferencesTab()
{

}

void SetupWindow::closeEvent(QCloseEvent *event)
{
    if (!isOkButton)
    {
        event->ignore();
        emit cancelButtonClicked();
        if (closeSetupWindow)
        {
            event->accept();
        }
        else
        {

        }
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

bool SetupWindow::isGraphViewChanged()
{
    return graphViewPreferencesChanged;
}

void SetupWindow::setSliderScaledMovement(int scaleMovement)
{
    ui->arrowMSHorizontalSlider->setValue(scaleMovement);
    currentArrowMovementValue = ui->arrowMSHorizontalSlider->value();
    ui->okGrapheViewButton->setEnabled(true);
}

void SetupWindow::setSliderKeyScale(int keyScale)
{
    ui->keyScalingSlider->setValue(keyScale);
    currentKeyScalingValue = ui->keyScalingSlider->value();
    ui->okGrapheViewButton->setEnabled(true);
}

void SetupWindow::setSliderValueMin(int valueMin)
{
    ui->valueMinSlider->setValue(valueMin);
    currentValueMinValue = ui->valueMinSlider->value();
    ui->okGrapheViewButton->setEnabled(true);
}

void SetupWindow::setSliderValueMax(int valueMax)
{
    ui->valueMaxSlider->setValue(valueMax);
    currentValueMaxValue = ui->valueMaxSlider->value();
    ui->okGrapheViewButton->setEnabled(true);
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

void SetupWindow::setInitialConditions()
{
    //graphViewPreferencesChanged = false;
    ui->arrowMSHorizontalSlider->setValue(initArrowMovementValue);
    ui->keyScalingSlider->setValue(initKeyScalingValue);
    ui->valueMinSlider->setValue(initValueMinValue);
    ui->valueMaxSlider->setValue(initValueMaxValue);
    ui->okGrapheViewButton->setEnabled(false);
}

void SetupWindow::setOkButtonEnabled()
{
    ui->okGrapheViewButton->setEnabled(false);
}

void SetupWindow::resetDefaultGraphViewPreferences()
{
    ui->arrowMSHorizontalSlider->setValue(ARROW_MOVEMENT_DEFAULT_VALUE);
    ui->keyScalingSlider->setValue(KEY_SCALING_DEFAULT_VALUE);
    ui->valueMinSlider->setValue(VALUE_MIN_DEFAULT_VALUE);
    ui->valueMaxSlider->setValue(VALUE_MAX_DEFAULT_VALUE);
}

void SetupWindow::resetDefaultLabelPreferences()
{

}
