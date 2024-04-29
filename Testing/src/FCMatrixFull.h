#ifndef __FCMATRIXFULL_H__
#define __FCMATRIXFULL_H__

#include "FCMatrix.h"

class FCMatrixFull : public FCMatrix
{
public:
    //Constructors
    FCMatrixFull();                          //Constructor 1
    FCMatrixFull(double **, int, int);       //Constructor 2 (Rows columns)
    FCMatrixFull(double *, int, int);        //Constructor 3 (Rows columns)
    FCMatrixFull(const std::vector<Vec> &);  //Constructor 4
    FCMatrixFull(const Vec &);               //Constructor 5 (vetor coluna)
    FCMatrixFull(const Vec &, char c = 'd'); //Created specifically for Romberg integration. Most likely unusable for any other situation.
    FCMatrixFull(const FCMatrixFull &);      //Copy constructor

    //Destructor
    ~FCMatrixFull();

    //Additional methods
    int GetRowN() const; // No. of rows
    int GetColN() const; // No. of columns
    Vec &operator[](int);
    void operator=(const FCMatrix &);
    void SwapLines(int, int);
    double Determinant() const;
    void operator|(const Vec &);                //Alters the obj. matrix (Augmented matrix) //If we need to alter the method, just uncomment and implement.
    FCMatrixFull operator||(const Vec &) const; //operator|| -> Doesn't alter obj. matrix (Augmented matrix) -> returns an FCMatrixFull //Only new method compared to abstract class...
    Vec GetRow(int i = 0) const;                //If we need to alter the method, just uncomment and implement.                         //FCMatrix.

    /*void operator+(const FCMatrix &);
    void operator-(const FCMatrix &);
    void operator*(const FCMatrix &);
    void operator*(double);*/
};

#endif // __FCMATRIXFULL_H__