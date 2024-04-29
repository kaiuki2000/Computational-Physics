#ifndef __INTEGRATORMC_H__
#define __INTEGRATORMC_H__

#include "Integrator.h"
#include "TFormula.h"
#include "TRandom3.h"

class IntegratorMC : public Integrator
{
public:
    //Default constructor
    IntegratorMC() : Ndim(0), F(nullptr) { ; }

    //Constructors for 1-dimensional functions
    IntegratorMC(double Argx0 = 0., double Argx1 = 1., const TF1 *Argf = nullptr) : Integrator(Argx0, Argx1, Argf), Ndim(1), F(nullptr) { ; }
    IntegratorMC(double Argx0, double Argx1, const TF1 &Argf) : IntegratorMC(Argx0, Argx1, &Argf) { ; }

    //Constructor for n-dimensional functions
    IntegratorMC(TFormula *Argf, int ArgN, std::vector<double> ArgVecx0, std::vector<double> ArgVecx1);

    //Destructor
    ~IntegratorMC();

    //'Setters'
    void SetDimension(int ArgN) { Ndim = ArgN; }

    //For 1-dim
    void SetLimits(double Argx0, double Argx1);
    void SetTF1(TF1 *Argf);

    //For n-dim
    void SetLimits(std::vector<double> ArgVecx0, std::vector<double> ArgVecx1);
    void SetFormula(TFormula *ArgFormula);

    //Monte-Carlo Integration techniques
    void UniformRandom(double &Integral, double &Error, int Nsamples);                                        //n-dim
    int UniformRandomRelativeError(double &Integral, double &Error, double RelError);                         //Created specifically for trab03 (n-dim)
    void ImportanceSampling(TF1 *Pdf, TF1 *Xy, double &Integral, double &Error, int Nsamples);                //1-dim
    int ImportanceSamplingRelativeError(TF1 *Pdf, TF1 *Xy, double &Integral, double &Error, double RelError); //Created specifically for trab03 (1-dim)
    void AcceptanceRejection(double &Integral, double &Error, int Nsamples);                                  //1-dim

private:
    //Function dimension
    int Ndim;

    //For Ndim > 1
    std::vector<double> Vecx0;
    std::vector<double> Vecx1;
    TFormula *F;
};
#endif // __INTEGRATORMC_H__