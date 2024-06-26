#ifndef __VANDERMONDE_H__
#define __VANDERMONDE_H__

#include "Vec.h"
#include "FCmatrix.h"
#include "FCmatrixFull.h"
#include "EqSolver.h"
#include "TF1.h"
#include "TGraph.h"
#include "TMath.h"
#include <cmath>

#include "TCanvas.h"
#include "TApplication.h"
#include "TStyle.h"
#include "TTimer.h"
#include "Getline.h"
#include "TFile.h"

class Vandermonde
{

public:
    // construtors, destructor
    Vandermonde();
    Vandermonde(unsigned, double, double, const TF1 &);
    ~Vandermonde();

    // getters
    const Vec &GetCoefficients();
    const FCmatrixFull &GetMatrix();
    const double *GetX();
    const double *GetY();

    double GetCoeffError();
    void GetInverseMatrix(FCmatrixFull &);

    // graphics getters
    TGraph &GetGraphPoints(); // return data points graph
    TF1 &GetPolyFunc();       // return polynomial function

    //Additional methods
    double PolyFunctionValue(double Argx);

private:
    //Additional methods
    double PolyFunction(double *Argx, double *Par)
    {
        return PolyFunctionValue(Argx[0]);
    }

    // setters
    void SetGraphicsPoints();     // set graphics with data points
    void SetPolynomialFunction(); // set polynomial TF1 function

    // data members
    FCmatrixFull MatrixCoefs; // coeff matrix (C)
    Vec PolCoefs;             // polynomial coeffs (a)

    TF1 *fPoly;     // polynomial function
    TGraph gPoints; // point's graphics

    int n; // number of points
    double *x;
    double *y;
};

#endif // __VANDERMONDE_H__