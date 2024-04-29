#ifndef __FCMATRIX_H__
#define __FCMATRIX_H__

#include "Vec.h"
#include <vector>

class FCMatrix
{
public:
    //Friend methods
    friend std::ostream &operator<<(std::ostream &, const FCMatrix &);

    //Pure virtual methods
    virtual int GetRowN() const = 0; // No. of rows
    virtual int GetColN() const = 0; // No. of columns
    virtual Vec &operator[](int) = 0;
    virtual void operator=(const FCMatrix &) = 0;
    virtual void SwapLines(int, int) = 0;
    virtual double Determinant() const = 0;
    virtual void operator|(const Vec &) = 0; //Alters the obj. matrix (Augmented matrix)
    virtual Vec GetRow(int i = 0) const = 0;

protected:
    std::vector<Vec> M;
};

#endif // __FCMATRIX_H__