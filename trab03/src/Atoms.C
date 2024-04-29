#include "Atoms.h"

const double Epslon = 1.;
const double Sigma = 1.;

auto LJPot = [](double *r, double *par = nullptr) {
    return 4 * Epslon * (pow(Sigma / r[0], 6) - pow(Sigma / r[0], 12));
};

TF1 *func2 = new TF1("", LJPot, 0.5, 22.);

////////////////////////////////////////////////////////////////////////
/////////////////////////// Constructors ///////////////////////////////
////////////////////////////////////////////////////////////////////////
Atoms::Atoms()
{
    pos = std::make_pair(0, 0);
    vel = std::make_pair(0, 0);
    ace = std::make_pair(0, 0);
    FinalForce = std::make_pair(0, 0);
    FinalPot = 0.;
    r = std::vector<std::pair<double, double>>(100, std::make_pair(0, 0));
}

Atoms::~Atoms()
{
}

/////////////////////////////////////////////////////////////////
///////////////////////// SETTERS ///////////////////////////////
/////////////////////////////////////////////////////////////////
void Atoms::SetPos(double &x, double &y)
{
    pos = std::make_pair(x, y);
}

void Atoms::SetAce()
{
    ace.first = FinalForce.first / m;
    ace.second = FinalForce.second / m;
}

void Atoms::SetR(std::pair<double, double> &pair, int i)
{
    r.insert(r.begin() + i, pair);
}

void Atoms::SetForce(std::pair<double, double> &pair, double &modr)
{
    FinalForce.first += pair.first;
    FinalForce.second += pair.second;
    FinalPot += func2->Eval(modr);
}

void Atoms::SetFinalForce(std::pair<double, double> &pair)
{
    FinalForce = pair;
}