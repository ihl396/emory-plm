#ifndef PLMALGORITHM_H
#define PLMALGORITHM_H

#include <QtCore/QCoreApplication>
#include <iostream>
#include <QDebug>
#include "datastructure.h"
#include <unordered_map>
using namespace std;

class plmalgorithm
{
    DataStructure data;

    public:
        plmalgorithm(DataStructure, double, double, double, double, double, double);
        void setOctaveFileLocation(QString);
        selectionStructure generateSelections();
        QVector<QVector<double>> isLM();
        QVector<QVector<double>> isPLM(QVector<QVector<double>>);
    private:
        double onset;
        double decay;
        double LM_start;
        double LM_end;
        double PLM_start;
        double PLM_end;
};

#endif // PLMALGORITHM_H
