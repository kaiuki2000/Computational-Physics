#ifndef __Vec__
#define __Vec__

#include <iostream> // ostream

class Vec
{

public:
    // constructors
    Vec(int i = 0, double x = 0); // Vec v;
    Vec(int, const double *);
    Vec(const Vec &);

    // destructor
    ~Vec();

    // operators
    double operator[](int i) const;
    double &operator[](int i);

    void operator=(const Vec &); // A=B
    const Vec &operator+=(const Vec &);

    //(...)
    /*
  the overloading of then * operator allows multiply a vector by a
  scalar:
  Vec * scalar
  */
    Vec operator*(double) const; //Vec.operator*(double) <=> A*5.

    // friend methods
    friend std::ostream &operator<<(std::ostream &, const Vec &);
    /*
  in order to multiply a scalar to a vector (scalar*Vec) we need
  to implement a friend method:
  friend Vec operator*(double, const Vec&);
  */

private:
    int N;           // number of elements
    double *entries; // array
};
#endif