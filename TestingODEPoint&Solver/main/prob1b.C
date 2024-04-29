#include "Integrator.h"
#include "ODEPoint.h"
#include "ODESolver.h"

#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "TF1.h"

int main()
{

    const double l = 5.;
    const double g = 9.8;

    //Prob1: Alínea b).

    //Solving differential equation with Runge-Kutta 4th order
    std::vector<TFormula> ArgFormulas;
    TFormula ArgFormula0("Formula0", "x[2]");
    TFormula ArgFormula1("Formula1", "(-9.8/5.)*sin(x[1])");

    ArgFormulas.push_back(ArgFormula0);
    ArgFormulas.push_back(ArgFormula1);

    ODESolver ODE1(ArgFormulas);
    std::vector<double> Point0{0., 65. * TMath::Pi() / 180., 0.};
    ODEPoint ODE1Point0(2, Point0);

    //For Theta0= 65 degrees, T= 4.87863 s, as seen in Alínea a).
    const double T = 4.87863;
    std::vector<ODEPoint> SolPoints3 = ODE1.RK4Solver(ODE1Point0, T / (10000.), 10000 * 10);

    std::vector<double> T1;
    std::vector<double> Theta1;
    std::vector<double> Omega1;
    std::vector<double> E1;
    //std::cout << "RK4Solver Points: " << std::endl; //Uncomment to print points...
    //Collecting values to draw graphs
    for (auto i : SolPoints3)
    {
        //std::cout << i << std::endl; //Uncomment to print points...
        T1.push_back(i.GetTime());
        Theta1.push_back(i.GetX(0) * 180 / TMath::Pi());
        Omega1.push_back(i.GetX(1) * 180 / TMath::Pi());
        E1.push_back(0.5 * 1 * l * l * (i.GetX(1) * i.GetX(1)) + 1 * 9.8 * l * (1 - cos(i.GetX(0))));
    }

    //Theta(Time) graph
    TGraph *G1 = new TGraph(T1.size(), &T1[0], &Theta1[0]);
    G1->SetLineColor(kRed);
    G1->SetLineWidth(2);
    G1->SetMarkerStyle(20);
    G1->SetMarkerSize(0.3);
    G1->SetMarkerColor(kRed);
    G1->SetTitle("#theta(t)");

    //Omega(Theta) graph
    TGraph *G2 = new TGraph(Theta1.size(), &Theta1[0], &Omega1[0]);
    G2->SetLineColor(kBlue);
    G2->SetLineWidth(2);
    G2->SetMarkerStyle(20);
    G2->SetMarkerSize(0.3);
    G2->SetMarkerColor(kBlue);
    G2->SetTitle("#omega(#theta)");

    //Energy(Time) graph
    TGraph *G3 = new TGraph(T1.size(), &T1[0], &E1[0]);
    G3->SetLineColor(kMagenta);
    G3->SetLineWidth(2);
    G3->SetMarkerStyle(20);
    G3->SetMarkerSize(0.3);
    G3->SetMarkerColor(kMagenta);
    G3->SetTitle("Energy(t)");

    //Theta(Time) plot
    TCanvas *C1 = new TCanvas("C1", "Multigraph", 500, 500, 600, 600);
    C1->SetGrid();

    TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(G1, "lp");
    Mg->Draw("A");
    Mg->GetXaxis()->SetTitle("t (s)");
    Mg->GetYaxis()->SetTitle("#theta (degrees)");

    C1->BuildLegend();
    C1->Modified();
    C1->SaveAs("prob1b_theta.pdf", "AP");

    //Omega(Theta) plot
    TCanvas *C2 = new TCanvas("C2", "Multigraph2", 500, 500, 600, 600);
    C2->SetGrid();

    TMultiGraph *Mg2 = new TMultiGraph();
    Mg2->Add(G2, "l");
    Mg2->Draw("A");
    Mg2->GetXaxis()->SetTitle("#theta (degrees)");
    Mg2->GetYaxis()->SetTitle("#omega (degrees s^{-1})");

    C2->BuildLegend();
    C2->Modified();
    C2->SaveAs("prob1b_diagramafase.pdf", "AP");

    //Energy(Time) plot
    TCanvas *C3 = new TCanvas("C3", "Multigraph3", 500, 500, 600, 600);
    C3->SetGrid();

    TMultiGraph *Mg3 = new TMultiGraph();
    Mg3->Add(G3, "l");
    Mg3->Draw("A");
    Mg3->GetXaxis()->SetTitle("t (s)");
    Mg3->GetYaxis()->SetTitle("Energy (J)");

    Mg3->SetMinimum(E1[0] - 50.);
    Mg3->SetMaximum(E1[E1.size() - 1] + 50.);

    C3->BuildLegend();
    C3->Modified();
    C3->SaveAs("prob1b_energia.pdf", "AP");

    return 0;
}
