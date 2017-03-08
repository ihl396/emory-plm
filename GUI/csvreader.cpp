#include "csvreader.h"

CsvReader::CsvReader(QStandardItemModel *model) {
    QVector<QVector<double>> dataArray;
    QList<QStandardItem*> standardItemList;
    this->model = model;
}



void CsvReader::importCSV(QString input) {
    QFile file (input);
    if (file.open(QIODevice::ReadOnly)) {
        QString data = file.readAll();
        data.remove( QRegExp("\r") ); //remove all ocurrences of CR (Carriage Return)
        QString temp;
        QChar character;
        QTextStream textStream(&data);
        QVector<double> row;

        while (!textStream.atEnd()) {
            textStream >> character;
            if (character == ',') {
          //    qDebug() << "here:" << temp.toDouble();
                row.push_back(temp.toDouble());
                checkString(temp, character);
            } else if (character == '\n') {
          //    qDebug() << "here:" << temp.toDouble();
                row.push_back(temp.toDouble());
                dataArray.push_back(row);
                row.clear();
                checkString(temp, character);
            } else if (textStream.atEnd()) {
                temp.append(character);
                checkString(temp);
            } else {
                temp.append(character);
            }

        }
    }
}


void CsvReader::checkString(QString &temp, QChar character) {

    if(temp.count("\"")%2 == 0) {
        //if (temp.size() == 0 && character != ',') //problem with line endings
        //    return;
        if (temp.startsWith( QChar('\"')) && temp.endsWith( QChar('\"') ) ) {
             temp.remove( QRegExp("^\"") );
             temp.remove( QRegExp("\"$") );
        }
        //FIXME: will possibly fail if there are 4 or more reapeating double quotes
        temp.replace("\"\"", "\"");
        QStandardItem *item = new QStandardItem(temp);
        standardItemList.append(item);
        if (character != QChar(',')) {
            model->appendRow(standardItemList);
            standardItemList.clear();
        }
        temp.clear();
    } else {
        temp.append(character);
    }
}


DataStructure CsvReader::exportData(DataStructure structure) {
    for (int i = 0; i < dataArray.size(); i++) {
        //QDebug deb = qDebug();
        for (int j = 0; j < dataArray[0].size(); j++) {
           //deb << dataArray[i][j];
           if (j == 3) {
               structure.time_values.append(dataArray[i][j]);
               //deb << dataArray[i][j];
           }
           else if (j == 2) {
               structure.z_acc_values.append(dataArray[i][j]);
           }
           else if (j == 1) {
               structure.y_acc_values.append(dataArray[i][j]);
           }
           else if (j == 0) {
               structure.x_acc_values.append(dataArray[i][j]);
           }
        }
      //qDebug() << "------------";
    }

    for (int i = 0; i < structure.x_acc_values.size(); i++) {
        double magnitude = sqrt(pow(structure.x_acc_values[i],2) + pow(structure.y_acc_values[i],2) + pow(structure.z_acc_values[i],2));
        structure.magnitude_values.append(magnitude);
    }

    return structure;
}
