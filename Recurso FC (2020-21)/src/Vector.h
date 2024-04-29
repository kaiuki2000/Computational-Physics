#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "Point.h"

class Vector : public Point
{
public:
    Vector() : A(Point()), B(Point()) { ; }
    Vector(const Point &ArgA, const Point &ArgB) : A(Point(ArgA)), B(Point(ArgB)) { ; }
    Vector(const Point &ArgB) : A(Point(0, 0)), B(Point(ArgB)) { ; }
    ~Vector() { ; }

    void Print();

    void operator=(const Point &);

private:
    Point A, B;
};
#endif // __VECTOR_H__