#include "classitem.h"
#include <QtMath>

// Constructor

ClassItem::ClassItem(){

}
ClassItem::ClassItem(QVector<double> vector, QString className)
{
    this->vector = vector;
    this->className = className;
}

// Public Methods

QVector<double> ClassItem::getVector(){
    return this->vector;
}

QString ClassItem::getClassName(){
    return this->className;
}

double ClassItem::getDistance(QVector<double> vector, int option){

    double distance = 0;

    for(int i = 0; i < this->vector.size(); i++){
        distance += qPow(this->vector[i] - vector[i], 2);
    }

    distance = qSqrt(distance);
    return distance;
}


