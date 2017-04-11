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
        int count = 0;

        // If the input file is a csv file.
        if (input.right(3) == "csv") {
            while (!textStream.atEnd()) {
                textStream >> character;
                if (character == ',') {
                    row.push_back(temp.toDouble());
                    checkString(temp, character);
                } else if (character == '\n') {
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

        // If the input file is a txt file.
        if (input.right(3) == "txt") {
            while (!textStream.atEnd()) {
                textStream >> character;
                if ((character == ',') & (count != 6)) {
                    row.push_back(temp.toDouble());
                    checkString(temp, character);
                    count++;
                } else if ((character == ',') & (count == 6)) {
                    row.push_back(temp.toDouble());
                    dataArray.push_back(row);
                    row.clear();
                    checkString(temp, character);
                    count = 0;
                } else if (textStream.atEnd()) {
                    temp.append(character);
                    checkString(temp);
                } else {
                    temp.append(character);
                }
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
    long x_msb, x_lsb, y_msb, y_lsb, z_msb, z_lsb;
    for (int i = 0; i < dataArray.size(); i++) {
        //QDebug deb = qDebug();
        for (int j = 0; j < dataArray[0].size(); j++) {
           //deb << dataArray[i][j];
           if (j == 0) {
               structure.time_values.append(dataArray[i][j]);
               //deb << dataArray[i][j];
           }
           else if (j == 5) {
               z_msb = (long) dataArray[i][j];
               z_lsb = (long) dataArray[i][j+1];

               long zAccel = ((z_msb << 8) | z_lsb) >> 4;
               if (zAccel > 2047) zAccel += (~4096 + 1);
               double zAccelToAdd = ((double)zAccel)/512;
               structure.z_acc_values.append((zAccelToAdd));
           }
           else if (j == 3) {
               y_msb = (long) dataArray[i][j];
               y_lsb = (long) dataArray[i][j+1];

               long yAccel = ((y_msb << 8) | y_lsb) >> 4;
               if (yAccel > 2047) yAccel += (~4096 + 1);
               double yAccelToAdd = ((double)yAccel)/512;
               structure.y_acc_values.append((yAccelToAdd));
           }
           else if (j == 1) {
               x_msb = (long) dataArray[i][j];
               x_lsb = (long) dataArray[i][j+1];

               long xAccel = ((x_msb << 8) | x_lsb) >> 4;
               if (xAccel > 2047) xAccel += (~4096 + 1);
               double xAccelToAdd = ((double)xAccel)/512;
               structure.x_acc_values.append((xAccelToAdd));
           }
        }
      //qDebug() << "------------";
    }

    for (int i = 0; i < structure.x_acc_values.size(); i++) {
        double magnitude = sqrt(pow(structure.x_acc_values[i],2) + pow(structure.y_acc_values[i],2) + pow(structure.z_acc_values[i],2));
        if (magnitude > 4) {
            qDebug() << magnitude;
        }
        structure.magnitude_values.append(magnitude);
        //qDebug() << magnitude;
    }

    return structure;
}

void CsvReader::importMarkers(QString input) {
    QFile file (input);
    if (file.open(QIODevice::ReadOnly)) {
        QString data = file.readAll();
        data.remove( QRegExp("\r") ); //remove all ocurrences of CR (Carriage Return)
        QString temp;
        QChar character;
        QTextStream textStream(&data);
        QVector<double> row;
        int count = 0;

        while (!textStream.atEnd()) {
            textStream >> character;
            if ((character == ',') & (count != 1)) {
                row.push_back(temp.toDouble());
                checkString(temp, character);
                count++;
            } else if ((character == ',') & (count == 1)) {
                row.push_back(temp.toDouble());
                markerArray.push_back(row);
                row.clear();
                checkString(temp, character);
                count = 0;
            } else if (textStream.atEnd()) {
                temp.append(character);
                row.push_back(temp.toDouble());
                markerArray.push_back(row);
                checkString(temp);
            } else {
                temp.append(character);
            }

        }
    }
}

markerStructure CsvReader::exportMarkers(markerStructure structure) {
    for (int i = 0; i < markerArray.size(); i++) {
        //QDebug deb = qDebug();
        for (int j = 0; j < markerArray[0].size(); j++) {
           //deb << dataArray[i][j];
           if (j == 0) {
               structure.keyPosition.append(markerArray[i][j]);
               //deb << dataArray[i][j];
           } else {
               structure.id.append((markerArray[i][j]));
           }
        }
      //qDebug() << "------------";
    }

    return structure;
}

void CsvReader::importSelections(QString input) {
    QFile file (input);
    if (file.open(QIODevice::ReadOnly)) {
        QString data = file.readAll();
        data.remove( QRegExp("\r") ); //remove all ocurrences of CR (Carriage Return)
        QString temp;
        QChar character;
        QTextStream textStream(&data);
        QVector<double> row;
        int count = 0;

        while (!textStream.atEnd()) {
            textStream >> character;
            if ((character == ',') & (count != 3)) {
                row.push_back(temp.toDouble());
                checkString(temp, character);
                count++;
            } else if ((character == ',') & (count == 3)) {
                row.push_back(temp.toDouble());
                selectionArray.push_back(row);
                row.clear();
                checkString(temp, character);
                count = 0;
            } else if (textStream.atEnd()) {
                temp.append(character);
                row.push_back(temp.toDouble());
                selectionArray.push_back(row);
                checkString(temp);
            } else {
                temp.append(character);
            }

        }
    }
}

selectionStructure CsvReader::exportSelections(selectionStructure structure) {
    for (int i = 0; i < selectionArray.size(); i++) {
        for (int j = 0; j < selectionArray[0].size(); j++) {
           //deb << dataArray[i][j];
           if (j == 0) {
               structure.xAxisKeyMin.append(selectionArray[i][j]);
               //deb << dataArray[i][j];
           }
           else if (j == 3) {
               structure.xAxisValueMax.append((selectionArray[i][j]));
           }
           else if (j == 2) {
               structure.xAxisValueMin.append((selectionArray[i][j]));
           }
           else if (j == 1) {
               structure.xAxisKeyMax.append((selectionArray[i][j]));
           }
        }
      //qDebug() << "------------";
    }

    return structure;
}
