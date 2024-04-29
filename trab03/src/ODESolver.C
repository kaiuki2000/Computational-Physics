#include "ODESolver.h"

//Solvers
//EulerSolver
std::vector<ODEPoint> ODESolver::EulerSolver(const ODEPoint &Point0, double h, int IterationsN)
{
    std::vector<ODEPoint> SolutionPoints;
    SolutionPoints.push_back(Point0);

    ODEPoint CurrentPoint(Point0);
    ODEPoint NextPoint(Point0);

    for (int i = 0; i < IterationsN; i++)
    {
        NextPoint[0] += h;

        for (int j = Formulas.size(); j > 0; j--)
            NextPoint[j] = CurrentPoint[j] + h * Formulas[j - 1].EvalPar(&(CurrentPoint.GetVector()[0]));

        SolutionPoints.push_back(NextPoint);
        CurrentPoint = NextPoint;
    }

    return SolutionPoints;
}

//PredictorCorrectorSolver
std::vector<ODEPoint> ODESolver::PredictorCorrectorSolver(const ODEPoint &Point0, double h, int IterationsN)
{
    std::vector<ODEPoint> SolutionPoints;
    SolutionPoints.push_back(Point0);

    ODEPoint CurrentPoint(Point0);
    ODEPoint NextPoint(Point0);
    ODEPoint TempPoint(Point0);

    for (int i = 0; i < IterationsN; i++)
    {
        TempPoint[0] += h;
        NextPoint[0] += h;

        for (int j = Formulas.size(); j > 0; j--)
        {
            TempPoint[j] = CurrentPoint[j] + h * Formulas[j - 1].EvalPar(&(CurrentPoint.GetVector()[0]));
            NextPoint[j] = CurrentPoint[j] + (h / 2) * (Formulas[j - 1].EvalPar(&(CurrentPoint.GetVector()[0])) + Formulas[j - 1].EvalPar(&(TempPoint.GetVector()[0])));
        }

        SolutionPoints.push_back(NextPoint);
        CurrentPoint = NextPoint;
        TempPoint = NextPoint;
    }

    return SolutionPoints;
}

//Leap-Frog method: used exclusively for 2nd order ODE's of the form d2x/dt2 = A(x)
std::vector<ODEPoint> ODESolver::LeapFrogSolver(const ODEPoint &Point0, double h, int IterationsN)
{
    std::vector<ODEPoint> SolutionPoints;
    SolutionPoints.push_back(Point0);

    ODEPoint CurrentPoint(Point0);
    ODEPoint NextPoint(Point0);

    double V_Half_plus = 0.;
    double V_Half_minus = 0.;

    for (int i = 0; i < IterationsN; i++)
    {
        NextPoint[0] += h;

        if (i == 0)
            V_Half_minus = Point0[2] - (h / 2) * Formulas[1].EvalPar(&(Point0.GetVector()[0]));
        else
            V_Half_minus = CurrentPoint[2] - (h / 2) * Formulas[1].EvalPar(&(CurrentPoint.GetVector()[0]));

        V_Half_plus = V_Half_minus + h * Formulas[1].EvalPar(&(CurrentPoint.GetVector()[0]));

        NextPoint[1] = CurrentPoint[1] + h * V_Half_plus;
        NextPoint[2] = CurrentPoint[2] + h * Formulas[1].EvalPar(&(CurrentPoint.GetVector()[0]));

        SolutionPoints.push_back(NextPoint);
        CurrentPoint = NextPoint;
    }

    //The following algorithm is also valid
    /*for (int i = 0; i < IterationsN; i++)
    {
        NextPoint[0] += h;
        NextPoint[1] = CurrentPoint[1] + CurrentPoint[2] * h + 0.5 * h * h * (Formulas[1].EvalPar(&(CurrentPoint.GetVector()[0])));
        NextPoint[2] = CurrentPoint[2] + 0.5 * h * (Formulas[1].EvalPar(&(CurrentPoint.GetVector()[0])) + Formulas[1].EvalPar(&(NextPoint.GetVector()[0])));

        SolutionPoints.push_back(NextPoint);
        CurrentPoint = NextPoint;
    }*/

    return SolutionPoints;
}

//4th order Runge-Kutta method
/*std::vector<ODEPoint> ODESolver::RK4Solver(const ODEPoint &Point0, double h, int IterationsN)
{
    std::vector<ODEPoint> SolutionPoints;
    SolutionPoints.push_back(Point0);

    ODEPoint CurrentPoint(Point0);
    ODEPoint NextPoint(Point0);

    std::vector<double> VecK1;
    std::vector<double> VecK2;
    std::vector<double> VecK3;
    std::vector<double> VecK4;

    ODEPoint K1;
    ODEPoint K1Temp;
    ODEPoint K2;
    ODEPoint K2Temp;
    ODEPoint K3;
    ODEPoint K3Temp;
    ODEPoint K4;

    int Dim = Formulas.size();

    for (int i = 0; i < IterationsN; i++)
    {
        NextPoint[0] += h;

        for (int j = 0; j < Dim; j++)
            VecK1.push_back(h * Formulas[j].EvalPar(&(CurrentPoint.GetVector()[0])));

        VecK1.insert(VecK1.begin(), h);
        K1.SetVector(VecK1);

        K1[0] -= h;

        K1Temp.SetVector(VecK1);
        K1Temp = K1Temp * 0.5;
        K1Temp = K1Temp + CurrentPoint;
        K1 = K1 * ((double)1 / (double)6);

        std::cout << i << ": K1= " << K1 << std::endl;

        for (int j = 0; j < Dim; j++)
            VecK2.push_back(h * Formulas[j].EvalPar(&(K1Temp.GetVector()[0])));

        VecK2.insert(VecK2.begin(), h);
        K2.SetVector(VecK2);
        K2[0] -= h;
        K2Temp.SetVector(VecK2);
        K2Temp = K2Temp * 0.5;
        K2Temp = K2Temp + CurrentPoint;
        K2 = K2 * ((double)2 / (double)6);

        std::cout << i << ": K2= " << K2 << std::endl;

        for (int j = 0; j < Dim; j++)
            VecK3.push_back(h * Formulas[j].EvalPar(&(K2Temp.GetVector()[0])));

        VecK3.insert(VecK3.begin(), h);
        K3.SetVector(VecK3);
        K3[0] -= h;
        K3Temp.SetVector(VecK3);
        K3Temp = K3Temp + CurrentPoint;
        K3 = K3 * ((double)2 / (double)6);

        std::cout << i << ": K3= " << K3 << std::endl;

        for (int j = 0; j < Dim; j++)
            VecK4.push_back(h * Formulas[j].EvalPar(&(CurrentPoint.GetVector()[0])));

        VecK4.insert(VecK3.begin(), 0);
        K4.SetVector(VecK4);
        K4 = K4 * ((double)1 / (double)6);

        std::cout << i << ": K4= " << K4 << std::endl;

        NextPoint = CurrentPoint + K1 + K2 + K3 + K4;
        NextPoint = NextPoint + K2;
        NextPoint = NextPoint + K3;
        NextPoint = NextPoint + K4;

        SolutionPoints.push_back(NextPoint);
        CurrentPoint = NextPoint;
        std::cout << std::endl;

        if (i != IterationsN - 1)
        {
            VecK1.clear();
            VecK2.clear();
            VecK3.clear();
            VecK4.clear();
        }
    }

    return SolutionPoints;
}*/

//4th order Runge-Kutta method
std::vector<ODEPoint> ODESolver::RK4Solver(const ODEPoint &Point0, double h, int IterationsN)
{
    std::vector<ODEPoint> SolutionPoints;
    SolutionPoints.push_back(Point0);

    ODEPoint CurrentPoint(Point0);
    ODEPoint NextPoint(Point0);

    std::vector<double> K1;
    std::vector<double> K2;
    std::vector<double> K3;
    std::vector<double> K4;

    std::vector<double> TempK1;
    std::vector<double> TempK2;
    std::vector<double> TempK3;

    int Dim = Formulas.size();

    for (int i = 0; i < IterationsN; i++)
    {
        NextPoint[0] += h;

        //K1 Calculations
        for (int j = 0; j < Dim; j++)
            K1.push_back(h * Formulas[j].EvalPar(&(CurrentPoint.GetVector()[0])));
        std::cout << "K1= " << K1[0] << std::endl;

        //Auxiliar point 1
        TempK1 = CurrentPoint.GetVector();
        TempK1[0] += 0.5 * h;
        for (int j = 0; j < Dim; j++)
            TempK1[j + 1] += 0.5 * K1[j];

        //K2 Calculations
        for (int j = 0; j < Dim; j++)
            K2.push_back(h * Formulas[j].EvalPar(&(TempK1[0])));
        std::cout << "K2= " << K2[0] << std::endl;

        //Auxiliar point 2
        TempK2 = CurrentPoint.GetVector();
        TempK2[0] += 0.5 * h;
        for (int j = 0; j < Dim; j++)
            TempK2[j + 1] += 0.5 * K2[j];

        //K3 Calculations
        for (int j = 0; j < Dim; j++)
            K3.push_back(h * Formulas[j].EvalPar(&(TempK2[0])));
        std::cout << "K3= " << K3[0] << std::endl;

        //Auxiliar point 3
        TempK3 = CurrentPoint.GetVector();
        TempK3[0] += h;
        for (int j = 0; j < Dim; j++)
            TempK3[j + 1] += K3[j];

        //K4 Calculations
        for (int j = 0; j < Dim; j++)
            K4.push_back(h * Formulas[j].EvalPar(&(TempK3[0])));
        std::cout << "K4= " << K4[0] << std::endl;

        //NextPoint Calculations
        for (int j = 0; j < Dim; j++)
            NextPoint[j + 1] += CurrentPoint[j + 1] + K1[j] / 6 + K2[j] / 3 + K3[j] / 3 + K4[j] / 6;

        SolutionPoints.push_back(NextPoint);
        CurrentPoint = NextPoint;

        K1.clear();
        K2.clear();
        K3.clear();
        K4.clear();

        TempK1.clear();
        TempK2.clear();
        TempK3.clear();
    }

    return SolutionPoints;
}