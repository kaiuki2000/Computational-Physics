#include "ODEPoint.h"

//Default constructor
ODEPoint::ODEPoint(int ArgNdim, const double *Argx) : Ndim(ArgNdim), x(new double[ArgNdim + 1])
{
    for (int i = 0; i < Ndim + 1; i++)
    {
        x[i] = Argx[i];
    }
}

//Copy constructor
ODEPoint::ODEPoint(const ODEPoint &Obj) : Ndim(Obj.Ndim), x(new double[Obj.Ndim + 1])
{
    for (int i = 0; i < Ndim + 1; i++)
    {
        x[i] = Obj.x[i];
    }
}

//Destructor
ODEPoint::~ODEPoint()
{
    if (x)
        delete[] x;
}

//Operators
void ODEPoint::operator=(const ODEPoint &Obj)
{
    Ndim = Obj.Ndim;
    for (int i = 0; i < Ndim + 1; i++)
    {
        x[i] = Obj.x[i];
    }
}

double &ODEPoint::operator[](int i)
{
    return x[i];
}

double ODEPoint::operator[](int i) const
{
    return x[i];
}

//Friend methods: Print
ostream &operator<<(std::ostream &s, const ODEPoint &Obj)
{
    s << std::fixed << std::setprecision(6) << "(";
    for (int i = 0; i < Obj.Ndim; i++)
    {
        s << std::setw(9) << Obj.x[i] << ", ";
    }
    s << std::setw(9) << Obj.x[Obj.Ndim] << ")";
    return s;
}
