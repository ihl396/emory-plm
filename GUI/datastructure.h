#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <QVector>
using namespace std;

struct DataStructure {
    QVector<double> time_values;
    QVector<double> x_acc_values;
    QVector<double> y_acc_values;
    QVector<double> z_acc_values;
    QVector<double> magnitude_values;
};

#endif // DATASTRUCTURE_H
