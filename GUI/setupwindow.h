#ifndef SETUPWINDOW_H
#define SETUPWINDOW_H

#include <QDialog>
#include "graphviewer.h"

namespace Ui {
class SetupWindow;
}

class SetupWindow : public QDialog
{
    Q_OBJECT

    //Ui::MainWindow *main_window_ui;
    class GraphViewer *graphViewer;
public:
    SetupWindow(QWidget *parent = 0);//, GraphViewer *gViewer = 0); //Ui::MainWindow *main_ui = 0);
    ~SetupWindow();
    void setCurrentTabIndex(int);
    void setInitialConditions();
    void setOkButtonEnabled();

    // Getter Methods
    void getGraphViewer(GraphViewer *gViewer);
    int getSliderScaledMovement();
    int getSliderKeyScale();
    int getSliderValueMin();
    int getSliderValueMax();
    int getSpinBoxScaledMovement();
    int getSpinBoxKeyScale();
    int getSpinBoxValueMin();
    int getSpinBoxValueMax();
    bool isGraphViewChanged();

    int initArrowMovementValue;
    int initKeyScalingValue;
    int initValueMinValue;
    int initValueMaxValue;
    int currentArrowMovementValue;
    int currentKeyScalingValue;
    int currentValueMinValue;
    int currentValueMaxValue;

private slots:
    void resetDefaultGraphViewPreferences();
    void resetDefaultLabelPreferences();

    // Setter Methods
    void setSliderScaledMovement(int);
    void setSliderKeyScale(int);
    void setSliderValueMin(int);
    void setSliderValueMax(int);
    /*void setSpinBoxScaledMovement(int);
    void setSpinBoxKeyScale(int);
    void setSpinBoxValueMin(int);
    void setSpinBoxValueMax(int);*/

    void okButtonClicked();
    void cancelButtonClicked();

private:
    Ui::SetupWindow *ui;
    void setupGraphViewPreferencesTab();
    void setupGraphViewSliders();
    void setupGraphViewSpinBoxes();
    //void setGraphViewChanges();

    void setupLabelPreferencesTab();

    //void mousePressEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *);

    const int ARROW_MOVEMENT_DEFAULT_VALUE = 5;
    const int KEY_SCALING_DEFAULT_VALUE = 5;
    const int VALUE_MIN_DEFAULT_VALUE = -7;
    const int VALUE_MAX_DEFAULT_VALUE = 7;
    bool graphViewPreferencesChanged = false;
    bool isOkButton = false;
    //bool isCancelButton = false;
    bool closeSetupWindow = false;
};

#endif // SETUPWINDOW_H
