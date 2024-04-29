#include <cmath>

double sum(int *vi, int *vj)
{
    double sum = 0;
    for (int i = vi[0]; i < vi[1]; i++)
    {
        for (int j = vj[0]; j < vj[1]; j++)
        {
            sum += cos(pow(i, 2) + sqrt(j));
        }
    }
    return sum;
}