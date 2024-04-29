#ifndef __LAGRANGEINTERPOLATOR_H__
#define __LAGRANGEINTERPOLATOR_H__

#include "DataPoints.h"
#include "TF1.h"

class LagrangeInterpolator : public DataPoints
{
public:
    LagrangeInterpolator(int ArgN = 0, double *Argx = nullptr, double *Argy = nullptr, TF1 *ArgF0 = nullptr);
    ~LagrangeInterpolator();
    double Interpolate(double Argx);
    void Draw(); //Draws everything (points and interpolation function)
    TF1 *GetInterpolationFunction();
    void SetFunction(TF1 *);

    //void Print(string filename=""); //Prints results to file (not yet implemented)
    //TString GetInterpolationFunctionExpression(); //Returns InterpolationFunction's explicit expression. Doesn't work...

private:
    double fInterpolator(double *fx, double *par)
    {
        return Interpolate(fx[0]);
    }
    TF1 *FInterpolator; //Interpolation function
    TF1 *F0;            //Eventual underlying function
};

#endif // __LAGRANGEINTERPOLATOR_H__