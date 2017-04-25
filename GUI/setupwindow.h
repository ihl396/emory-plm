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
    void setInitialGraphViewConditions();
    void setInitialLabelConditions();
    void setOkGraphViewButtonEnabled();
    void setOkLabelButtonEnabled();

    // Graph View Getter Methods
    void getGraphViewer(GraphViewer *gViewer);
    int getSliderScaledMovement();
    int getSliderKeyScale();
    int getSliderValueMin();
    int getSliderValueMax();
    int getSpinBoxScaledMovement();
    int getSpinBoxKeyScale();
    int getSpinBoxValueMin();
    int getSpinBoxValueMax();

    // Label Getter Methods
    QString getLabelText();
    QColor getLabelColor();

    int initArrowMovementValue;
    int initKeyScalingValue;
    int initValueMinValue;
    int initValueMaxValue;
    int currentArrowMovementValue;
    int currentKeyScalingValue;
    int currentValueMinValue;
    int currentValueMaxValue;

    QString initLabelText;
    QString initLabelColorText;
    int initLabelColorIndex;
    QString currentLabelText;
    QString currentLabelColorText;
    QColor labelColor;
    int currentLabelColorIndex;

private slots:
    void resetDefaultGraphViewPreferences();
    //void resetDefaultLabelPreferences();

    // Setter Methods
    void setSliderScaledMovement(int);
    void setSliderKeyScale(int);
    void setSliderValueMin(int);
    void setSliderValueMax(int);
    /*void setSpinBoxScaledMovement(int);
    void setSpinBoxKeyScale(int);
    void setSpinBoxValueMin(int);
    void setSpinBoxValueMax(int);*/

    void setLabelText(QString labelText);
    void setLabelColorIndex(int index);

    void okGraphViewButtonClicked();
    void okLabelButtonClicked();
    //void cancelGraphViewButtonClicked();
    //void cancelLabelButtonClicked();
    void cancelBothTabs();

private:
    Ui::SetupWindow *ui;
    void setupGraphViewPreferencesTab();
    void setupGraphViewSliders();
    void setupGraphViewSpinBoxes();
    //void setGraphViewChanges();

    void setupLabelPreferencesTab();
    void setupLabelTextLineEdit();
    void setupLabelColorComboBox();

    //void mousePressEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *);

    const int ARROW_MOVEMENT_DEFAULT_VALUE = 5;
    const int KEY_SCALING_DEFAULT_VALUE = 5;
    const int VALUE_MIN_DEFAULT_VALUE = -4;
    const int VALUE_MAX_DEFAULT_VALUE = 4;
    //bool graphViewPreferencesChanged = false;
    bool isOkButton = false;
    //bool isCancelButton = false;
    bool closeSetupWindow = false;
    enum Colors
    {
        RED = 0,
        ORANGE = 1,
        YELLOW = 2,
        GREEN = 3,
        BLUE = 4,
        VIOLET = 5
    };
};

#endif // SETUPWINDOW_H
