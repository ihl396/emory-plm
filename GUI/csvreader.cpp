#include "csvreader.h"

CsvReader::CsvReader(QStandardItemModel *model) {
    QVector<QString> timeArray;
    QVector<QVector<double>> dataArray;
    QList<QStandardItem*> standardItemList;
    this->model = model;
}



void CsvReader::importCSV(QString input) {
    QFile file (input);
    if (file.open(QIODevice::ReadOnly)) {
        QString data = file.readAll();
        data.remove( QRegExp("\r") ); //remove all ocurrences of CR (Carriage Return)
        QString temp = "";
        QChar character;
        QTextStream textStream(&data);
        QVector<double> row;
        int count = 0;
        bool timeStamp = true;

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
            bool first = true;
            while (!textStream.atEnd()) {
                while (character != '\n' && first) {
                    textStream >> character;
                }

                first = false;
                textStream >> character;

                if ((character == '\n' || textStream.atEnd())) {
                        row.push_back(temp.toDouble());
                        dataArray.push_back(row);
                        row.clear();
                        timeStamp = true;
                        checkString(temp, character);
                } else if ((character == ',')) {
                    if (timeStamp) {
                        timeArray.push_back(temp);
                        timeStamp = false;
                    } else {
                        row.push_back(temp.toDouble());
                    }
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
           if (j == 4) {
               z_msb = (long) dataArray[i][j];
               z_lsb = (long) dataArray[i][j+1];

               long zAccel = ((z_msb << 8) | z_lsb) >> 4;
               if (zAccel > 2047) zAccel += (~4096 + 1);
               double zAccelToAdd = ((double)zAccel)/512;
               structure.z_acc_values.append((zAccelToAdd));
           } else if (j == 2) {
               y_msb = (long) dataArray[i][j];
               y_lsb = (long) dataArray[i][j+1];

               long yAccel = ((y_msb << 8) | y_lsb) >> 4;
               if (yAccel > 2047) yAccel += (~4096 + 1);
               double yAccelToAdd = ((double)yAccel)/512;
               structure.y_acc_values.append((yAccelToAdd));
           } else if (j == 0) {
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

    QVector<double> time_values;

    const QString sformat="hh:mm:ss:zzz"; //Generate Date

    for (int i = 0; i < timeArray.length(); i++) {
        QString singleTime = timeArray.at(i);
        singleTime = singleTime.right(singleTime.length()-3);
        int ind = singleTime.lastIndexOf(":");
        double ticks = (255 - (singleTime.right(singleTime.length()-ind-1).toDouble()))/255;
        QString manipulated = singleTime.left(ind);
        manipulated.append(":");
        manipulated.append(QString::number(ticks).mid(2, 3));

        double timeSeconds = QCPAxisTickerDateTime::dateTimeToKey(QDateTime(QDate::fromString("20170421", "yyyyMMdd"),QTime::fromString(manipulated, sformat)));
        time_values.append(timeSeconds);
    }

    structure.time_values = time_values;

    for (int i = 0; i < structure.x_acc_values.size(); i++) {
        double magnitude = sqrt(pow(structure.x_acc_values[i],2) + pow(structure.y_acc_values[i],2) + pow(structure.z_acc_values[i],2));
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
        QVector<int> intRow;
        QVector<QString> qStringRow;
        int count = 0;

        while (!textStream.atEnd()) {
            textStream >> character;
            if ((character == ',') & (count == 4)) {
                intRow.push_back(temp.toInt());
                selectionIntArray.push_back(intRow);
                intRow.clear();
                checkString(temp, character);
                count++;
            } else if ((character == ',') & (count == 5)) {
                qStringRow.push_back(QString(temp));
                selectionQStringArray.push_back(qStringRow);
                qStringRow.clear();
                checkString(temp, character);
                count = 0;
            } else if ((character == ',') & (count != 3)) {
                row.push_back(temp.toDouble());
                checkString(temp, character);
                count++;
            } else if ((character == ',') & (count == 3)) {
                row.push_back(temp.toDouble());
                selectionDoubleArray.push_back(row);
                row.clear();
                checkString(temp, character);
                count++;
            }
            else if (textStream.atEnd()) {
                temp.append(character);
                qStringRow.push_back(QString(temp));
                selectionQStringArray.push_back(qStringRow);
                qStringRow.clear();
                checkString(temp);
            } else {
                temp.append(character);
            }

        }
    }
}

selectionStructure CsvReader::exportSelections(selectionStructure structure) {
    for (int i = 0; i < selectionDoubleArray.size(); i++) {
        for (int j = 0; j < selectionDoubleArray[0].size() + 2; j++) {
           //deb << dataArray[i][j];
           if (j == 0) {
               structure.xAxisKeyMin.append(selectionDoubleArray[i][j]);
               //deb << dataArray[i][j];
           }
           else if (j == 3) {
               structure.xAxisValueMax.append((selectionDoubleArray[i][j]));
           }
           else if (j == 2) {
               structure.xAxisValueMin.append((selectionDoubleArray[i][j]));
           }
           else if (j == 1) {
               structure.xAxisKeyMax.append((selectionDoubleArray[i][j]));
           }
           else if (j == 4) {
               structure.colorIndex.append((selectionIntArray[i][0]));
           }
           else if (j == 5) {
               structure.labelText.append((selectionQStringArray[i][0]));
           }
        }
      //qDebug() << "------------";
    }

    return structure;
}
