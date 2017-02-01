#ifndef MARKERPOPUP_H
#define MARKERPOPUP_H



#include <QDialog>
#include <QColor>
#include <QWidget>
#include <QPalette>
#include <QObject>
#include <QSpinBox>
#include <QStringList>

namespace Ui {
class MarkerPopup;
}
//class MainWindow;
class MarkerPopup : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color NOTIFY ColorChanged)

public:
    explicit MarkerPopup(QWidget *parent = 0);
    ~MarkerPopup();
    //MainWindow *pmainwindow;


    QColor color() const
    {
        return m_color;
    }

public slots:

    void setCol();
    void strListData();
    void getMarkerName(QString);
    void setTagName(QString);

signals:
    void ColorChanged(QColor);
    void markerDataSend(QStringList);


private:
    Ui::MarkerPopup *ui;
    QColor w_color;
    QColor m_color;
};

#endif // MARKERPOPUP_H
