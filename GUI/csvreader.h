#ifndef CSVREADER_H
#define CSVREADER_H

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStandardItem>
#include <QList>
#include "datastructure.h"

using namespace std;

class CsvReader {

    QVector<QVector<double>> dataArray;
    QList<QStandardItem*> standardItemList;
    QStandardItemModel *model;

    public:
        CsvReader (QStandardItemModel*);
        void checkString (QString &temp, QChar character = 0);
        void importCSV(QString);
        DataStructure exportData (DataStructure);
};

#endif // CSVREADER_H
