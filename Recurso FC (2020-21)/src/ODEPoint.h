#ifndef __ODEPOINT_H__
#define __ODEPOINT_H__

#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class ODEPoint
{
public:
    //Constructors and destructor
    ODEPoint(int ArgNdim = 0, const double *Argx = nullptr); //Default constructor
    ODEPoint(const ODEPoint &);                              //Copy constructor
    ~ODEPoint();                                             //Destructor

    //'Getters'
    int GetNdim() const { return Ndim; };
    double GetTime() const { return x[0]; };
    double GetX(int i) const { return x[i + 1]; };
    double *GetArray() const { return x; };

    //Operators
    void operator=(const ODEPoint &);
    double &operator[](int i);
    double operator[](int i) const;

    //Friend methods
    friend ostream &operator<<(ostream &, const ODEPoint &);

private:
    int Ndim;  //Number of dependent variables
    double *x; //independent variable + dependent variables (Ndim +1)
};
#endif // __ODEPOINT_H__