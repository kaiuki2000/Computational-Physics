#include "RootFinder.h"

//Método auxiliar da classe RootFinder
void RootFinder::SetBoundaries(double Argx0, double Argx1)
{
    x0 = Argx0;
    x1 = Argx1;
}

//Implementação do método Quasi-Newton
void RootFinder::QuasiN(double delta, double &Argx0,
                        int n_max, double epslon, double &x)
{
    //Introdução da iterada inicial no vetor x
    x = Argx0;

    double r1, r0 = Argx0;
    //Calculo das restantes iterações
    //O ciclo para se for atingido o número máximo de iterações, n_max
    for (int i = 0; i < n_max; i++)
    {
        if (i != 0)
            r0 = r1;
        r1 = r0 - Eval(r0) * (delta / ((Eval(r0 + delta)) - (Eval(r0))));
        x = r1;
        //O ciclo para se o erro for menor que o ε introduzido pelo utilizador
        if (fabs(r1 - r0) < fabs(epslon))
            return;
    }
}
