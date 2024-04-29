#ifndef __ODEPOINT_H__
#define __ODEPOINT_H__

#include <vector>
#include <iostream>
#include <iomanip>

class ODEPoint
{
public:
    //Constructors
    ODEPoint(int ArgNdim = 0, const double *Argx = nullptr);
    ODEPoint(int ArgNdim, const std::vector<double> &Argx);
    ODEPoint(const ODEPoint &Obj);

    //Destructor
    ~ODEPoint();

    //'Getters'
    int GetNdim() const { return Ndim; };
    double GetTime() const { return x[0]; };
    double GetX(int i) const { return x[i + 1]; };
    std::vector<double> GetVector() const { return x; };
    double *GetArray() const;

    //'Setters'
    void SetNdim(int ArgNdim) { Ndim = ArgNdim; };
    void SetVector(const std::vector<double> &Argx)
    {
        Ndim = Argx.size() - 1;
        x = Argx;
    };

    //Operators
    ODEPoint operator*(double) const;
    ODEPoint operator+(const ODEPoint &) const;
    ODEPoint operator-(const ODEPoint &) const;

    void operator=(const ODEPoint &);

    double operator[](int i) const;
    double &operator[](int i);

    //Friend methods
    friend std::ostream &operator<<(std::ostream &, const ODEPoint &);

private:
    int Ndim;              //Number of dependent variables
    std::vector<double> x; //Independent variable + dependent variables (Ndim+1)
};
#endif // __ODEPOINT_H__