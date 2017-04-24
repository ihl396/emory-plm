#include "octaveinvoker.h"

octaveinvoker::octaveinvoker()
{
    octaveFileLocation = "";
}

void octaveinvoker::setOctaveFileLocation(QString) {

}

selectionStructure octaveinvoker::callOctave() {

//    QProcess *myProcess = new QProcess(this);
//    myProcess->start(QString("C:/Program Files/MATLAB/R2016b/bin/matlab.exe"), QStringList() << QString("-r C:/Users/Asussy/Documents/GitHub/emory-plm/Octave/isLM.m") << QString("-nosplash") << QString("nodesktop"));
//    QByteArray s = myProcess->readAllStandardOutput();
//    QByteArray b = myProcess->readAllStandardError();

    selectionStructure returnStructure;
    return returnStructure;

}
