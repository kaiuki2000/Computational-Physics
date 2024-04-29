#ifndef __POINT1D_H__
#define __POINT1D_H__

#include "point.h"
#include <cmath>

class point1D : public point
{
public:
    point1D() { this->SetName("point1D"); };
    point1D(double Argx)
    {
        this->SetName("point1D");
        x = Argx;
    }
    virtual ~point1D() { ; }
    double Norma()
    {
        printf("[%s] ", __PRETTY_FUNCTION__);
        return fabs(x);
    };
    void Print()
    {
        printf("[%s] ", __PRETTY_FUNCTION__);
        cout << "(" << x << ")" << endl;
    };
    void SetPoint(double *Argx)
    {
        printf("[%s] ", __PRETTY_FUNCTION__);
        x = *Argx;
    };

protected:
    double x;
};
#endif // __POINT1D_H__