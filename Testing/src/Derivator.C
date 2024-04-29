#include "Derivator.h"

//Forward difference derivation method
double Derivator::ForwardDiff(double Argx) const
{
    double ForwardDiff = 0.;

    ForwardDiff = (-1 * f->Eval(Argx + 2 * h) + 4 * f->Eval(Argx + h) - 3 * f->Eval(Argx)) / (2 * h);
    return ForwardDiff;
}

//Backward difference derivation method
double Derivator::BackwardDiff(double Argx) const
{
    double BackwardDiff = 0.;
    BackwardDiff = (f->Eval(Argx - 2 * h) - 4 * f->Eval(Argx - h) + 3 * f->Eval(Argx)) / (2 * h);
    return BackwardDiff;
}

//Central difference derivation method
double Derivator::CentralDiff(double Argx) const
{
    double CentralDiff = 0.;
    CentralDiff = (1 / (12 * h)) * ((f->Eval(Argx - 2 * h) + 8 * f->Eval(Argx + h)) - (8 * f->Eval(Argx - h) + f->Eval(Argx + 2 * h)));
    return CentralDiff;
}

//Three point second derivative method
double Derivator::ThreePoint2nd(double Argx) const
{
    double ThreePoint2nd = 0.;
    ThreePoint2nd = (f->Eval(Argx + h) - 2 * f->Eval(Argx) + f->Eval(Argx - h)) / (h * h);
    return ThreePoint2nd;
}

//Five point second derivate method
double Derivator::FivePoint2nd(double Argx) const
{
    double FivePoint2nd = 0.;
    FivePoint2nd = (-1 * f->Eval(Argx - 2 * h) + 16 * f->Eval(Argx - h) - 30 * f->Eval(Argx) + 16 * f->Eval(Argx + h) - f->Eval(Argx + 2 * h)) / (12 * h * h);
    return FivePoint2nd;
}

//Four point third derivative method
double Derivator::FourPoint3rd(double Argx) const
{
    double FourPoint3rd = 0.;
    FourPoint3rd = (f->Eval(Argx + 3 * h) - 3 * f->Eval(Argx + h) + 3 * f->Eval(Argx - h) - f->Eval(Argx - 3 * h)) / (8 * h * h * h);
    return FourPoint3rd;
}

//Five point fourth derivative method
double Derivator::FivePoint4th(double Argx) const
{
    double FivePoint4th = 0.;
    FivePoint4th = (f->Eval(Argx + 4 * h) - 4 * f->Eval(Argx + 2 * h) + 6 * f->Eval(Argx) - 4 * f->Eval(Argx - 2 * h) + f->Eval(Argx - 4 * h)) / (16 * h * h * h * h);
    return FivePoint4th;
}
