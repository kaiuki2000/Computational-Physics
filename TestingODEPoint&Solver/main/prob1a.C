#include "Integrator.h"
#include "ODEPoint.h"
#include "ODESolver.h"

#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "TF1.h"

#include "TTimer.h"
#include "Getline.h"

int main()
{

    const double l = 5.;
    const double g = 9.8;

    //Prob1: Alínea a).

    //Function that calculates the period for a given Theta0
    auto Period_Lambda = [&](double *Theta0, double *par) {
        //Converting from degrees into radians
        Theta0[0] = Theta0[0] * TMath::Pi() / 180.;

        auto Alpha_Lambda = [&](double *Alpha, double *par = nullptr) {
            return 1 / sqrt(1 - sin(Theta0[0] / 2) * sin(Theta0[0] / 2) * sin(Alpha[0]) * sin(Alpha[0]));
        };

        TF1 *Alpha = new TF1("Alpha", Alpha_Lambda, 0., TMath::PiOver2(), 0);

        Integrator AlphaIntegrator(0., TMath::PiOver2(), Alpha);

        double Integral = 0.;
        double Error = 0.;

        //Using Romberg integration...
        AlphaIntegrator.RombergRelativeError(Integral, Error, 1e-3);

        double Period = 4 * sqrt(l / g) * Integral;

        delete Alpha;

        return Period;
    };

    TF1 *Period = new TF1("Period", Period_Lambda, 1., 90., 0);

    TCanvas *C1 = new TCanvas("C1", "Multigraph1", 500, 500, 600, 600);
    C1->SetGrid();

    //Period(Theta0) graph
    TGraph *T = new TGraph(Period);
    T->SetLineColor(kOrange);
    T->SetLineWidth(3);
    T->SetMarkerStyle(20);
    T->SetMarkerColor(kOrange);
    T->SetTitle("Period(#theta_{0})");

    //Period(Theta0) plot
    TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(T);
    Mg->Draw("A");
    Mg->GetXaxis()->SetTitle("#theta_{0} (degrees)");
    Mg->GetYaxis()->SetTitle("Period (s)");

    C1->BuildLegend();
    C1->Modified();
    C1->SaveAs("prob1a_periodo.pdf", "AP");

    //Specifying integration method used...
    std::cout << "\nPara o cálculo dos integrais foi utilizado o método de Romberg, garantindo que o erro reltaivo era inferior a 1e-3." << std::endl
              << "Para ângulos iniciais da forma Thetha0= 1 + 4n (n= 0, 1, 2, ..., 22), tem-se:\n"
              << std::endl;

    //Printing periods for certain values of Theta0
    for (int n = 0; n < 23; n++)
    {
        std::cout << "Theta0= " << std::setw(2) << 1 + 4 * n << " graus= " << std::setw(9) << (1 + 4 * n) * (TMath::Pi() / 180.) << " rad: "
                  << "T= " << Period->Eval(1 + 4 * n) << " s"
                  << std::endl;
    }

    return 0;
}
