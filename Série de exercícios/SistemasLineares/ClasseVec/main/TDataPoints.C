#include "DataPoints.h"
#include "LagrangeInterpolator.h"
#include "NewtonInterpolator.h"
#include "NevilleInterpolator.h"

int main()
{
    auto fTeste = new TF1("fTeste", "exp(x*sin(x))", 0 - 0.001, 5 + 0.001); //Underlying function: "exp(x*sin(x))", "exp(x*x)"
    int n = 6;
    double x[n] = {0, 1, 2, 3, 4, 5};
    double y[n] = {fTeste->Eval(0), fTeste->Eval(1), fTeste->Eval(2), fTeste->Eval(3), fTeste->Eval(4), fTeste->Eval(5)};

    DataPoints Data1(n, x, y);
    Data1.Print("Teste");
    //Data1.Draw(); Cannot have more than one instance of TApplication at a time...

    //Testing LagrangeInterpolator...
    LagrangeInterpolator LI_Data1(n, x, y);
    LI_Data1.SetFunction(fTeste);
    LI_Data1.Draw();

    /*
    TString tstr = LI_Data1.GetInterpolationFunctionExpression();
    const char *c = tstr.Data();
    std::cout << "InterpolationFunction's expression: P(x) = " << c << std::endl;
    std::cout << "InterpolationFunction's expression: P(x) = " << tstr.Sizeof() << std::endl;
    */
    //Doesn't work...

    //Testing NewtonInterpolator...
    NewtonInterpolator NI_Data1(n, x, y);
    NI_Data1.SetFunction(fTeste);
    NI_Data1.Draw();

    //Testing NevilleInterpolator...
    NevilleInterpolator NLI_Data1(n, x, y);
    NLI_Data1.SetFunction(fTeste);
    NLI_Data1.Draw();

    return (0);
}