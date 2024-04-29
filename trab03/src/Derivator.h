#ifndef __DERIVATOR_H__
#define __DERIVATOR_H__

#include "Func1D.h"

class Derivator : public Func1D
{
public:
    //Constructors and destructor
    Derivator(double Argh = 1e-5, const TF1 *Argf = nullptr) : h(Argh), Func1D(Argf) { ; }
    Derivator(double Argh, const TF1 &Argf) : Derivator(Argh, &Argf) { ; }
    ~Derivator() = default;

    //Derivation methods
    //1st Derivative
    double ForwardDiff(double Argx) const;
    double BackwardDiff(double Argx) const;
    double CentralDiff(double Argx) const;

    //2nd Derivative: central difference methods
    double ThreePoint2nd(double Argx) const;
    double FivePoint2nd(double Argx) const;

    //3rd Derivative : central difference method
    double FourPoint3rd(double Argx) const;

    //4th Derivative (used in Simpson's integration rule) : central difference method
    double FivePoint4th(double Argx) const;

private:
    double h; //Derivation step
};
#endif // __DERIVATOR_H__