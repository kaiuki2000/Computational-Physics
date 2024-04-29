#include <cmath>
#include "TF1.h"
#include "Integrator.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TAxis.h"

using namespace std;

//Converts degrees to radians
double Deg2Rad(double &deg)
{
    return deg * TMath::Pi() / 180.;
}

//Prob1a
int main()
{
    const double l = 5.;
    const double g = 9.8;

    //Lambda function utilized to calculate the pendulum's period for a given Thetha0
    auto PeriodLambda = [&](double *Thetha0, double *PeriodPar) {
        //Theta0 is provided in degrees
        //Alpha comes in radians, though
        auto FunctionLambda = [&](double *Alpha, double *FunctionPar) {
            return 1 / sqrt(1 - sin(Deg2Rad(Thetha0[0]) / 2.) * sin(Deg2Rad(Thetha0[0]) / 2.) * sin(Alpha[0]) * sin(Alpha[0]));
        };

        auto Function = new TF1("Function", FunctionLambda, 0., TMath::PiOver2(), 0);

        Integrator Int(0., TMath::PiOver2(), Function);

        double IntegralVal = 0.;
        double Error = 0.;

        //Using Romberg integration (guaranteeing a relative error smaller than 10^-3)
        Int.RombergRelativeError(IntegralVal, Error, 1e-3);

        delete Function;

        return 4 * sqrt(l / g) * IntegralVal;
    };

    auto PeriodTF1 = new TF1("PeriodTF1", PeriodLambda, 1., 90., 0);

    TCanvas *C1 = new TCanvas("C1", "Multigraph", 500, 500, 600, 600);
    C1->SetGrid();

    //As asked in the question paper
    PeriodTF1->SetNpx(23);
    TGraph *G1 = new TGraph(PeriodTF1);
    G1->SetLineColor(kOrange);
    G1->SetLineWidth(3);
    G1->SetMarkerStyle(20);
    G1->SetMarkerColor(kOrange);
    G1->SetTitle("T(#theta_{0})");

    TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(G1, "lp");
    Mg->Draw("A");
    Mg->GetXaxis()->SetTitle("#theta_{0} (Degrees)");
    Mg->GetYaxis()->SetTitle("T (Seconds)");

    C1->BuildLegend();
    C1->Modified();
    C1->SaveAs("TesteProb1a_periodo.pdf", "AP");

    cout << endl;

    cout << "Para a integração numérica foi utilizado o método de Romberg, garantindo que o erro relativo era inferior a 10^-3." << endl
         << "A seguir, apresento os valores do período para diferentes valores de Theta0:" << endl;

    for (int n = 0; n < 23; n++)
    {
        cout << "Theta0 = " << setw(2) << 1 + 4 * n << "°: T= " << PeriodTF1->Eval(1 + 4 * n);

        if (n != 22)
            cout << " s;" << endl;
        else
            cout << " s." << endl;
    }

    delete PeriodTF1;

    return 0;
}