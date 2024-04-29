#include "Point.h"

Point::Point(const Point &Obj)
{
    if (Obj.x)
        x = new double(*Obj.x);
    else
    {
        x = nullptr;
    }

    if (Obj.y)
        y = new double(*Obj.y);
    else
    {
        y = nullptr;
    }
}

Point::~Point()
{
    if (x)
        delete x;

    if (y)
        delete y;
}

void Point::SetX(double Argx)
{
    if (x)
        *x = Argx;
    else
    {
        x = new double(Argx);
    }
}

void Point::SetY(double Argy)
{
    if (y)
        *y = Argy;
    else
    {
        y = new double(Argy);
    }
}

void Point::Print()
{
    if (x && y)
        std::cout << "(" << *x << ", " << *y << ")" << std::endl;
    else
    {
        std::cout << "Can't print! Either 'x' or 'y' is a nullptr!" << std::endl;
    }
}

void Point::operator=(const Point &Obj)
{
    if (this != &Obj)
    {
        if (x)
            delete x;

        if (Obj.x)
            x = new double(*Obj.x);
        else
        {
            x = nullptr;
        }

        if (y)
            delete y;

        if (Obj.y)
            y = new double(*Obj.y);
        else
        {
            y = nullptr;
        }
    }
}
