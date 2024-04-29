#ifndef __ODESOLVER_H__
#define __ODESOLVER_H__

#include "ODEPoint.h"
#include "RootFinder.h"
#include "TFormula.h"

class ODESolver
{
public:
    ODESolver() { ; }                                                                //Default constructor
    ODESolver(const std::vector<TFormula> &ArgFormulas) { Formulas = ArgFormulas; }; //Constructor receiving std::vector<TFormula>
    ~ODESolver() { Formulas.clear(); };                                              //Destructor

    //'Setters'
    void SetFormulas(const std::vector<TFormula> &ArgFormulas) { Formulas = ArgFormulas; };

    //'Getters'
    TFormula &GetFormula(int i) { return Formulas[i]; };

    //Solvers
    std::vector<ODEPoint> EulerSolver(const ODEPoint &Point0, double h, int IterationsN);              //Euler method
    std::vector<ODEPoint> PredictorCorrectorSolver(const ODEPoint &Point0, double h, int IterationsN); //Predictor-Corrector method
    std::vector<ODEPoint> LeapFrogSolver(const ODEPoint &Point0, double h, int IterationsN);           //Leap-Frog method: used exclusively for 2nd order ODE's of the form d2x/dt2 = A(x)
    std::vector<ODEPoint> RK2Solver(const ODEPoint &Point0, double h, int IterationsN);                //2nd order Runge-Kutta method
    std::vector<ODEPoint> RK4Solver(const ODEPoint &Point0, double h, int IterationsN);                //4th order Runge-Kutta method

    //Shooting method boundary value problem solver (for 2nd order differential equations with boundary values in [x0,x1]): (Boundary conditions)
    //1: considers "T(x0) = a and T'(x1) = b", or "T'(x0) = a and T(x1) = b". (Derivative + normal) or (Normal + derivative)
    //2: considers "T(x0) = a and T(x1) = b", or "T'(x0) = a and T'(x1) = b". (Normal + normal) or (Derivative + derivative)
    std::vector<ODEPoint> ShootingMethodBVPSolver1(const ODEPoint &Point, double x1, double x1Image, int x1DerivativeBool, int RK4IterationN);
    std::vector<ODEPoint> ShootingMethodBVPSolver2(const ODEPoint &Point, double x1, double x1Image, int x1DerivativeBool, int RK4IterationN);

private:
    std::vector<TFormula> Formulas; //Vector containing all the functions to be used
};

#endif // __ODESOLVER_H__