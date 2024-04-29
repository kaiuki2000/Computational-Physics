#include "Integrator.h"

//Trapezoidal method for integration
void Integrator::Trapezoidal(int n, double &Integral, double &Error)
{
    //Defining 'h', slice size, and 'Sum' variable, to store integral values in each slice
    double h = (x1 - x0) / n;
    double Sum = 0.;
    Error = 0.;

    //Calculating 'Sum'
    for (int i = 0; i < n; i++)
    {
        Sum += (f->Eval(x0 + h * i) + f->Eval(x0 + h * (1 + i)));
    }

    //Calculating 'Integral'
    Integral = (h / 2) * Sum;

    //Calculating 'Error' using mean value theorem
    Derivator D(1e-5, f);
    double AuxError = 0.;
    AuxError = (D.CentralDiff(x0) + D.CentralDiff(x1));
    Error = fabs(-1 * pow(h, 2) / 12 * AuxError);
}

//Trapezoidal rule: adaptive scheme method
void Integrator::TrapezoidalAdaptive(double &Integral, double &Error)
{
    int k = 1;
    double tempError = 1e3;
    double fSum = 0.;

    //F1 Calculation
    double Fk = ((x1 - x0) / 2) * (f->Eval(x0) + f->Eval(x1));
    k++;

    //std::cout << Fk << std::endl;

    //Fk Calculation for k>1
    while (tempError > Error)
    {
        tempError = -Fk;
        fSum = 0.;

        for (int i = 1; i <= pow(2, k - 2); i++)
        {
            fSum += f->Eval(x0 + (2 * i - 1) * (x1 - x0) / (pow(2, k - 1)));
        }

        Fk = 0.5 * Fk + ((x1 - x0) / (pow(2, k - 1))) * fSum;
        k++;

        //std::cout << Fk << std::endl;

        tempError = fabs(tempError + Fk);
    }

    //New error
    Integral = Fk;
    Error = tempError;
}

//Simpson rule for integration
void Integrator::Simpson(int n, double &Integral, double &Error)
{
    //Even number of slices
    if (n % 2 == 0)
    {
        //Defining 'h', slice size, 'Sum1' variable and 'Sum2' variable to calculate the integral approximation
        double h = (x1 - x0) / n;
        double Sum1 = 0.;
        double Sum2 = 0.;
        Error = 0.;

        //Calculating 'Sum1'
        for (int i = 1; i <= n / 2; i++)
        {
            Sum1 += f->Eval(x0 + (2 * i - 1) * h);
        }

        //Calculating 'Sum2'
        for (int i = 1; i <= n / 2 - 1; i++)
        {
            Sum2 += f->Eval(x0 + (2 * i) * h);
        }

        //Calculating 'Integral'
        Integral = (h / 3) * (f->Eval(x0) + f->Eval(x1) + 4 * Sum1 + 2 * Sum2);
    }

    //Uneven number of slices
    if (n % 2 == 1)
    {
        double h = (x1 - x0) / n;
        double Sum = 0.;
        double LastPiece = 0.;
        Error = 0.;

        //Calculating 'Sum'
        for (int i = 1; i <= (n + 1) / 2 - 1; i++)
        {
            double j = x0 + (2 * i - 1) * h;
            Sum += (h / 3) * (f->Eval(j - h) + 4 * f->Eval(j) + f->Eval(j + h));
        }

        //Calculating 'LastPiece'
        LastPiece = (h / 12) * (-1 * f->Eval(x1 - 2 * h) + 8 * f->Eval(x1 - h) + 5 * f->Eval(x1));

        //Calculating 'Integral'
        Integral = Sum + LastPiece;
    }

    //Calculating 'Error' using mean value theorem
    Derivator D(1e-5, f);
    double AuxError = 0.;
    AuxError = (D.FourPoint3rd(x0) + D.FourPoint3rd(x1));
    Error = fabs(-1 * pow(((x1 - x0) / n), 4) / 180 * AuxError);
}

//Romberg method for integration
void Integrator::Romberg(int n, double &Integral, double &Error)
{
    Vec V;
    double VecValue = 0.;
    double PlaceholderError = 0.;

    //Calculation of M's first column (k=1)
    for (int j = 1; j <= n; j++)
    {
        Trapezoidal(pow(2, j - 1), VecValue, PlaceholderError);
        V.push_back(VecValue);
    }

    //Instantiating matrix M with V as its 1st column
    FCMatrixFull M(V, 'd');

    //Calculation of the other n-1 columns and their addition as a column in matrix M
    for (int k = 2; k <= n; k++)
    {
        V.clear();
        //Calculation of column k (k>1)
        for (int j = 1; j <= n; j++)
        {
            if (j < k)
                V.push_back(0);
            else
            {
                V.push_back(M[j - 1][k - 2] + (1 / (pow(4, k - 1) - 1)) * (M[j - 1][k - 2] - M[j - 2][k - 2]));
            }
        }
        //Adding V as a column in matrix M (k>1)
        M | V;
    }

    //Calculation of 'Integral' and 'Error'
    Integral = M[n - 1][n - 1];
    Error = fabs(M[n - 1][n - 1] - M[n - 1][n - 2]);
}
