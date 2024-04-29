#include "IntegratorMC.h"
#include "TMath.h"

using namespace std;

int main()
{
    TF1 *F = new TF1("F", "TMath::Exp(-x*x)", 0., 1.);

    IntegratorMC FIntegratorMC(0., 1., F);

    double result = 0.;
    double error = 0.;

    FIntegratorMC.UniformRandom(result, error, 100);

    cout << "O valor obtido para o integral, com nSamples= 100, é:\nIntegral= " << result << "\nErro= " << error << endl;

    return (0);
}

//Monte-Carlo Integration: "Importance-Sampling":
//1). First, we need to normalize the pdf:
//int_{x1}^{x2}k*pdf(x)dx=1 => k=... => pdf(x) -> k*pdf(x);
//2). Then, we need to determine x(y), with y in [0.,1.]:
//y = int_{x1}^{x}k*pdf(t)dt => x = f(y) (function of y);
//3). Then, we can call the "Importance-Sampling" integration algorithm, already implemented in the class 'IntegratorMC';
//<IntegratorMCObject>.ImportanceSampling(TF1 *Pdf, TF1 *Xy, double &Integral, double &Error, int Nsamples).

//This integration method is not used here, but it could have been.