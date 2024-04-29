#include "IntegratorMC.h"

#include <vector>

using namespace std;

int main()
{
    vector<double> Vecx0{0., 0.};
    vector<double> Vecx1{1., 1.};

    //This first formula doesn't work?
    //TFormula *Formula = new TFormula("Formula", "(x[0]*x[0]-x[1]*x[1])/((x[0]*x[0]+x[1]*x[1])*(x[0]*x[0]+x[1]*x[1]))");
    TFormula *Formula = new TFormula("Formula", "1-x**2-y**2");

    IntegratorMC FormulaIntegratorMC(Formula, 2, Vecx0, Vecx1);

    double Integral = 0.;
    double Error = 0.;

    FormulaIntegratorMC.UniformRandom(Integral, Error, 100);

    cout << "Standard Monte-Carlo:\n\nnSamples=100:\nIntegral= " << Integral << "\nError= " << Error << endl;

    FormulaIntegratorMC.UniformRandom(Integral, Error, 1000);

    cout << "\nSamples=1000:\nIntegral= " << Integral << "\nError= " << Error << endl;

    delete Formula;

    return 0;
}