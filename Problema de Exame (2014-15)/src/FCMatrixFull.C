#include "FCMatrixFull.h"
#include "FCMatrixAlgorithm.h"

//#define DEBUGBUILD2_1

//Default constructor
FCMatrixFull::FCMatrixFull()
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
}

//Constructor 2
FCMatrixFull::FCMatrixFull(double **matrix, int m, int n) //m Rows && n columns
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (!matrix)
        throw std::invalid_argument(Form("[%s] Recieved null pointer to array...!\n", __PRETTY_FUNCTION__));

    for (int i = 0; i < m; i++)
        M.emplace_back(n, matrix[i]);
}

//Constructor 3 (Vetores coluna)
FCMatrixFull::FCMatrixFull(double *vec, int m, int n)
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (!vec)
        throw std::invalid_argument(Form("[%s] Recieved null pointer to array...!\n", __PRETTY_FUNCTION__));

    for (int i = 0; i < m; ++i)
    {
        M.emplace_back(n, &vec[i * n]);
    }
}

//Constructor 4
FCMatrixFull::FCMatrixFull(const std::vector<Vec> &matrix)
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    for (int i = 0; i < matrix.size(); i++)
    {
        M.emplace_back(matrix[i]);
    }
}

//Constructor 5
FCMatrixFull::FCMatrixFull(const Vec &vec)
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    for (int i = 0; i < vec.size(); i++)
    {
        M.emplace_back(1, vec[i]);
    }
}

//Created specifically for Romberg integration. Most likely unusable for any other situation.
FCMatrixFull::FCMatrixFull(const Vec &vec, char c)
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    for (int i = 0; i < vec.size(); i++)
    {
        M.emplace_back(1, vec[i], 'd');
    }
}

//Copy constructor
FCMatrixFull::FCMatrixFull(const FCMatrixFull &matrix) : FCMatrixFull(matrix.M)
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
}

//Destructor
FCMatrixFull::~FCMatrixFull()
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    M.clear();
}

//Additional methods
//Get number of rows
int FCMatrixFull::GetRowN() const
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    return M.size();
}

//Get number of columns
int FCMatrixFull::GetColN() const
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    return M[0].size();
}

//operator[]
Vec &FCMatrixFull::operator[](int i)
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    return M[i];
}

//operator=
void FCMatrixFull::operator=(const FCMatrix &matrix)
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (this != &matrix)
    {
        M.clear();
        for (int i = 0; i < matrix.GetRowN(); i++)
        {
            M.push_back(matrix.GetRow(i)); //Changed: matrix.M[i]-> matrix.GetRow(i)...
        }
    }
}

//SwapLines method
void FCMatrixFull::SwapLines(int i, int j)
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    std::swap(M[i], M[j]);
}

//operator| (Alters the obj. matrix)
void FCMatrixFull::operator|(const Vec &vec)
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (M.size() == vec.size())
    {
        for (int i = 0; i < M.size(); i++)
        {
            M[i].push_back(vec[i]);
        }
    }
    else
    {
        throw std::invalid_argument(Form("[%s] [nullptr] Matrix size and vector size incompatible...!\n", __PRETTY_FUNCTION__));
    }
}

//operator|| -> Doesn't alter obj. matrix (Augmented matrix) -> returns an FCMatrix
FCMatrixFull FCMatrixFull::operator||(const Vec &vec) const
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (M.size() == vec.size())
    {
        FCMatrixFull A(M);
        for (int i = 0; i < A.GetRowN(); i++)
        {
            A[i].push_back(vec[i]);
        }
        return A;
    }
    else
    {
        throw std::invalid_argument(Form("[%s] [nullptr] Matrix size and vector size incompatible...!\n", __PRETTY_FUNCTION__));
    }
}

//Determinant method
double FCMatrixFull::Determinant() const
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (M.size() == M[0].size())
    {
        int sign = 1;
        double det = 1;
        FCMatrixFull MDet(M);
        sign = FCMatrixAlgorithm::GaussElimination(MDet);
        for (int i = 0; i < M.size(); i++)
        {
            det *= MDet[i][i];
        }
        return det * sign;
    }
    else
    {
        throw std::invalid_argument(Form("[%s] Cannot compute non-square matrix determinant...!\n", __PRETTY_FUNCTION__));
    }
}

//GetRow method
Vec FCMatrixFull::GetRow(int i) const
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    return (M[i]);
}
