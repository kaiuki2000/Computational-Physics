#ifndef __VEC_H__
#define __VEC_H__

#include <iostream>
#include "TROOT.h"
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <cstdio>
#include <cmath>

class Vec
{
public:
    //Constructors
    Vec(int n = 0, int val = 0);    //Constructor: Number of elements, value of the elements;
    Vec(int n, double val, char c); //Constructor: Number of elements, value of the elements, 'd' flag for double;
                                    //Created specifically for Romberg integration. Most likely unusable for any other situation.

    Vec(int, double *); //Constructor: Number of elements, array;
    Vec(const Vec &);   //Copy constructor;

    Vec &operator=(const Vec &); //Copy assignment;

    ~Vec(); //Destructor.

    //Methods
    void SetEntries(int, double *);
    int size() const;
    double operator[](int) const;
    double &operator[](int);
    const Vec &operator+=(const Vec &);
    const Vec &operator-=(const Vec &);
    const Vec &operator*=(double);
    const Vec &operator/=(double);
    Vec operator*(double) const;
    double maxAbs();
    void swap(int, int);
    void push_back(double);
    void clear();
    double dot(const Vec &);

    //Friend methods
    friend std::ostream &operator<<(std::ostream &, const Vec &);

private:
    int N;           //Number of elements
    double *entries; //Pointer to array of doubles
};

#endif // __VEC_H__