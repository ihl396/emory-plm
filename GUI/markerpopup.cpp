#include "markerpopup.h"
#include "ui_markerpopup.h"


#include <QDebug>

//class Mainwindow;

MarkerPopup::MarkerPopup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MarkerPopup)
{
    ui->setupUi(this);
    this->setModal(true);
//    MainWindow *pmainwindow;
//    pmainwindow = new MainWindow;
//    connect(ui->buttonBox, SIGNAL(accepted()), pmainwindow, SLOT(markerfc()));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(setCol()));
    connect(ui->spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(setCol()));
    connect(ui->spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(setCol()));
    MarkerPopup::setCol();
    connect(this, SIGNAL(accepted()), this, SLOT(strListData()));
}

MarkerPopup::~MarkerPopup()
{
    delete ui;
}

void MarkerPopup::setTagName(QString tagnum)
{
    QString tagname = "Marker ";
    tagname.append(tagnum);
    ui->marker_name->setText(tagname);

}

void MarkerPopup::setCol()
{
    m_color.setRgb(ui->spinBox->value(),ui->spinBox_2->value(),ui->spinBox_3->value());
    QPalette pal = ui->color_disp->palette();
    pal.setColor(QPalette::Window, m_color);
    ui->color_disp->setPalette(pal);
    emit ColorChanged(m_color);
}

void MarkerPopup::strListData(){

    QString comment = ui->lineEdit->text();
    QStringList markerinfo;
    int red = ui->spinBox->value() ; int green = ui->spinBox_2->value(); int blue = ui->spinBox_3->value();
    markerinfo << QString::number(red) << QString::number(green) << QString::number(blue) << comment;
    emit markerDataSend(markerinfo);


}

void MarkerPopup::getMarkerName(QString markertag)
{
    ui->marker_name->setText(markertag);
}
