#ifndef OCTAVEINVOKER_H
#define OCTAVEINVOKER_H

#include <QtCore/QCoreApplication>
#include <iostream>
//#include <octave/oct.h>
//#include <octave/octave.h>
//#include <octave/parse.h>
//#include <octave/interpreter.h>
#include "datastructure.h"
#include <QProcess>

using namespace std;

class octaveinvoker
{
    QString octaveFileLocation;

    public:
        octaveinvoker();
        void setOctaveFileLocation(QString);
        selectionStructure callOctave(QVector<double>, QVector<double>);
};

#endif // OCTAVEINVOKER_H
