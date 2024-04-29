#ifndef __POINT_H__
#define __POINT_H__

#include <string>
#include <iostream>

using namespace std;

class point
{
public:
    point() { ; }
    virtual ~point() { ; }
    virtual double Norma() = 0;
    virtual void Print() = 0;
    virtual void SetPoint(double *) = 0;
    void SetName(string str) { name = str; };
    string GetName() { return name; };

protected:
    string name;
};
#endif // __POINT_H__