#include "FCmatrixAlgorithm.h"

//#define DEBUGBUILD3

//GaussElimination without pivoting
int FCmatrixAlgorithm::GaussElimination(FCmatrix &matrix)
{
#ifdef DEBUGBUILD3
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    int sign = 1;
    int counter = 0;
    for (int i = 0; i < matrix.GetRowN() - 1; i++)
    {
        //Swap lines in order to not divide by 0
        while (matrix[i][i] == 0)
        {
            counter++;
            if (counter == matrix.GetRowN())
            {
                counter = 0;
                i++;
                break;
            }
            matrix.SwapLines(i, i + counter);
            sign *= -1;
        }
        for (int j = i + 1; j < matrix.GetRowN(); j++)
        {
            double factor = matrix[j][i] / matrix[i][i];
            matrix[j] -= matrix[i] * (factor);
        }
    }
    return sign;
}