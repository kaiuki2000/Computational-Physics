#include "FCMatrix.h"

//#define DEBUGBUILD2

//Friend methods
//std::cout << FCMatrix...
std::ostream &operator<<(std::ostream &s, const FCMatrix &matrix)
{
#ifdef DEBUGBUILD2
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    s << "Matrix: [\n";
    for (int i = 0; i < matrix.GetRowN(); ++i)
    {
        s << "           " << matrix.M[i] << "\n";
    }
    s << "        ]";
    printf("\n");
    return s;
}

//operator= //Why does this even work?
void FCMatrix::operator=(const FCMatrix &matrix)
{
#ifdef DEBUGBUILD2
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
