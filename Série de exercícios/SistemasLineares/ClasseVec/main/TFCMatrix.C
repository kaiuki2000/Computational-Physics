#include "FCMatrix.h"
#include "FCMatrixAlgorithm.h"
#include "EqSolver.h"
#include "FCTools.h"

int main()
{
    FCMatrixFull A; //Default constructor

    int m = 3;
    int n = 3;
    double **M1 = new double *[m];
    M1[0] = new double[n]{0, -2, 3};
    M1[1] = new double[n]{-4, 5, 16};
    M1[2] = new double[n]{0, -7, 6};
    FCMatrixFull B(M1, m, n); //Constructor 2

    double *vec1 = new double[5]{1, 2, 3, 4, 5};
    FCMatrixFull C(vec1, 5, 1); //Constructor 3 (Vetor coluna)

    FCMatrixFull D(C);

    std::cout << A << std::endl;
    std::cout << B << std::endl;
    std::cout << C << std::endl;
    std::cout << D << std::endl;
    std::cout << "1st line of matrix B: " << B[0] << std::endl;
    std::cout << "2nd line of matrix B: " << B[1] << std::endl;
    std::cout << "3rd line of matrix B: " << B[2] << std::endl;
    std::cout << "B[1][2]= " << B[1][2] << std::endl;
    std::cout << std::endl;
    std::cout << "Swapping lines 1 and 3 of matrix B: " << std::endl;
    B.SwapLines(0, 2);
    std::cout << B << std::endl;

    std::cout << A << std::endl;
    A = B; //operator=
    std::cout << "Matrix A: " << std::endl;
    std::cout << A << std::endl;

    //FCMatrixAlgorithm: GaussElimination test...
    std::cout << "Gauss elimination of matrix A: " << std::endl;
    FCMatrixAlgorithm::GaussElimination(A);
    std::cout << A << std::endl;

    //Constructor 5
    double *vals = new double[3]{16, 0, -1};
    Vec v1(3, vals);
    std::cout << "Accessing v1 elements: " << v1 << std::endl;
    FCMatrixFull E(v1);
    std::cout << E << std::endl;

    //EqSolver: back substitution test...
    double **M2 = new double *[m];
    M2[0] = new double[n]{0, -2, 6}; // {2, -2, 6}
    M2[1] = new double[n]{0, 4, 3};  // {-2, 4, 3}
    M2[2] = new double[n]{-1, 0, 4}; // {-1, 8, 4}
    FCMatrixFull F(M2, m, n);        //Constructor 2
    std::cout << F << std::endl;
    std::cout << E << std::endl;

    /*F | v1;
    std::cout << F << std::endl;
    FCMatrixAlgorithm::GaussElimination(F);
    std::cout << F << std::endl;*/

    /*EqSolver Fsolver(F.GetMCoeff, F.GetVconst);
    std::cout << Fsolver.GaussEliminationSolver() << std::endl;*/

    EqSolver Fsolver1(F, v1);
    std::cout << "Solution: " << Fsolver1.GaussEliminationSolver() << std::endl;

    std::cout << std::endl;
    std::cout << "Augmented matrix F | v1:" << std::endl;
    std::cout << (F || v1) << std::endl; //operator|| -> Doesn't alter obj. matrix (Augmented matrix) -> returns an FCMatrix
    EqSolver Fsolver2(F || v1);          //operator|| -> Doesn't alter obj. matrix (Augmented matrix) -> returns an FCMatrix
    std::cout << "Solution: " << Fsolver2.GaussEliminationSolver() << std::endl;

    //Maybe fazer com que o operador | cria uma nova matriz, ou seja, não altere a matriz F...! -> operator|| -> retorna uma FCMatrix

    //Determinant method...
    std::cout << "\nMatrix F:\n"
              << F << std::endl;
    std::cout << "Det(F) = |F| = " << F.Determinant() << std::endl;

    //Testing FCTools...
    std::vector<std::string> StrMatrix;
    StrMatrix = FCTools::ReadFile2String("matrix.txt");

    std::cout << std::endl;
    for (int i = 0; i < StrMatrix.size(); i++)
    {
        std::cout << StrMatrix[i] << std::endl;
    }

    std::vector<Vec> VecMatrix;
    VecMatrix = FCTools::ReadFile2Vec("matrix.txt");

    std::cout << std::endl;
    for (int i = 0; i < VecMatrix.size(); i++)
    {
        std::cout << VecMatrix[i] << std::endl;
    }

    int ll = 5;
    Vec *VecMatrix2 = FCTools::ReadFile2Vecp("matrix.txt", ll);

    std::cout << std::endl;
    for (int i = 0; i < ll; i++)
    {
        std::cout << VecMatrix2[i] << std::endl;
    }
    delete[] VecMatrix2;

    std::cout << std::endl;
    FCMatrixFull ActualVecMatrix(VecMatrix);
    std::cout << ActualVecMatrix << std::endl;
    std::cout << "Det(ActualVecMatrix) = |ActualVecMatrix| = " << ActualVecMatrix.Determinant() << std::endl; //Testing if the matrix is functional...

    ActualVecMatrix.SwapLines(1, 2);
    std::cout << "Det(ActualVecMatrix) = |ActualVecMatrix| = " << ActualVecMatrix.Determinant() << std::endl;

    std::cout << std::endl;
    double **M3 = new double *[m];
    M3[0] = new double[n]{0, 1, 1}; // {0, 1, 1}
    M3[1] = new double[n]{2, 1, 1}; // {2, 1, 1}
    M3[2] = new double[n]{1, 2, 4}; // {1, 2, 4}

    FCMatrixFull G(M3, m, m);
    std::cout << "Matrix G:\n"
              << G << std::endl;
    std::cout << "Det(G) = |G| = " << G.Determinant() << std::endl;

    std::cout << std::endl;
    std::cout << F << std::endl;
    std::cout << "Vector: " << v1 << std::endl;
    std::cout << "Solution: " << Fsolver1.GaussEliminationSolver() << std::endl;
    std::cout << std::endl;

    EqSolver Fsolver3(F, v1, "LU");
    std::cout << F << std::endl;
    std::cout << "Vector: " << v1 << std::endl;
    std::cout << "Solution: " << Fsolver3.LUDecompositionSolver_Doolittle() << std::endl;

    return (0);
}