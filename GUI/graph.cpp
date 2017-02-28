#include "graph.h"

Graph::Graph()
{
}

void Markup::read(const QJSonObject &json)
{
    p_markups.clear();
    QJsonArray m_array = json["markups"].toArray();
    for(int m_Index = 0; m_Index < m_array.size(); ++m_Index)
    {
        QJSonObject m_object = m_array[m_Index].toObject();
        Markup m;
        m.read(m_object);
        p_markups.append(m);
    }
}

void Markup::write(QJSonObject &json) const
{
    QJsonArray m_array;
    foreach (const Markup m, p_markups)
    {
        QJsonObject m_object;
        m.write(m_object);
        m_array.append(m_object);
    }
    json["Markups"] = p_markups;
}

void annotate(const Markup markup)
{
    //Code which annotates the graph
}
