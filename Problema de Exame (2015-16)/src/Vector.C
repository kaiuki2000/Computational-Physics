#include "Vector.h"

void Vector::Print()
{
    if ((A.GetX() && A.GetY()) && (B.GetX() && B.GetY()))
        std::cout << "(" << *B.GetX() - *A.GetX() << ", " << *B.GetY() - *A.GetY() << ")" << std::endl;
    else
    {
        std::cout << "Can't print! Either 'A' or 'B' is not a valid Point!" << std::endl;
    }
}

void Vector::operator=(const Point &Obj)
{
    if (Obj.GetX() && Obj.GetY())
    {
        A.SetX(0.);
        A.SetY(0.);

        B.SetX(*Obj.GetX());
        B.SetY(*Obj.GetY());
    }
    else
    {
        A = Point();
        B = Point();
    }
}
