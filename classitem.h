#ifndef CLASSITEM_H
#define CLASSITEM_H

#include <QVector>
#include <QString>

class ClassItem
{
private:
    QVector<double> vector;
    QString className;

public:
    ClassItem();
    ClassItem(QVector<double> vector, QString className);

    QVector<double> getVector();
    QString getClassName();

    double getDistance(QVector<double> vector, int option);

};

#endif // CLASSITEM_H
