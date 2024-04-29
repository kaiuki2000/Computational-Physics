#include "point2D.h"

void Printpointname(point *obj)
{
    cout << "Tipo de point: " << obj->GetName() << endl;
}

int main()
{
    point1D P(4.);
    P.Print();
    cout << "Norma de P(point1D)= " << P.Norma() << endl;
    Printpointname(&P);
    cout << endl;

    point2D P2(1., 2.);
    P2.Print();
    cout << "Norma de P2(point2D)= " << P2.Norma() << endl;
    Printpointname(&P2);

    return 0;
}