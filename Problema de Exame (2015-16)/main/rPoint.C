#include "Point.h"

int main()
{
    Point *P12;
    {
        Point P1(1.5, 3.);
        Point P2;
        P2.SetX(0.2);
        P2.SetY(-0.4);

        P1.Print();
        P2.Print();

        P12 = new Point(P1);
    }

    Point P3 = *P12;
    Point P4;
    P3.Print();

    return 0;
}