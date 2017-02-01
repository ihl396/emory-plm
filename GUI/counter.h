#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
#include <iostream>
#include <QTimer>

using namespace std;

class Counter : public QObject
{
Q_OBJECT

Q_PROPERTY(float counter READ getCounter WRITE setCounter NOTIFY counterUpdated)

public:
explicit Counter(QObject *parent = 0);
int getCounter();
void setCounter(int);

signals:
void counterUpdated(int);

public slots:
void doTheStuff();

private:
int m_counter;
int c;
QTimer *timer;
};

#endif // COUNTER_H
