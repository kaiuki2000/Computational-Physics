#include "Vandermonde.h"

//#define DEBUGBUILD4 //Uncomment for debugging

//Constructors and destructors
//Default constructor
Vandermonde::Vandermonde() : n(0), x(nullptr), y(nullptr), fPoly(nullptr) //Initializes data members
{
#ifdef DEBUGBUILD4
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
}

//Constructor 2
Vandermonde::Vandermonde(unsigned Argn, double ArgXmin, double ArgXmax, const TF1 &Argf) : n(Argn), fPoly(nullptr)
{
#ifdef DEBUGBUILD4
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (n > 0) //In case the number of elements is >0
    {
        if (ArgXmax > ArgXmin)
        {
            //Creating arrays
            x = new double[n];
            y = new double[n];

            for (int i = 0; i < n; i++)
            {
                //Calculating x and y values
                x[i] = ArgXmin + i * (ArgXmax - ArgXmin) / (n - 1);
                y[i] = Argf.Eval(x[i]);

                //Printing values of x and y
                //std::cout << "(" << x[i] << "," << y[i] << ")" << std::endl;
            }

            //Defining MatrixCoefs
            Vec line;
            for (int i = 0; i < n; i++)
            {
                line.clear();
                for (int j = 0; j < n; j++)
                {
                    line.push_back(pow(x[i], j));
                }
                MatrixCoefs.AddLine(line);
            }

            //Printing MatrixCoefs
            //std::cout << std::endl
            //<< MatrixCoefs << std::endl;

            //Initializing gPoints
            SetGraphicsPoints();

            //Calculating PolCoefs
            EqSolver EqSolver1(MatrixCoefs, Vec(n, y));
            PolCoefs = EqSolver1.GaussEliminationSolver();
            //std::cout << "Coefficient vector: " << PolCoefs << std::endl;

            //Defining fPoly
            SetPolynomialFunction();
        }
        else
        {
            if (ArgXmax < ArgXmin)
            {
                //Creating arrays
                x = new double[n];
                y = new double[n];

                for (int i = 0; i < n; i++)
                {
                    //Calculating x and y values
                    x[i] = ArgXmax + i * (ArgXmin - ArgXmax) / (n - 1);
                    y[i] = Argf.Eval(x[i]);

                    //Printing values of x and y
                    //std::cout << "(" << x[i] << "," << y[i] << ")" << std::endl;
                }

                //Defining MatrixCoefs
                Vec line;
                for (int i = 0; i < n; i++)
                {
                    line.clear();
                    for (int j = 0; j < n; j++)
                    {
                        line.push_back(pow(x[i], j));
                    }
                    MatrixCoefs.AddLine(line);
                }

                //Printing MatrixCoefs
                //std::cout << std::endl
                //<< MatrixCoefs << std::endl;

                //Initializing gPoints
                SetGraphicsPoints();

                //Calculating PolCoefs
                EqSolver EqSolver1(MatrixCoefs, Vec(n, y));
                PolCoefs = EqSolver1.GaussEliminationSolver();
                //std::cout << "Coefficient vector: " << PolCoefs << std::endl;

                //Defining fPoly
                SetPolynomialFunction();
            }
            else //In case (ArgXmin == ArgXmax): Error!
            {
                throw std::invalid_argument(Form("[%s] ArgXmin cannot be equal to ArgXmax...!\n", __PRETTY_FUNCTION__));
            }
        }
    }
    else
    {
        if (n == 0) //In case the number of elements is =0
        {
            x = nullptr;
            y = nullptr;
        }
        else //In case the number of elements is <0
        {
            throw std::invalid_argument(Form("[%s] Number of elements can't be negative...!\n", __PRETTY_FUNCTION__));
        }
    }
}

//Destructor
Vandermonde::~Vandermonde()
{
#ifdef DEBUGBUILD4
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    //Checks if the pointer exists. If it does, deletes it.
    if (x)
        delete[] x;
    if (y)
        delete[] y;
    if (fPoly)
        delete fPoly;
}

//GetCoefficients method
const Vec &Vandermonde::GetCoefficients()
{
    return PolCoefs;
}

//GetMatrix method
const FCmatrixFull &Vandermonde::GetMatrix()
{
    return MatrixCoefs;
}

//GetX method
const double *Vandermonde::GetX()
{
    return x;
}

//GetY method
const double *Vandermonde::GetY()
{
    return y;
}

//GetGraphPoints method
TGraph &Vandermonde::GetGraphPoints()
{
    return gPoints;
}

//PolyFunctionValue method
double Vandermonde::PolyFunctionValue(double Argx)
{
    double result = 0.;
    //Calculating the PolynomialFunctionValue at x=Argx.
    for (int i = 0; i < n; i++)
    {
        result += PolCoefs[i] * pow(Argx, i);
    }
    return result;
}

//GetPolyFunc method
TF1 &Vandermonde::GetPolyFunc()
{
    return *fPoly;
}

//Private methods
//SetGraphicsPoints method
void Vandermonde::SetGraphicsPoints()
{
    //Initializing gPoints
    gPoints = TGraph(n, x, y);
    gPoints.SetMarkerStyle(20);
    gPoints.SetMarkerColor(38);
    gPoints.SetMarkerSize(2);
    gPoints.SetTitle("gPoints");
    gPoints.SetName("gPoints");
}

//SetPolynomialFunction method
void Vandermonde::SetPolynomialFunction()
{
    //Initializing fPoly
    fPoly = new TF1("fPoly", this, &Vandermonde::PolyFunction, x[0] - 0.001, x[n - 1] + 0.001, 0);
    fPoly->SetLineColor(kRed + 2);
    fPoly->SetLineWidth(2);
    fPoly->SetTitle("fPoly");
}

//GetCoefError method
double Vandermonde::GetCoeffError()
{
    //Calculating vector D = C * a - b.
    //D = MatrixCoefs * PolCoefs - b.
    Vec b(n, y);
    Vec D = MatrixCoefs * PolCoefs;
    D -= b;

    //Return max{|D[i]|}
    return D.maxAbs();
}

//GetInverseMatrix method
void Vandermonde::GetInverseMatrix(FCmatrixFull &inv)
{
    //Alters FCmatrixFull &inv to be equal to the inverse matrix of MatrixCoefs
    inv = MatrixCoefs.inv(MatrixCoefs, n);
}
