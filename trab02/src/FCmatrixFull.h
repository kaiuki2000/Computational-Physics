#ifndef __FCMATRIXFULL_H__
#define __FCMATRIXFULL_H__

#include "FCmatrix.h"

class FCmatrixFull : public FCmatrix
{
public:
    //Constructors
    FCmatrixFull();                         //Constructor 1
    FCmatrixFull(double **, int, int);      //Constructor 2 (Rows columns)
    FCmatrixFull(double *, int, int);       //Constructor 3 (Rows columns)
    FCmatrixFull(const std::vector<Vec> &); //Constructor 4
    FCmatrixFull(const Vec &);              //Constructor 5 (vetor coluna)
    FCmatrixFull(const FCmatrixFull &);     //Copy constructor

    //Destructor
    ~FCmatrixFull();

    //Additional methods
    int GetRowN() const; // No. of rows
    int GetColN() const; // No. of columns
    Vec &operator[](int);
    void operator=(const FCmatrix &);
    void SwapLines(int, int);
    double Determinant() const;
    void operator|(const Vec &);                //Alters the obj. matrix (Augmented matrix) //If we need to alter the method, just uncomment and implement.
    FCmatrixFull operator||(const Vec &) const; //operator|| -> Doesn't alter obj. matrix (Augmented matrix) -> returns an FCmatrixFull //Only new method compared to abstract class...
    Vec GetRow(int i = 0) const;                //If we need to alter the method, just uncomment and implement.                         //FCmatrix.
    Vec GetCol(int i = 0) const;
    void AddLine(Vec);
    FCmatrixFull inv(FCmatrixFull &, int &);

    FCmatrixFull operator+(const FCmatrix &) const; //add 2 matrices of any kind
    FCmatrixFull operator-(const FCmatrix &) const; //sub 2 matrices of any kind
    FCmatrixFull operator*(const FCmatrix &) const; //mul 2 matrices of any kind
    FCmatrixFull operator*(double lambda) const;    //mul matrix of any kind by scalar
    Vec operator*(const Vec &) const;               //mul matrix by Vec
};

#endif // __FCMATRIXFULL_H__