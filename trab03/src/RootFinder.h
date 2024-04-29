#ifndef ROOTFINDER_H
#define ROOTFINDER_H

#include <iostream>
#include <cmath>
#include <Func1D.h>

using namespace std;

//Classe na qual foi implementado o método Quasi-Newton
class RootFinder : public Func1D
{

public:
    RootFinder(double Argx0 = 0, double Argx1 = 0, TF1 *Argfunc = NULL) : x0(Argx0), x1(Argx1), Func1D(Argfunc) { ; }
    ~RootFinder() { ; }
    void SetBoundaries(double Argx0, double Argx1);
    double QuasiN(double &delta, double &Argx0, int n_max, double epslon);

protected:
    double x0;
    double x1;
};

#endif
