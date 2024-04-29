#ifndef __POINT2D_H__
#define __POINT2D_H__

#include "point1D.h"

class point2D : public point1D
{
public:
    point2D() { this->SetName("point2D"); }
    point2D(double Argx, double Argy)
    {
        this->SetName("point2D");
        x = Argx;
        y = Argy;
    }
    ~point2D() { ; }
    double Norma()
    {
        printf("[%s] ", __PRETTY_FUNCTION__);
        return sqrt(x * x + y * y);
    };
    void Print()
    {
        printf("[%s] ", __PRETTY_FUNCTION__);
        cout << "(" << x << ", " << y << ")" << endl;
    }
    void SetPoint(double *Argx)
    {
        printf("[%s] ", __PRETTY_FUNCTION__);
        x = Argx[0];
        y = Argx[1];
    };

private:
    double y;
};

#endif // __POINT2D_H__