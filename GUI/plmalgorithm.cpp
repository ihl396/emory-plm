#include "plmalgorithm.h"

plmalgorithm::plmalgorithm(DataStructure data, double onset, double decay, double LM_start, double LM_end, double PLM_start, double PLM_end)
{
    this->data = data;
    this->onset = onset;
    this->decay = decay;
    this->LM_start = LM_start;
    this->LM_end = LM_end;
    this->PLM_start = PLM_start;
    this->PLM_end = PLM_end;
}

QVector<QVector<double>> plmalgorithm::isLM() {
    QVector<double> returnTimeStart;
    QVector<double> returnTimeEnd;
    QVector<double> returnMagStart;
    QVector<double> returnMagEnd;
    QVector<double> returnDuration;
    QVector<double> timeValues = data.time_values;
    QVector<double> magnitudeValues = data.magnitude_values;
    QVector<int> onsetIndex;
    QVector<int> decayIndex;
    QVector<double> magnitudeOnset;
    QVector<double> timeOnset;
    QVector<double> magnitudeDecay;
    QVector<double> timeDecay;
    int index = 0;

    for (int i = 0; i < magnitudeValues.length(); i++) {
        if (magnitudeValues.at(i) > onset) {
            magnitudeOnset.append(magnitudeValues.at(i));
            timeOnset.append(timeValues.at(i));
        }
    }

    for (int i = 0; i < magnitudeValues.length(); i++) {
        if (magnitudeValues.at(i) < decay) {
            magnitudeDecay.append(magnitudeValues.at(i));
            timeDecay.append(timeValues.at(i));
        }
    }

    for (int i = 0; i < magnitudeDecay.length(); i++) {
        double decayM = magnitudeDecay.at(i);
        double decayT = timeDecay.at(i);

        for (index; index < magnitudeOnset.length(); index++) {
            double onsetM = magnitudeOnset.at(index);
            double onsetT = timeOnset.at(index);

            if (onsetT > decayT) {
                break;
            }

            double duration = decayT - onsetT;

            if ((LM_start <= duration) && (duration <= LM_end)) {
                returnTimeStart.append(onsetT);
                returnTimeEnd.append(decayT);
                returnMagStart.append(onsetM);
                returnMagEnd.append(decayM);
                returnDuration.append(duration);

                while (timeOnset.at(index) < decayT) {
                    double x = timeOnset.at(index);
                    index++;
                }
                break;
            }

        }
    }

    QVector<QVector<double>> returnVector;
    returnVector.append(returnTimeStart);
    returnVector.append(returnTimeEnd);
    returnVector.append(returnMagStart);
    returnVector.append(returnMagEnd);
    returnVector.append(returnDuration);

    return returnVector;

}

QVector<QVector<double>> plmalgorithm::isPLM(QVector<QVector<double>> LM) {
    QVector<double> timeStart = LM.at(0);
    QVector<double> timeEnd = LM.at(1);
    QVector<double> magStart = LM.at(2);
    QVector<double> magEnd = LM.at(3);
    QVector<double> duration = LM.at(4);

    QVector<int> setIndex;
    QVector<double> returnTimeStart;
    QVector<double> returnTimeEnd;
    QVector<double> returnMagStart;
    QVector<double> returnMagEnd;

    for (int i = 0; i < timeStart.length()-1; i++) {
        double firstLMEnd = timeEnd.at(i);
        double secondLMStart = timeStart.at(i+1);
        double durationBetweenMovements = secondLMStart - firstLMEnd;

        if ((PLM_start < durationBetweenMovements) && (durationBetweenMovements < PLM_end)) {
            setIndex.append(i);
        } else {
            setIndex.append(i);
            if (setIndex.length() >= 4) {
                    returnTimeStart.append(timeStart.at(setIndex.at(0)));
                    returnTimeEnd.append(timeEnd.at(setIndex.at(setIndex.length()-1)));
                    returnMagStart.append(magStart.at(setIndex.at(0)));
                    returnMagEnd.append(magEnd.at(setIndex.at(setIndex.length()-1)));
                    setIndex.clear();
            } else {
                setIndex.clear();
            }
        }
    }

    QVector<QVector<double>> returnVector;
    returnVector.append(returnTimeStart);
    returnVector.append(returnTimeEnd);
    returnVector.append(returnMagStart);
    returnVector.append(returnMagEnd);

    return returnVector;
}

selectionStructure plmalgorithm::generateSelections() {

//    QProcess *myProcess = new QProcess(this);
//    myProcess->start(QString("C:/Program Files/MATLAB/R2016b/bin/matlab.exe"), QStringList() << QString("-r C:/Users/Asussy/Documents/GitHub/emory-plm/Octave/isLM.m") << QString("-nosplash") << QString("nodesktop"));
//    QByteArray s = myProcess->readAllStandardOutput();
//    QByteArray b = myProcess->readAllStandardError();
    QVector<QVector<double>> LM = isLM();
    QVector<QVector<double>> PLM = isPLM(LM);
    selectionStructure returnStructure;
    returnStructure.xAxisKeyMin = PLM.at(0);
    returnStructure.xAxisKeyMin = PLM.at(1);
    returnStructure.xAxisKeyMin = PLM.at(2);
    returnStructure.xAxisKeyMin = PLM.at(3);
    return returnStructure;
}
