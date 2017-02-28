#ifndef GRAPH_H
#define GRAPH_H

#include<QList>
#include<markup.h>
#include<QJsonObject>
#include<QString>
#include<QJsonArray>

class Graph
{
public:
    Graph();
    QList<Markup> Markups;
    void annotate(const Markup &markup);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
private:
    QList<Markup> p_markups;
};

#endif // GRAPH_H
