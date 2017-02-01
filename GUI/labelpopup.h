#ifndef LABELPOPUP_H
#define LABELPOPUP_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class LabelPopup;
}

class LabelPopup : public QDialog
{
    Q_OBJECT

public:
    explicit LabelPopup(QWidget *parent = 0);
    ~LabelPopup();

public slots:
    void setTagName(QString);
    void getLabelName(QString);
    void strListData();

signals:
    void labelDataSend(QStringList);

private:
    Ui::LabelPopup *ui;
};

#endif // LABELPOPUP_H
