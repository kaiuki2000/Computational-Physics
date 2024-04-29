#include "ODEsolver.h"

////////////////////////////////// constructor

ODEsolver::ODEsolver(const vector<TF1> &vf) : F(vf) { ; }

///////////////////////////////// destructor

ODEsolver::~ODEsolver()
{
    if (F.size() > 0)
        F.clear();
}

////////////////////////////////// setter

void ODEsolver::SetODEfunc(const vector<TF1> &vf)
{
    F = vf;
}

/////////////////////////////////// Runge-Kutta - ordem 3

vector<ODEpoint> ODEsolver::RK3(const ODEpoint &P0, double h, double T)
{
    vector<ODEpoint> vP; // vetor das solucoes
    vP.push_back(P0);    // adicionar o ponto inicial

    int Nh = int(T / h); // nb steps

    ODEpoint Pnow(P0);    // (t(i),y(i)) - iteracao atual
    ODEpoint Pmedio1(P0); // (t(i+h/3),y(i+h/3))
    ODEpoint Pmedio2(P0); // (t(i+2*h/3),y(i+2*h/3))
    ODEpoint Pnext(P0);   // (t(i+h),y(i+h)) - iteracao seguinte

    vector<double> K1(Nh, 0); // h* 1st slope (slope at t(i))
    vector<double> K2(Nh, 0); // h* 2nd slope (slope at t(i+h/3))
    vector<double> K3(Nh, 0); // h* 3rd slope (slope at t(i+2*h/3))

    for (int n = 0; n < Nh; n++)
    {
        Pmedio1[0] = Pnow[0] + h / 3;     // t(i+1/3) = t(i) + h/3
        Pmedio2[0] = Pnow[0] + 2 * h / 3; // t(i+2/3) = t(i) + 2*h/3
        Pnext[0] = Pnow[0] + h;           // t(i+1) = t(i) + h

        for (int i = 0; i < P0.Ndim(); i++)
        {
            K1[i] = h * F[i].EvalPar(Pnow.GetArray()); // K1 = h*f(t(i),y(i))
            Pmedio1[i + 1] = Pnow.X(i) + K1[i] / 3;    // y(i+h/3) = y(i) + K1/3
        }

        for (int i = 0; i < P0.Ndim(); i++)
        {
            K2[i] = h * F[i].EvalPar(Pmedio1.GetArray()); // K2 = h*f((t(i)+h/3,y(i)+K1/3))
            Pmedio2[i + 1] = Pnow.X(i) + 2 * K2[i] / 3;   // y(i+2*h/3) = y(i) + 2*K2/3
        }

        for (int i = 0; i < P0.Ndim(); i++)
        {
            K3[i] = h * F[i].EvalPar(Pmedio2.GetArray());               // K3 = h*f((t(i)+2*h/3,y(i)+2*K2/3))
            Pnext[i + 1] = Pnow.X(i) + (1. / 4.) * (K1[i] + 3 * K3[i]); // y(i+h) = y(i) + (1/4)*(K1+3*K3)
        }

        vP.push_back(Pnext); // adicionar ponto seguinte
        Pnow = Pnext;        // iteracao seguinte passa a ser a atual
    }

    // clear vectors
    K1.clear();
    K2.clear();
    K3.clear();

    return vP;
}