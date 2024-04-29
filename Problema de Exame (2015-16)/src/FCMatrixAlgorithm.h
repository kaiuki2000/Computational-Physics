#ifndef __FCMATRIXALGORITHM_H__
#define __FCMATRIXALGORITHM_H__

#include "FCMatrix.h"
#include "FCMatrixFull.h"

class FCMatrixAlgorithm
{
public:
    static int GaussElimination(FCMatrix &);
    static FCMatrixFull *LUDecomposition_Doolittle(FCMatrix &);
};

#endif // __FCMATRIXALGORITHM_H__