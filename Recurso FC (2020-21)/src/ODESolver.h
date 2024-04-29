#ifndef __ODESOLVER_H__
#define __ODESOLVER_H__

#include "ODEPoint.h"
#include "RootFinder.h"

class ODESolver
{
public:
    //Constructor and destructor
    ODESolver(const vector<TF1> &);
    ~ODESolver();

    //'Setter'
    void SetODEFunc(const vector<TF1> &);

    //Solvers
    vector<ODEPoint> Euler(const ODEPoint &Point0, double h, double T);              //Euler method
    vector<ODEPoint> PredictorCorrector(const ODEPoint &Point0, double h, double T); //Predictor-Corrector method
    vector<ODEPoint> LeapFrog(const ODEPoint &Point0, double h, double T);           //Leap-Frog method

    vector<ODEPoint> RK2(const ODEPoint &Point0, double h, double T); //2nd order Runge-Kutta method
    vector<ODEPoint> RK3(const ODEPoint &Point0, double h, double T); //3rd order Runge-Kutta method
    vector<ODEPoint> RK4(const ODEPoint &Point0, double h, double T); //4th order Runge-Kutta method

    //Shooting method boundary value problem solver (for 2nd order differential equations with boundary values in [x0,x1]): (Boundary conditions)
    //1: considers "T(x0) = a and T'(x1) = b", or "T'(x0) = a and T(x1) = b". (Derivative + normal) or (Normal + derivative)
    //2: considers "T(x0) = a and T(x1) = b", or "T'(x0) = a and T'(x1) = b". (Normal + normal) or (Derivative + derivative)
    std::vector<ODEPoint> ShootingMethodBVPSolver1(const ODEPoint &Point, double x1, double x1Image, int x1DerivativeBool, int RK4IterationN);
    std::vector<ODEPoint> ShootingMethodBVPSolver2(const ODEPoint &Point, double x1, double x1Image, int x1DerivativeBool, int RK4IterationN);

private:
    vector<TF1> F; //Vector containing all the funcitons to be used
};

#endif // __ODESOLVER_H__