#include "labelpopup.h"
#include "ui_labelpopup.h"

LabelPopup::LabelPopup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LabelPopup)
{
    ui->setupUi(this);
    connect(this, SIGNAL(accepted()), this, SLOT(strListData()));
}

LabelPopup::~LabelPopup()
{
    delete ui;
}

void LabelPopup::setTagName(QString tagnum)
{
    QString tagname = "Marker ";
    tagname.append(tagnum);
    ui->label_name->setText(tagname);

}

void LabelPopup::getLabelName(QString labeltag)
{
    ui->label_name->setText(labeltag);
}

void LabelPopup::strListData(){

    QString comment = ui->lineEdit->text();
    QStringList labelinfo;
    QString combotext;
    if (ui->comboBox->currentText() == "Square"){
        combotext = "Square";
    }
    else if (ui->comboBox->currentText() == "Circle"){
        combotext = "Circle";
    }
    labelinfo << combotext << comment;
//    int red = ui->spinBox->value() ; int green = ui->spinBox_2->value(); int blue = ui->spinBox_3->value();
//    labelinfo << QString::number(red) << QString::number(green) << QString::number(blue) << comment;
    emit labelDataSend(labelinfo);


}
