#ifndef __ODEsolver__
#define __ODEsolver__

#include "ODEpoint.h"
#include "TF1.h"

using namespace std;

class ODEsolver
{

public:
    ODEsolver(const vector<TF1> &); // constructor
    ~ODEsolver();                   // destructor

    void SetODEfunc(const vector<TF1> &);                         // setter
    vector<ODEpoint> RK3(const ODEpoint &P0, double h, double T); // Runge-Kutta de ordem 3

private:
    vector<TF1> F; // vetor de funcoes que dao as derivadas das variaveis dependentes
};

#endif