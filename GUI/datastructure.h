#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <QVector>
using namespace std;

struct DataStructure {
    QVector<QString> time_values;
    QVector<double> x_acc_values;
    QVector<double> y_acc_values;
    QVector<double> z_acc_values;
    QVector<double> magnitude_values;
};

struct markerStructure {
    QVector<double> keyPosition;
    QVector<double> id;
};

struct selectionStructure {
    QVector<double> xAxisKeyMin;
    QVector<double> xAxisKeyMax;
    QVector<double> xAxisValueMin;
    QVector<double> xAxisValueMax;
};

#endif // DATASTRUCTURE_H
