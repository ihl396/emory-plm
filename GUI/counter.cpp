#include <QObject>
#include <iostream>
#include <QTimer>
#include "counter.h"

using namespace std;

Counter::Counter(QObject *parent) :
QObject(parent)
{
m_counter = 0;
c = 1;
timer->start(200); // tick every 1 second (1000ms)
}
void Counter::doTheStuff()
{
if(m_counter < 5000)
setCounter(m_counter + c);
else
setCounter(0);
}

int Counter::getCounter()
{
return m_counter;
}

void Counter::setCounter(int c)
{
cout<<"setting counter"<<endl;
if (c != m_counter)
{
m_counter = c;
emit counterUpdated(m_counter);
}
}
