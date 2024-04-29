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
EqSolver::EqSolver(const FCMatrix &matrix)
{
#ifdef DEBUGBUILD4
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    ReducedMatrix = matrix;
    FCMatrixAlgorithm::GaussElimination(ReducedMatrix);
}

//Constructor 3 (Receives coefficient matrix and constants vector)
EqSolver::EqSolver(const FCMatrix &matrix, const Vec &vec)
{
#ifdef DEBUGBUILD4
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    ReducedMatrix = matrix;
    ReducedMatrix | vec;
    FCMatrixAlgorithm::GaussElimination(ReducedMatrix);
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

EqSolver::EqSolver(const FCMatrix &matrix, const Vec &vec, std::string method)
{
#ifdef DEBUGBUILD4
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (method == "LU")
    {
        M = matrix;
        b = vec;
    }
}

//Método dedicado à resolução de um sistema de equações após simplificação do mesmo através do método de decomposição LU de Doolittle
Vec EqSolver::LUDecompositionSolver_Doolittle()
{
    FCMatrixFull *LU = new FCMatrixFull[2];
    LU = FCMatrixAlgorithm::LUDecomposition_Doolittle(M); //Chamada do método 'simplificador' utilizando os membros do objeto EqSolver criado na main que chamou o método
    FCMatrixFull L(LU[0]);
    FCMatrixFull U(LU[1]);
    delete[] LU;

    /*std::cout << std::endl
              << "Matrizes L e U respetivamente:" << std::endl;
    std::cout << L << std::endl
              << U << std::endl;*/
    //Uncomment for testing...

    //Separação do sistema LUx=b e resolução do mesmo recorrendo a dois Vec's onde são armazenadas soluções temporárias
    Vec y(b.size(), 0.0);
    for (int i = 0; i < L.GetRowN(); i++)
    {
        y[i] = (b[i] - L[i].dot(y)) / 1.;
    }
    Vec x(b.size(), 0.0);

    for (int i = U.GetRowN() - 1; i >= 0; i--)
    {
        x[i] = (y[i] - U[i].dot(x)) / U[i][i];
    }
    return x;
}