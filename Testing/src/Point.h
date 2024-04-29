#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>

class Point
{
public:
    Point() : x(nullptr), y(nullptr) { ; }
    Point(double Argx, double Argy) : x(new double(Argx)), y(new double(Argy)) { ; }
    Point(const Point &Obj);
    ~Point();

    void SetX(double Argx);
    void SetY(double Argy);

    double *GetX() const { return x; };
    double *GetY() const { return y; };

    void Print();

    void operator=(const Point &Obj);

private:
    double *x;
    double *y;
};
#endif // __POINT_H__