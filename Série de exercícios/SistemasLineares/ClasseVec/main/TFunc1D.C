#include "Func1D.h"
#include "Integrator.h"
#include "IntegratorMC.h"
#include <iomanip>

int main()
{

    //Instantiate object Func1D
    auto f = [](double *x, double *par = nullptr) {
        return sin(x[0]) / x[0] + 0.5 * cos(0.5 * x[0]);
    };

    Func1D F1(new TF1("F1", f, 0.1, 10., 0));
    Func1D F2(TF1("F2", f, 0.1, 10., 0));

    //Output
    /*for (double a = 0.1; a < 1; a += 0.1)
    {
        std::cout << a << " " << f(&a) << " " << F1.Eval(a) << " " << F2.Eval(a) << std::endl;
    }*/

    //Drawing
    //F2.Draw();

    Integrator I_F1(0.1, 10., TF1("F3", f, 0.1, 10., 0));

    double Integral = 0.;
    double Error = 0.;
    I_F1.Trapezoidal(1000, Integral, Error);

    std::cout << "Function1: Trapezoidal rule- 1000 slices" << std::endl;

    std::cout << std::setprecision(16) << "Integral value: " << Integral << std::endl
              << "Error value: " << Error << std::endl;
    std::cout << std::endl;

    auto f2 = [](double *x, double *par) {
        return cos(x[0]);
    };

    //Trapezoidal
    Integrator I_F2(0., TMath::PiOver2(), TF1("F4", f2, 0., TMath::PiOver2()));
    I_F2.Trapezoidal(1000, Integral, Error);

    std::cout << "Function2: Trapezoidal rule- 1000 slices" << std::endl;

    std::cout << std::setprecision(16) << "Integral value: " << Integral << std::endl
              << "Error value: " << Error << std::endl;
    std::cout << std::endl;

    //Adaptive trapezoidal
    Error = 1e-10;
    I_F2.TrapezoidalAdaptive(Integral, Error);

    std::cout << "Function2: Adaptive trapezoidal rule- Error < 1e-10" << std::endl;

    std::cout << std::setprecision(16) << "Integral value: " << Integral << std::endl
              << "Error value: " << Error << std::endl;
    std::cout << std::endl;

    //Simpson rule: Even number of slices
    I_F2.Simpson(1000, Integral, Error);

    std::cout << "Function2: Simpson rule- 1000 slices" << std::endl;

    std::cout << std::setprecision(16) << "Integral value: " << Integral << std::endl
              << "Error value: " << Error << std::endl;
    std::cout << std::endl;

    //Simpson rule: Uneven number of slices
    I_F2.Simpson(1001, Integral, Error);

    std::cout << "Function2: Simpson rule- 1001 slices" << std::endl;

    std::cout << std::setprecision(16) << "Integral value: " << Integral << std::endl
              << "Error value: " << Error << std::endl;
    std::cout << std::endl;

    //Romberg rule
    I_F2.Romberg(5, Integral, Error);

    std::cout << "Function2: Romberg rule- n=5" << std::endl;

    std::cout << std::setprecision(16) << "Integral value: " << Integral << std::endl
              << "Error value: " << Error << std::endl;
    std::cout << std::endl;

    //IntegratorMC testing
    IntegratorMC MC_F2(0., TMath::PiOver2(), TF1("F5", f2, 0., TMath::PiOver2()));

    //UniformRandom
    MC_F2.UniformRandom(Integral, Error, 1e6);

    std::cout << "Function2: 'Standard' Monte-Carlo integration (UniformRandom)- Nsamples=1e6" << std::endl;

    std::cout << std::setprecision(16) << "Integral value: " << Integral << std::endl
              << "Error value: " << Error << std::endl;
    std::cout << std::endl;

    //AcceptanceRejection
    auto f3 = [](double *x, double *par) {
        return 3 * x[0] * x[0];
    };

    IntegratorMC MC_F3(3., 7., TF1("F6", f3, 3., 7.));

    //UniformRandom
    MC_F3.UniformRandom(Integral, Error, 1e6);

    std::cout << "Function3: 'Standard' Monte-Carlo integration (UniformRandom)- Nsamples=1e6" << std::endl;

    std::cout << std::setprecision(16) << "Integral value: " << Integral << std::endl
              << "Error value: " << Error << std::endl;
    std::cout << std::endl;

    //AcceptanceRejection
    MC_F3.AcceptanceRejection(Integral, Error, 1e6);

    std::cout << std::endl;
    std::cout << "Function3: 'Acceptance-Rejection' Monte-Carlo integration (AcceptanceRejection)- Nsamples=1e6" << std::endl;

    std::cout << std::setprecision(16) << "Integral value: " << Integral << std::endl
              << "Error value: " << Error << std::endl;

    return (0);
}