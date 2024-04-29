#ifndef __ODEpoint__
#define __ODEpoint__

#include <vector>
#include <iostream>

using namespace std;

class ODEpoint
{

public:
    // constructors and destructor
    ODEpoint(int fndim = 0, const double *x = nullptr);
    ODEpoint(const ODEpoint &); // copy constructor
    ~ODEpoint();

    // getters
    int Ndim() const { return ndim; }          // get nb of dependent variables
    double T() const { return x[0]; }          // get time
    double X(int i) const { return x[i + 1]; } // get dependent variable with index i (i+1 on array x)
    double *GetArray() { return x; }           // get array of all variables

    // operators
    void operator=(const ODEpoint &); // *this = P
    double &operator[](int);          // *this[i] = x[i]

    // print
    friend ostream &operator<<(ostream &, const ODEpoint &);

private:
    int ndim;  // nb of dependent variables
    double *x; // independent variable + dependent variables (ndim+1)
};

#endif