#include "moment.h"

// Constructor

Moment::Moment()
{
    this->p = 0;
    this->q = 0;
}

// Public Methods

double Moment::getP(){
    return this->p;
}

double Moment::getQ(){
    return this->q;
}

double Moment::getValue(){
    return value;
}

void Moment::setOrder(double p, double q){
    this->p = p;
    this->q = q;
}

void Moment::setValue(double value){
    this->value = value;
}

