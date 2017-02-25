#ifndef MARKUP_H
#define MARKUP_H

#include<QString>
#include<QJsonObject>
#include<QColor>

class Markup
{
public:
    enum ToolType { Shade, Trace };
    enum MarkType { I, P, R, U, D, N }; //Sample letter types, N = None

    Markup();
    Markup(ToolType tooltype, int key, double height, Marktype marktype, QColor rgba);

    QString notes() const;
    void setNotes(const Qstring &notes);

    int key() const;
    void setKey(int key);

    double height() const;
    void setHeight(double height);

    ToolType toolType() const;
    void setToolType(ToolType tooltype);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

private:
    QString notes;
    int key;
    double height;
    QColor rgba;
    ToolType tooltype;
    MarkType marktype;
};

#endif // MARKUP_H
