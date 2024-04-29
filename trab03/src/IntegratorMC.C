#include "IntegratorMC.h"

#include "TH1D.h"
#include "THStack.h"

//Constructor for n-dimensional functions
IntegratorMC::IntegratorMC(TFormula *Argf, int ArgN, std::vector<double> ArgVecx0, std::vector<double> ArgVecx1)
{
    if (ArgN == ArgVecx0.size() && ArgN == ArgVecx1.size()) //Testing dimensions to make sure they match
    {
        Ndim = ArgN; //Defining Ndim
        F = Argf;    //Defining F

        for (int i = 0; i < Ndim; i++)
        {
            Vecx0.push_back(ArgVecx0[i]); //Defining Vecx0
            Vecx1.push_back(ArgVecx1[i]); //Defining Vecx1
        }
    }
    else
    {
        std::cout << "***Error***: Dimensions do not match!" << std::endl;
    }
}

//Destructor
IntegratorMC::~IntegratorMC()
{
    Vecx0.clear();
    Vecx1.clear();
    //Checking if F exists
    if (F)
        delete F;
}

//1-dim: SetLimits method
void IntegratorMC::SetLimits(double Argx0, double Argx1)
{
    x0 = Argx0;
    x1 = Argx1;
}

//1-dim: SetTF1 method
void IntegratorMC::SetTF1(TF1 *Argf)
{
    //Updating Ndim
    Ndim = 1;
    //Updating f
    f = Argf;
}

//n-dim: SetLimits method
void IntegratorMC::SetLimits(std::vector<double> ArgVecx0, std::vector<double> ArgVecx1)
{
    if (Ndim == ArgVecx0.size() && Ndim == ArgVecx1.size()) //Testing dimensions to make sure they match
    {
        //Clearing old vectors
        Vecx0.clear();
        Vecx1.clear();

        //Filling Vecx0 and Vecx1 with the new values
        for (int i = 0; i < ArgVecx0.size(); i++)
        {
            Vecx0.push_back(ArgVecx0[i]);
            Vecx1.push_back(ArgVecx1[i]);
        }
    }
    else
    {
        std::cout << "***Error***: Dimensions do not match!" << std::endl;
    }
}

//n-dim: SetFormula method
void IntegratorMC::SetFormula(TFormula *ArgFormula)
{
    //Updating Ndim to match the new formula's dimension
    Ndim = ArgFormula->GetNdim();
    //Updating F
    F = ArgFormula;
}

//'Standard' Monte-Carlo Integration
void IntegratorMC::UniformRandom(double &Integral, double &Error, int Nsamples)
{
    if (Ndim == 1 && f)
    {
        TRandom3 Rgen(0);
        double x = 0.;
        double fSum = 0.;
        double fSumSq = 0.;
        double mean = 0.;

        for (int i = 0; i < Nsamples; i++)
        {
            //Generating x in the interval [x0,x1]
            x = x0 + (x1 - x0) * Rgen.Uniform();
            fSum += f->Eval(x);
            fSumSq += (f->Eval(x) * f->Eval(x));
        }

        //Calculating mean
        mean = fSum / Nsamples;

        //Calculating Integral
        Integral = (x1 - x0) * mean;

        //Calculating Error
        Error = ((x1 - x0) / sqrt(Nsamples)) * sqrt((fSumSq / Nsamples) - (mean * mean));
    }
    if (Ndim > 1 && F)
    {
        if (Ndim == Vecx0.size() && Ndim == Vecx1.size())
        {
            TRandom3 Rgen(0);
            double Volume = 1.;
            double *x = new double[Ndim];
            double fSum = 0.;
            double fSumSq = 0.;
            double mean = 0.;
            double TempError = 1.;

            //Calculating Volume
            for (int i = 0; i < Ndim; i++)
                Volume *= (Vecx0[i] - Vecx1[i]);

            for (int i = 0; i < Nsamples; i++)
            {
                //Generating x
                for (int j = 0; j < Ndim; j++)
                {
                    x[j] = Vecx0[j] + (Vecx1[j] - Vecx0[j]) * Rgen.Uniform();
                }

                fSum += F->EvalPar(x);
                fSumSq += (F->EvalPar(x) * F->EvalPar(x));
            }

            //Calculating mean
            mean = fSum / Nsamples;

            //Calculating Integral
            Integral = Volume * mean;

            //Calculating Error
            TempError = sqrt((fSumSq / Nsamples) - (mean * mean));

            for (int i = 0; i < Ndim; i++)
                TempError *= ((Vecx1[i] - Vecx0[i]) / (sqrt(Nsamples)));

            Error = TempError;
        }
    }
}

//'Standard' Monte-Carlo Integration: stops when relative error is smaller than 'RelError'
int IntegratorMC::UniformRandomRelativeError(double &Integral, double &Error, double RelError)
{
    //This commented section proved very inefficient, thus it was discarded.
    //Starts at 1e6 samples
    /*int NumberSamples = 1e6;

    do
    {
        UniformRandom(Integral, Error, NumberSamples);
        //Number of samples increases by 1e6 each iteration
        NumberSamples += 1;
    } while ((double)(Error / Integral) > RelError);

    return NumberSamples - 1;*/

    double FSum = 0.;
    double FSumSq = 0.;
    double x = 0.;

    //Count starts at 10. Because the Maxwell-Boltzmann distribution is almost zero for most values of x in [0.,inf],
    //We decided to start Count at 10 so that we find non-zero values, which lead to a better integral approximation.
    int Count = 10;
    double Error_temp = 1.;
    double Integral_temp = 1.;
    double RelError_temp = 1.;
    gRandom->SetSeed(0);

    //Calculating the first 10 points
    for (int i = 0; i < Count; i++)
    {
        x = gRandom->Uniform(x0, x1);
        FSum += f->Eval(x);
        FSumSq += (f->Eval(x) * f->Eval(x));
    }

    //This cicle will stop when the desired relative error is achieved
    while (RelError_temp > RelError)
    {
        x = gRandom->Uniform(x0, x1);
        FSum += f->Eval(x);
        FSumSq += (f->Eval(x) * f->Eval(x));

        Count++;

        double FMean = (double)(FSum / Count);
        double FMeanSq = (double)(FSumSq / Count);
        double Variance = (double)(FMeanSq - FMean * FMean);

        Integral_temp = FMean * (x1 - x0);
        Error_temp = sqrt((double)(Variance / Count)) * (x1 - x0);
        RelError_temp = (double)(Error_temp / Integral_temp);
    }

    //Calculating integral value and its error
    Integral = Integral_temp;
    Error = Error_temp;
    //Returning number of randoms generated
    return Count;
}

//1-dim: Importance Sampling Monte-Carlo Integration method
void IntegratorMC::ImportanceSampling(TF1 *Pdf, TF1 *Xy, double &Integral, double &Error, int Nsamples)
{
    TRandom3 Rgen(0);
    double FSum = 0.;
    double FSumSq = 0.;
    double y = 0.;
    double x = 0.;
    double Quotient = 0.;

    for (int i = 0; i < Nsamples; i++)
    {
        //Generating y in the interval [0,1]
        y = Rgen.Uniform(0., 1.);

        //Generating x in the interval [x0,x1]
        x = Xy->Eval(y);

        //Calculating f[x(y)]/p[x(y)] for each y
        Quotient = f->Eval(x) / Pdf->Eval(x);

        FSum += Quotient;
        FSumSq += Quotient * Quotient;
    }

    //Calculating Integral
    Integral = FSum / Nsamples;

    //Calculating Error
    Error = (1 / sqrt(Nsamples)) * (sqrt(FSumSq / Nsamples - Integral * Integral));
}

//Importance sampling: stops when relative error is smaller than 'RelError'
int IntegratorMC::ImportanceSamplingRelativeError(TF1 *Pdf, TF1 *Xy, double &Integral, double &Error, double RelError)
{
    //This commented section proved rather inefficient, thus it was discarded.
    //Starts at 1e6 samples
    /*int NumberSamples = 1e6;

    do
    {
        ImportanceSampling(Pdf, Xy, Integral, Error, NumberSamples);
        //Number of samples increases by 1e6 each iteration
        NumberSamples += 1;
    } while ((double)(Error / Integral) > RelError);

    return NumberSamples - 1;*/

    double FSum = 0.;
    double FSumSq = 0.;
    double y = 0.;
    double x = 0.;
    double Quotient = 0.;

    //Here we also initialize Count as 10, pretty much due to the same reasons as in UniformRandomRelativeError.
    //However, in this case, due to using "importance sampling", we could've actually started Count = 1 and still obtain good results.
    //We decided to leave Count=10 just to make sure no errors occur.
    int Count = 10;
    double Error_temp = 1.;
    double Integral_temp = 1.;
    double RelError_temp = 1.;
    gRandom->SetSeed(0);

    for (int i = 0; i < Count; i++)
    {
        //Generating random y in [0,1]
        y = gRandom->Uniform();
        //Generating random x in [x0,x1]
        x = Xy->Eval(y);

        //Calculating the quotient: f(x) / pdf(x)
        Quotient = f->Eval(x) / Pdf->Eval(x);

        FSum += Quotient;
        FSumSq += Quotient * Quotient;
    }

    while (RelError_temp > RelError)
    {
        //Generating random y in [0,1]
        y = gRandom->Uniform();
        //Generating random x in [x0,x1]
        x = Xy->Eval(y);

        //Calculating the quotient: f(x) / pdf(x)
        Quotient = f->Eval(x) / Pdf->Eval(x);

        FSum += Quotient;
        FSumSq += Quotient * Quotient;

        //Incrementing Count
        Count++;

        double FMean = (double)(FSum / Count);
        double FMeanSq = (double)(FSumSq / Count);
        double Variance = (double)(FMeanSq - FMean * FMean);

        Integral_temp = FMean;
        Error_temp = sqrt((double)(Variance / Count));
        RelError_temp = (double)(Error_temp / Integral_temp);
    }

    //Calculating integral value and its error
    Integral = Integral_temp;
    Error = Error_temp;
    //Returning Count
    return Count;
}

//1-dim: Acceptance-Rejection Monte-Carlo Integration method
void IntegratorMC::AcceptanceRejection(double &Integral, double &Error, int Nsamples)
{
    if (Ndim == 1)
    {
        double fMax = f->GetMaximum();

        TH1D *H1 = new TH1D("H1", "Normalized distribution", 100, x0, x1);
        for (int i = 0; i < Nsamples; i++)
            H1->Fill(f->GetRandom());

        double Norm = H1->GetEntries();
        H1->Scale(1 / Norm);

        TRandom3 Rgen(0);
        TH1D *H2 = new TH1D("H2", "Acceptance-Rejection with fMax", 100, x0, x1);
        for (int i = 0; i < Nsamples; i++)
        {
            double x = x0 + (x1 - x0) * Rgen.Uniform();
            double u = Rgen.Uniform();
            if (u < (f->Eval(x) / fMax))
                H2->Fill(x);
        }

        Norm = H2->GetEntries();
        H2->Scale(1 / Norm);

        Integral = Norm / Nsamples * fMax * (x1 - x0);
        Error = (x1 - x0) * fMax / Nsamples * sqrt(Norm * (1 - Norm / Nsamples));

        TCanvas *C1 = new TCanvas("C1", "C1", 500, 500);

        H1->SetLineColor(kBlue);
        H1->SetLineWidth(2.0);

        H2->SetLineColor(kRed);
        H2->SetLineWidth(2.0);

        THStack *S = new THStack("HistStack", "ROOT f->GetRandom() vs User Acceptance-Rejection");
        S->Add(H1);
        S->Add(H2);

        S->Draw("HIST nostack");

        C1->BuildLegend();
        C1->Modified();
        C1->SaveAs("Acceptance-Rejection.eps", "AP");

        delete C1;
        delete S;
        delete H1;
        delete H2;
    }
}
