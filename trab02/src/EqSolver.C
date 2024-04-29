#include "EqSolver.h"

//#define DEBUGBUILD4

//Constructors
//Default constructor
EqSolver::EqSolver()
{
#ifdef DEBUGBUILD4
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
}

//Constructor 2 (Receives augmented matrix)
EqSolver::EqSolver(const FCmatrix &matrix)
{
#ifdef DEBUGBUILD4
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    ReducedMatrix = matrix;
    FCmatrixAlgorithm::GaussElimination(ReducedMatrix);
}

//Constructor 3 (Receives coefficient matrix and constants vector)
EqSolver::EqSolver(const FCmatrix &matrix, const Vec &vec)
{
#ifdef DEBUGBUILD4
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    ReducedMatrix = matrix;
    ReducedMatrix | vec;
    FCmatrixAlgorithm::GaussElimination(ReducedMatrix);
}

Vec EqSolver::GaussEliminationSolver()
{
#ifdef DEBUGBUILD4
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    const int xNo = ReducedMatrix.GetRowN();
    double x[xNo];
    double Sumx = 0;

    for (int i = xNo - 1; i >= 0; i--)
    {
        if (i == (xNo - 1))
        {
            x[i] = ReducedMatrix[i][xNo] / ReducedMatrix[i][i]; //Vconst[i]->Mcoeff[i][xNo]
        }
        else
        {
            Sumx = 0;

            for (int j = i + 1; j < xNo; j++)
            {
                Sumx += x[j] * ReducedMatrix[i][j];
            }

            x[i] = (ReducedMatrix[i][xNo] - Sumx) / ReducedMatrix[i][i]; //Vconst[i]->Mcoeff[i][xNo]
        }
    }
    return (Vec(xNo, x));
}