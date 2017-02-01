#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QDialog>

namespace Ui {
class editwindow;
}

class editwindow : public QDialog
{
    Q_OBJECT

public:
    explicit editwindow(QWidget *parent = 0);
    ~editwindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    //void on_buttonBox_accepted();

    void on_pushButton_5_clicked();

private:
    Ui::editwindow *ui;
};

#endif // EDITWINDOW_H
