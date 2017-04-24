#ifndef CSVREADER_H
#define CSVREADER_H

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStandardItem>
#include <QList>
#include "datastructure.h"
#include <QDebug>

using namespace std;

class CsvReader {

    QVector<QString> timeArray;
    QVector<QVector<double>> dataArray;
    QVector<QVector<double>> markerArray;
    QVector<QVector<double>> selectionArray;
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
