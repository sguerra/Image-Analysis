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

double ClassItem::getDistance(QVector<double> vector, int metric){

    double distance = 0;

    for(int i = 0; i < this->vector.size(); i++){

        if(metric == METRIC_ABSOLUTE){
            distance += qAbs(this->vector[i] - vector[i]);
        }
        else if(metric == METRIC_EUCLIDEAN){
            distance += qPow(this->vector[i] - vector[i], 2);
        }
        else if(metric == METRIC_INFINITE){
            double absolute = qAbs(this->vector[i] - vector[i]);
            distance = absolute > distance ? absolute : distance;
        }
    }

    if(metric == METRIC_EUCLIDEAN){
        distance = qSqrt(distance);
    }

    return distance;
}


