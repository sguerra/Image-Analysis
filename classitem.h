#ifndef CLASSITEM_H
#define CLASSITEM_H

#include <QVector>
#include <QString>

const int METRIC_ABSOLUTE = 0;
const int METRIC_EUCLIDEAN = 1;
const int METRIC_INFINITE = 2;

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

    double getDistance(QVector<double> vector, int metric);

};

#endif // CLASSITEM_H
