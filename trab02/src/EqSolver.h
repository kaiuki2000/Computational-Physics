#ifndef __EQSOLVER_H__
#define __EQSOLVER_H__

#include "FCmatrixAlgorithm.h"

class EqSolver
{
public:
    EqSolver();                              //Default constructor
    EqSolver(const FCmatrix &);              //Constructor 2 (Receives augmented matrix)
    EqSolver(const FCmatrix &, const Vec &); //Constructor 3 (Receives coefficient matrix and constants vector)

    //Solvers
    Vec GaussEliminationSolver();

private:
    //Elementos já reduzidos, i.e, já passaram por eliminação de Gauss...
    FCmatrixFull ReducedMatrix;

    //LUDecompositionSolver_Doolittle
    FCmatrixFull M; //Coefficient matrix
    Vec b;          //Constants vector
};

#endif // __EQSOLVER_H__