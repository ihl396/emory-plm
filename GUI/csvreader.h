#ifndef CSVREADER_H
#define CSVREADER_H

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStandardItem>
#include <QList>
#include "datastructure.h"
#include <QDebug>
#include <QTime>
#include <QDateTime>
#include "qcustomplot.h"

using namespace std;

class CsvReader {

    QVector<QString> timeArray;
    QVector<QVector<double>> dataArray;
    QVector<QVector<double>> markerArray;
    QVector<QVector<double>> selectionDoubleArray;
    QVector<QVector<int>> selectionIntArray;
    QVector<QVector<QString>> selectionQStringArray;
    QList<QStandardItem*> standardItemList;
    QStandardItemModel *model;

    public:
        CsvReader (QStandardItemModel*);
        void checkString (QString &temp, QChar character = 0);
        void importCSV(QString);
        void importMarkers(QString);
        void importSelections(QString);
        DataStructure exportData (DataStructure);
        markerStructure exportMarkers(markerStructure);
        selectionStructure exportSelections(selectionStructure);
};

#endif // CSVREADER_H
