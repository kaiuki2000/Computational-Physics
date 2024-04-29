#include "Vector.h"

void PP(Point *Obj)
{
    Obj->Print();
}

int main()
{
    Point P1(1., 3.);
    Point P2(5., 2.);
    P1.Print();
    P2.Print();
    Vector V(P1, P2); //V=vector de P1 para P2

    V = P1;
    V.Print();

    Point *A = new Vector(P1);
    //((Vector *)A)->Print();
    delete A;

    return 0;
}