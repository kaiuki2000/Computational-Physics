#include "ODEpoint.h"

//////////////////////////////////////// constructor

ODEpoint::ODEpoint(int fndim, const double *fx) : ndim(fndim), x(new double[fndim + 1])
{
    for (int i = 0; i < ndim + 1; i++)
    {
        x[i] = fx[i];
    }
}

//////////////////////////////////////// copy constructor

ODEpoint::ODEpoint(const ODEpoint &P) : ndim(P.ndim), x(new double[P.ndim + 1])
{
    for (int i = 0; i < ndim + 1; i++)
    {
        x[i] = P.x[i];
    }
}

/////////////////////////////////////// destructor

ODEpoint::~ODEpoint()
{
    if (x)
        delete[] x;
}

/////////////////////////////////////// operators

void ODEpoint::operator=(const ODEpoint &Pa)
{
    ndim = Pa.ndim;
    for (int i = 0; i < ndim + 1; i++)
    {
        x[i] = Pa.x[i];
    }
}

double &ODEpoint::operator[](int i)
{
    return x[i];
}

/////////////////////////////////////// Print (friend method)

ostream &operator<<(std::ostream &s, const ODEpoint &P)
{
    s << "(";
    for (int i = 0; i < P.ndim; i++)
    {
        s << P.x[i] << ", ";
    }
    s << P.x[P.ndim] << ")";
    return s;
}