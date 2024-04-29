#include "ODESolver.h"

//Constructor
ODESolver::ODESolver(const vector<TF1> &vf) : F(vf) { ; }

//Destructor
ODESolver::~ODESolver()
{
    if (F.size() > 0)
        F.clear();
}

//Setter
void ODESolver::SetODEFunc(const vector<TF1> &vf)
{
    F = vf;
}

//Euler method
vector<ODEPoint> ODESolver::Euler(const ODEPoint &Point0, double h, double T)
{
    vector<ODEPoint> vP;  // Solution vector
    vP.push_back(Point0); // Adding initial point

    int Nh = int(T / h); // Number of steps

    ODEPoint Pnow(Point0);
    ODEPoint Pnext(Point0);

    for (int n = 0; n < Nh; n++)
    {
        Pnext[0] = Pnow[0] + h;

        for (int i = 0; i < Point0.GetNdim(); i++)
            Pnext[i + 1] = Pnow.GetX(i) + h * F[i].EvalPar(Pnow.GetArray());

        vP.push_back(Pnext); // Adding next point
        Pnow = Pnext;        // Updating current iteration
    }

    return vP;
}

//Predictor-Corrector method
vector<ODEPoint> ODESolver::PredictorCorrector(const ODEPoint &Point0, double h, double T)
{
    vector<ODEPoint> vP;  // Solution vector
    vP.push_back(Point0); // Adding initial point

    int Nh = int(T / h); // Number of steps

    ODEPoint Pnow(Point0);
    ODEPoint Pnext(Point0);
    ODEPoint Ptemp(Point0);

    for (int n = 0; n < Nh; n++)
    {
        Pnext[0] = Pnow[0] + h;
        Ptemp[0] = Pnow[0] + h;

        for (int i = 0; i < Point0.GetNdim(); i++)
        {
            Ptemp[i + 1] = Pnow.GetX(i) + h * F[i].EvalPar(Pnow.GetArray());
            Pnext[i + 1] = Pnow.GetX(i) + (h / 2.) * (F[i].EvalPar(Pnow.GetArray()) + F[i].EvalPar(Ptemp.GetArray()));
        }

        vP.push_back(Pnext); // Adding next point
        Pnow = Pnext;        // Updating current iteration
        Ptemp = Pnext;       // Updating temporary (end) point
    }

    return vP;
}

//Leap-Frog method
vector<ODEPoint> ODESolver::LeapFrog(const ODEPoint &Point0, double h, double T)
{
    vector<ODEPoint> vP;  // Solution vector
    vP.push_back(Point0); // Adding initial point

    int Nh = int(T / h); // Number of steps

    ODEPoint Pnow(Point0);
    ODEPoint Pnext(Point0);

    for (int n = 0; n < Nh; n++)
    {
        Pnext[0] += h;
        Pnext[1] = Pnow[1] + Pnow[2] * h + 0.5 * h * h * F[1].EvalPar(Pnow.GetArray());
        Pnext[2] = Pnow[2] + 0.5 * h * (F[1].EvalPar(Pnow.GetArray()) + F[1].EvalPar(Pnext.GetArray()));

        vP.push_back(Pnext); // Adding next point
        Pnow = Pnext;        // Updating current iteration
    }

    return vP;
}

//Second order Runge-Kutta method
vector<ODEPoint> ODESolver::RK2(const ODEPoint &Point0, double h, double T)
{
    vector<ODEPoint> vP;  // Solution vector
    vP.push_back(Point0); // Adding initial point

    int Nh = int(T / h); // Number of steps

    ODEPoint Pnow(Point0);
    ODEPoint P1(Point0);
    ODEPoint Pnext(Point0);

    vector<double> K1(Nh, 0); // h* 1st slope
    vector<double> K2(Nh, 0); // h* 2nd slope

    for (int n = 0; n < Nh; n++)
    {
        P1[0] = Pnow[0] + h / 2.;
        Pnext[0] = Pnow[0] + h;

        for (int i = 0; i < Point0.GetNdim(); i++)
        {
            K1[i] = h * F[i].EvalPar(Pnow.GetArray());
            P1[i + 1] = Pnow.GetX(i) + K1[i] / 2.;
        }

        for (int i = 0; i < Point0.GetNdim(); i++)
        {
            K2[i] = h * F[i].EvalPar(P1.GetArray());
            Pnext[i + 1] = Pnow.GetX(i) + K2[i];
        }

        vP.push_back(Pnext); // Adding next point
        Pnow = Pnext;        // Updating current iteration
    }

    // Clearing vectors
    K1.clear();
    K2.clear();

    return vP;
}

//Third order Runge-Kutta method
vector<ODEPoint> ODESolver::RK3(const ODEPoint &Point0, double h, double T)
{
    vector<ODEPoint> vP;  // Solution vector
    vP.push_back(Point0); // Adding initial point

    int Nh = int(T / h); // Number of steps

    ODEPoint Pnow(Point0);  // (t(i),y(i)) - Current iteration
    ODEPoint P1(Point0);    // (t(i+h/3),y(i+h/3))
    ODEPoint P2(Point0);    // (t(i+2*h/3),y(i+2*h/3))
    ODEPoint Pnext(Point0); // (t(i+h),y(i+h)) - Next iteration

    vector<double> K1(Nh, 0); // h* 1st slope (slope at t(i))
    vector<double> K2(Nh, 0); // h* 2nd slope (slope at t(i+h/3))
    vector<double> K3(Nh, 0); // h* 3rd slope (slope at t(i+2*h/3))

    for (int n = 0; n < Nh; n++)
    {
        P1[0] = Pnow[0] + h / 3;     // t(i+1/3) = t(i) + h/3
        P2[0] = Pnow[0] + 2 * h / 3; // t(i+2/3) = t(i) + 2*h/3
        Pnext[0] = Pnow[0] + h;      // t(i+1) = t(i) + h

        for (int i = 0; i < Point0.GetNdim(); i++)
        {
            K1[i] = h * F[i].EvalPar(Pnow.GetArray()); // K1 = h*f(t(i),y(i))
            P1[i + 1] = Pnow.GetX(i) + K1[i] / 3;      // y(i+h/3) = y(i) + K1/3
        }

        for (int i = 0; i < Point0.GetNdim(); i++)
        {
            K2[i] = h * F[i].EvalPar(P1.GetArray());  // K2 = h*f((t(i)+h/3,y(i)+K1/3))
            P2[i + 1] = Pnow.GetX(i) + 2 * K2[i] / 3; // y(i+2*h/3) = y(i) + 2*K2/3
        }

        for (int i = 0; i < Point0.GetNdim(); i++)
        {
            K3[i] = h * F[i].EvalPar(P2.GetArray());                       // K3 = h*f((t(i)+2*h/3,y(i)+2*K2/3))
            Pnext[i + 1] = Pnow.GetX(i) + (1. / 4.) * (K1[i] + 3 * K3[i]); // y(i+h) = y(i) + (1/4)*(K1+3*K3)
        }

        vP.push_back(Pnext); // Adding next point
        Pnow = Pnext;        // Updating current iteration
    }

    // Clearing vectors
    K1.clear();
    K2.clear();
    K3.clear();

    return vP;
}

//Fourth order Runge-Kutta method
vector<ODEPoint> ODESolver::RK4(const ODEPoint &Point0, double h, double T)
{
    vector<ODEPoint> vP;  // Solution vector
    vP.push_back(Point0); // Adding initial point

    int Nh = int(T / h); // Number of steps

    ODEPoint Pnow(Point0); // (t(i),y(i)) - Current iteration
    ODEPoint P1(Point0);
    ODEPoint P2(Point0);
    ODEPoint P3(Point0);
    ODEPoint Pnext(Point0); // (t(i+h),y(i+h)) - Next iteration

    vector<double> K1(Nh, 0); // h* 1st slope
    vector<double> K2(Nh, 0); // h* 2nd slope
    vector<double> K3(Nh, 0); // h* 3rd slope
    vector<double> K4(Nh, 0); // h* 4th slope

    for (int n = 0; n < Nh; n++)
    {
        P1[0] = Pnow[0] + h / 2.; // t(i+1/2) = t(i) + h/2
        P2[0] = Pnow[0] + h / 2.; // t(i+1/2) = t(i) + h/2
        P3[0] = Pnow[0] + h;      // t(i+1) = t(i) + h
        Pnext[0] = Pnow[0] + h;   // t(i+1) = t(i) + h

        for (int i = 0; i < Point0.GetNdim(); i++)
        {
            K1[i] = h * F[i].EvalPar(Pnow.GetArray());
            P1[i + 1] = Pnow.GetX(i) + K1[i] / 2.;
        }

        for (int i = 0; i < Point0.GetNdim(); i++)
        {
            K2[i] = h * F[i].EvalPar(P1.GetArray());
            P2[i + 1] = Pnow.GetX(i) + K2[i] / 2.;
        }

        for (int i = 0; i < Point0.GetNdim(); i++)
        {
            K3[i] = h * F[i].EvalPar(P2.GetArray());
            P3[i + 1] = Pnow.GetX(i) + K3[i];
        }

        for (int i = 0; i < Point0.GetNdim(); i++)
        {
            K4[i] = h * F[i].EvalPar(P3.GetArray());
            Pnext[i + 1] = Pnow.GetX(i) + (1. / 6.) * (K1[i] + 2 * K2[i] + 2 * K3[i] + K4[i]);
        }

        vP.push_back(Pnext); // Adding next point
        Pnow = Pnext;        // Updating current iteration
    }

    // Clearing vectors
    K1.clear();
    K2.clear();
    K3.clear();
    K4.clear();

    return vP;
}

//Shooting method boundary value problem solver (for 2nd order differential equations with boundary values in [x0,x1])
std::vector<ODEPoint> ODESolver::ShootingMethodBVPSolver1(const ODEPoint &Point, double x1, double x1Image, int x1DerivativeBool, int RK4IterationN)
{
    auto F = [&Point, &x1, &x1Image, &x1DerivativeBool, &RK4IterationN, this](double *u, double *par) {
        ODEPoint Point0(Point);
        if (x1DerivativeBool == 1)
            Point0[2] = u[0];
        if (x1DerivativeBool == 0)
            Point0[1] = u[0];

        double h = (x1 - Point[0]) / (double)RK4IterationN;
        std::vector<ODEPoint> RK4Points = RK4(Point0, h, h * RK4IterationN);

        if (x1DerivativeBool == 1)
            return (x1Image - RK4Points[RK4IterationN][2]);
        if (x1DerivativeBool == 0)
            return (x1Image - RK4Points[RK4IterationN][1]);

        return 0.;
    };

    TF1 *F_TF1 = new TF1("F_TF1", F, Point[0], x1, 0);

    double u = 0.;
    if (x1DerivativeBool == 1)
        u = Point[2];
    if (x1DerivativeBool == 0)
        u = Point[1];

    double uFinal = 0.;

    RootFinder FRootFinder(Point[0], x1, F_TF1);
    FRootFinder.QuasiN(1e-5, u, 100, 1e-5, uFinal);

    ODEPoint TruePoint0(Point);
    if (x1DerivativeBool == 1)
        TruePoint0[2] = uFinal;
    if (x1DerivativeBool == 0)
        TruePoint0[1] = uFinal;

    double h = (x1 - Point[0]) / (double)RK4IterationN;

    return RK4(TruePoint0, h, h * RK4IterationN);
}

//Shooting method boundary value problem solver (for 2nd order differential equations with boundary values in [x0,x1])
std::vector<ODEPoint> ODESolver::ShootingMethodBVPSolver2(const ODEPoint &Point, double x1, double x1Image, int x1DerivativeBool, int RK4IterationN)
{
    auto F = [&Point, &x1, &x1Image, &x1DerivativeBool, &RK4IterationN, this](double *u, double *par) {
        ODEPoint Point0(Point);
        if (x1DerivativeBool == 1)
            Point0[1] = u[0];
        if (x1DerivativeBool == 0)
            Point0[2] = u[0];

        double h = (x1 - Point[0]) / (double)RK4IterationN;
        std::vector<ODEPoint> RK4Points = RK4(Point0, h, h * RK4IterationN);

        if (x1DerivativeBool == 1)
            return (x1Image - RK4Points[RK4IterationN][2]);
        if (x1DerivativeBool == 0)
            return (x1Image - RK4Points[RK4IterationN][1]);

        return 0.;
    };

    TF1 *F_TF1 = new TF1("F_TF1", F, Point[0], x1, 0);

    double u = 0.;
    if (x1DerivativeBool == 1)
        u = Point[1];
    if (x1DerivativeBool == 0)
        u = Point[2];

    double uFinal = 0.;

    RootFinder FRootFinder(Point[0], x1, F_TF1);
    FRootFinder.QuasiN(1e-5, u, 100, 1e-5, uFinal);

    ODEPoint TruePoint0(Point);
    if (x1DerivativeBool == 1)
        TruePoint0[1] = uFinal;
    if (x1DerivativeBool == 0)
        TruePoint0[2] = uFinal;

    double h = (x1 - Point[0]) / (double)RK4IterationN;

    return RK4(TruePoint0, h, h * RK4IterationN);
}
