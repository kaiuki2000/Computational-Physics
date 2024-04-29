#ifndef __ATOMS_H__
#define __ATOMS_H__
#include <utility> // std::pair, std::make_pair
#include <string>
#include <iostream>
#include <vector>
#include "TStopwatch.h"
#include "TMultiGraph.h"
#include "TF1.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"

const double m = 1.;
class Atoms
{
public:
    Atoms();
    ~Atoms();
    void SetPos(double &x, double &y);
    void SetAce();
    void SetR(std::pair<double, double> &pair, int i);
    void SetForce(std::pair<double, double> &pair, double &modr); //Force and position
    void SetFinalForce(std::pair<double, double> &pair);

    std::vector<std::pair<double, double>> r, Pot;
    std::pair<double, double> FinalForce, pos, vel, ace;
    double FinalPot;
};

#endif // __ATOMS_H__