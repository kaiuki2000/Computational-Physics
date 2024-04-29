#ifndef __EQSOLVER_H__
#define __EQSOLVER_H__

#include "FCMatrixAlgorithm.h"

class EqSolver
{
public:
    EqSolver();                                                  //Default constructor
    EqSolver(const FCMatrix &);                                  //Constructor 2 (Receives augmented matrix)
    EqSolver(const FCMatrix &, const Vec &);                     //Constructor 3 (Receives coefficient matrix and constants vector)
    EqSolver(const FCMatrix &, const Vec &, std::string method); //Constructor 4 (LU Decomposition)

    //Solvers
    Vec GaussEliminationSolver();
    Vec LUDecompositionSolver_Doolittle();

private:
    //Elementos já reduzidos, i.e, já passaram por eliminação de Gauss...
    FCMatrixFull ReducedMatrix;

    //LUDecompositionSolver_Doolittle
    FCMatrixFull M; //Coefficient matrix
    Vec b;          //Constants vector
};

#endif // __EQSOLVER_H__