#ifndef __INTEGRATOR_H__
#define __INTEGRATOR_H__

#include "Func1D.h"
#include "Derivator.h"
#include "FCMatrix.h"
#include "FCMatrixFull.h"

class Integrator : public Func1D
{
public:
    //Constructors and destructor
    Integrator(double Argx0 = 0., double Argx1 = 1., const TF1 *Argf = nullptr) : x0(Argx0), x1(Argx1), Func1D(Argf) { ; }
    Integrator(double Argx0, double Argx1, const TF1 &Argf) : Integrator(Argx0, Argx1, &Argf) { ; }
    virtual ~Integrator() = default;

    //Integrator methods
    /*
    n ............. Number of slices (input);
    Integral ...... Integral value by reference (input/output);
    Error ......... Error value by reference (input/output).
   */

    void Trapezoidal(int n, double &Integral, double &Error);
    void TrapezoidalAdaptive(double &Integral, double &Error); //Doubles the amount of slices to improve precision
    void Simpson(int n, double &Integral, double &Error);
    void Romberg(int n, double &Integral, double &Error); //An n*n matrix will be created to estimate de integral

protected:
    double x0;
    double x1;
};

#endif // __INTEGRATOR_H__