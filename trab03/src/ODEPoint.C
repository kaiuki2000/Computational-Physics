#include "ODEPoint.h"

//Constructor1: int + double*
ODEPoint::ODEPoint(int ArgNdim, const double *Argx) : Ndim(ArgNdim)
{
    if (Argx)
    {
        for (int i = 0; i < Ndim + 1; i++)
            x.push_back(Argx[i]);
    }
}

//Constructor2: int + std::vector<double>
ODEPoint::ODEPoint(int ArgNdim, const std::vector<double> &Argx) : Ndim(ArgNdim)
{
    x = Argx;
}

//Copy constructor
ODEPoint::ODEPoint(const ODEPoint &Obj) : Ndim(Obj.Ndim)
{
    x = Obj.x;
}

//Destructor
ODEPoint::~ODEPoint()
{
    x.clear();
}

//GetArray method
double *ODEPoint::GetArray() const
{
    double *xArray = new double[Ndim + 1];

    for (int i = 0; i < Ndim + 1; i++)
    {
        xArray[i] = x[i];
    }

    return xArray;
}

//Operators
//Operator*
ODEPoint ODEPoint::operator*(double lambda) const
{
    ODEPoint CopyObj(*this);

    for (int i = 0; i < CopyObj.Ndim + 1; i++)
        CopyObj.x[i] *= lambda;

    return CopyObj;
}

//Operator+
ODEPoint ODEPoint::operator+(const ODEPoint &Obj) const
{
    if (Obj.Ndim == this->Ndim)
    {
        ODEPoint CopyObj(*this);

        for (int i = 0; i < CopyObj.Ndim + 1; i++)
            CopyObj.x[i] += Obj.x[i];

        return CopyObj;
    }
    else
    {
        std::cout << "***Error***: ODEPoint dimensions do not match...! Returning 'empty' ODEPoint" << std::endl;
        return (ODEPoint());
    }
}

//Operator-
ODEPoint ODEPoint::operator-(const ODEPoint &Obj) const
{
    if (Obj.Ndim == this->Ndim)
    {
        ODEPoint CopyObj(*this);

        for (int i = 0; i < CopyObj.Ndim + 1; i++)
            CopyObj.x[i] -= Obj.x[i];

        return CopyObj;
    }
    else
    {
        std::cout << "***Error***: ODEPoint dimensions do not match...! Returning 'empty' ODEPoint" << std::endl;
        return (ODEPoint());
    }
}

//Operator=
void ODEPoint::operator=(const ODEPoint &Obj)
{
    if (this != &Obj)
    {
        Ndim = Obj.Ndim;
        x = Obj.x;
    }
}

//Operator[] const
double ODEPoint::operator[](int i) const
{
    if (i >= 0 && i < Ndim + 1)
    {
        return x[i];
    }
    else
    {
        std::cout << "***Error***: Invalid argument...! Argument must be in the interval [0," << Ndim + 1 << "] Returning 'x[0]'" << std::endl;
        return x[0];
    }
}

//Operator[]
double &ODEPoint::operator[](int i)
{
    if (i >= 0 && i < Ndim + 1)
    {
        return x[i];
    }
    else
    {
        std::cout << "***Error***: Invalid argument...! Argument must be in the interval [0," << Ndim + 1 << "] Returning 'x[0]'" << std::endl;
        return x[0];
    }
}

//Friend methods
std::ostream &operator<<(std::ostream &S, const ODEPoint &Obj)
{
    S << "(";
    for (int i = 0; i < Obj.Ndim + 1; i++)
    {
        S << std::fixed << std::setprecision(6) << Obj.x[i];
        if (i < Obj.Ndim)
            S << ", ";
    }
    S << ")";
    return S;
}
