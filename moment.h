#ifndef MOMENT_H
#define MOMENT_H

#include <QPair>

class Moment
{

private:
    double p;
    double q;

    double value;

public:
    Moment();

    double getP();
    double getQ();
    double getValue();

    void setOrder(double p, double q);
    void setValue(double value);

};

#endif // MOMENT_H
