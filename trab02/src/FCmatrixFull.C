#include "FCmatrixFull.h"
#include "FCmatrixAlgorithm.h"

//#define DEBUGBUILD2_1

//Default constructor
FCmatrixFull::FCmatrixFull()
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
}

//Constructor 2
FCmatrixFull::FCmatrixFull(double **matrix, int m, int n) //m Rows && n columns
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
FCmatrixFull::FCmatrixFull(double *vec, int m, int n)
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
FCmatrixFull::FCmatrixFull(const std::vector<Vec> &matrix)
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
FCmatrixFull::FCmatrixFull(const Vec &vec)
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    for (int i = 0; i < vec.size(); i++)
    {
        M.emplace_back(1, vec[i]);
    }
}

//Copy constructor
FCmatrixFull::FCmatrixFull(const FCmatrixFull &matrix) : FCmatrixFull(matrix.M)
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
}

//Destructor
FCmatrixFull::~FCmatrixFull()
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    M.clear();
}

//Additional methods
//Get number of rows
int FCmatrixFull::GetRowN() const
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    return M.size();
}

//Get number of columns
int FCmatrixFull::GetColN() const
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    return M[0].size();
}

//operator[]
Vec &FCmatrixFull::operator[](int i)
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    return M[i];
}

//operator=
void FCmatrixFull::operator=(const FCmatrix &matrix)
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
void FCmatrixFull::SwapLines(int i, int j)
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    std::swap(M[i], M[j]);
}

//operator| (Alters the obj. matrix)
void FCmatrixFull::operator|(const Vec &vec)
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

//operator|| -> Doesn't alter obj. matrix (Augmented matrix) -> returns an FCmatrix
FCmatrixFull FCmatrixFull::operator||(const Vec &vec) const
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (M.size() == vec.size())
    {
        FCmatrixFull A(M);
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
double FCmatrixFull::Determinant() const
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (M.size() == M[0].size())
    {
        int sign = 1;
        double det = 1;
        FCmatrixFull MDet(M);
        sign = FCmatrixAlgorithm::GaussElimination(MDet);
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
Vec FCmatrixFull::GetRow(int i) const
{
#ifdef DEBUGBUILD2_1
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    return (M[i]);
}

//GetCol
Vec FCmatrixFull::GetCol(int i) const
{
    Vec v;
    double a[GetRowN()];

    for (int j = 0; j < GetRowN(); j++)
    {
        a[j] = M[j][i];
    }
    v.SetEntries(GetRowN(), a);
    return v;
}

//AddLine method
void FCmatrixFull::AddLine(Vec v)
{
    M.push_back(v);
}

//FCmatrixFull operators: +, -, *
FCmatrixFull FCmatrixFull::operator+(const FCmatrix &f) const //add 2 matrices of any kind
{
    Vec v1, v2, v;
    std::vector<Vec> vv;

    if ((f.GetRowN() == this->GetRowN()) && (f.GetColN() == this->GetColN()))
    {
        for (int i = 0; i < M.size(); i++)
        {
            v1 = f.GetRow(i);
            v2 = M[i];
            v = (v1 += v2);
            vv.push_back(v);
        }
        FCmatrixFull fm(vv);
        return fm;
    }
    else
    {
        std::cout << "Uma vez que não é possível realizar a operação com as matrizes pedidas, é feito o retorno de uma matriz nula.";
        std::cout << std::endl
                  << "Para adicionar duas matrizes, garanta que têm a mesma dimensão...!" << std::endl;
        FCmatrixFull fm;
        return fm;
    }
}

FCmatrixFull FCmatrixFull::operator-(const FCmatrix &f) const //sub 2 matrices of any kind
{
    Vec v1, v2, v;
    std::vector<Vec> vv;

    if (f.GetRowN() == this->GetRowN() && f.GetColN() == this->GetColN())
    {
        for (int i = 0; i < M.size(); i++)
        {
            v1 = f.GetRow(i);
            v2 = M[i];
            v = (v1 -= v2);
            vv.push_back(v);
        }
        FCmatrixFull fm(vv);
        return fm;
    }
    else
    {
        std::cout << "Uma vez que não é possível realizar a operação com as matrizes pedidas, é feito o retorno de uma matriz nula.";
        std::cout << std::endl
                  << "Para subtrarair duas matrizes, garanta que têm a mesma dimensão...!" << std::endl;
        FCmatrixFull fm;
        return fm;
    }
}

FCmatrixFull FCmatrixFull::operator*(const FCmatrix &f) const //mul 2 matrices of any kind
{
    Vec v1, v2;
    std::vector<Vec> vv;
    double a[f.GetColN()];
    FCmatrixFull mult;

    if (f.GetRowN() == this->GetColN())
    {

        Vec v(f.GetColN());
        for (int i = 0; i < GetRowN(); i++)
        {
            v1 = GetRow(i);
            for (int j = 0; j < f.GetColN(); j++)
            {
                v2 = f.GetCol(j);
                a[j] = v1.dot(v2);
            }
            v.SetEntries(f.GetColN(), a);
            vv.push_back(v);
        }

        FCmatrixFull mult(vv);
        return mult;
    }
    else
    {
        std::cout << "Uma vez que não é possível realizar a operação com as matrizes pedidas, é feito o retorno de uma matriz nula.";
        std::cout << std::endl
                  << "Para multiplicar duas matrizes, garanta que a segunda tem número de linhas igual ao número de colunas da primeira...!" << std::endl;
        FCmatrixFull mult;
        return mult;
    }
}

FCmatrixFull FCmatrixFull::operator*(double lambda) const //mul matrix of any kind by scalar
{
    Vec v1;
    std::vector<Vec> vv;
    double a[GetRowN()];

    for (int j = 0; j < GetRowN(); j++)
    {
        v1 = GetRow(j);
        for (int i = 0; i < GetColN(); i++)
        {
            a[i] = v1[i] * lambda;
        }
        v1.SetEntries(GetColN(), a);
        vv.push_back(v1);
    }
    FCmatrixFull mult(vv);
    return mult;
}

Vec FCmatrixFull::operator*(const Vec &v) const //mul matrix by Vec
{
    Vec mul;

    if (GetColN() != v.size())
    {
        std::cout << "É impossível multiplicar esta matriz por este vetor.\nCertifique-se que a dimensão das colunas da matriz é igual à dimensão do vetor...!\n";
        return mul;
    }

    double a[GetColN()];

    for (int i = 0; i < GetColN(); i++)
    {
        a[i] = GetRow(i).dot(v);
    }

    mul.SetEntries(GetColN(), a);

    return mul;
}

//inv method
//Como funciona:
//Este algoritmo assume uma matriz MatB de dimensão n. A inversa é calculada em n iterações.
//Basicamente a cada iteração os elementos a(i,j) da matriz vão ser sucessivamente substituídos pelos elementos da sua inversa.
//O algoritmo escolhe os pivots começando de a(1,1) até a(n,n). Se algum dos pivots der 0, a inversa não pode ser calculada.
//A forma como cada elemento é calculado está em baixo.
FCmatrixFull FCmatrixFull::inv(FCmatrixFull &MatB, int &size)
{
    double pivot, det = 1.0;
    int i, j, p;
    for (p = 0; p < size; p++)
    {
        pivot = MatB[p][p];
        det = det * pivot;
        if (fabs(pivot) < 1e-16)   //Precisão de um double
            return FCmatrixFull(); //Não foi possível calcular a inversa
        for (i = 0; i < size; i++)
            MatB[i][p] = -MatB[i][p] / pivot;
        for (i = 0; i < size; i++)
            if (i != p)
                for (j = 0; j < size; j++)
                    if (j != p)
                        MatB[i][j] = MatB[i][j] + MatB[p][j] * MatB[i][p];
        for (j = 0; j < size; j++)
            MatB[p][j] = MatB[p][j] / pivot;
        MatB[p][p] = 1 / pivot;
    }
    return MatB;
}