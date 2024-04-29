#include "ODEPoint.h"
#include "ODESolver.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "TF1.h"

int main()
{
    //Testing ODESolver class: Leap-Frog method
    std::vector<TFormula> ArgFormulas;
    TFormula ArgFormula0("Formula0", "x[2]");
    TFormula ArgFormula1("Formula1", "-x[1]");

    ArgFormulas.push_back(ArgFormula0);
    ArgFormulas.push_back(ArgFormula1);

    ODESolver ODE1(ArgFormulas);
    std::vector<double> Point0{0., 1., 0.};
    ODEPoint ODE1Point0(2, Point0);

    std::vector<ODEPoint> SolPoints2 = ODE1.LeapFrogSolver(ODE1Point0, 0.001, 20000);
    std::vector<ODEPoint> SolPoints3 = ODE1.RK4Solver(ODE1Point0, 0.001, 20000);

    std::vector<double> T2;
    std::vector<double> X2;
    std::vector<double> dX2;
    std::cout << "LeapFrogSolver points: " << std::endl;
    for (auto i : SolPoints2)
    {
        std::cout << i << std::endl;
        T2.push_back(i.GetTime());
        X2.push_back(i.GetX(0));
        dX2.push_back(i.GetX(1));
    }
    std::cout << std::endl;

    std::vector<double> T3;
    std::vector<double> X3;
    std::vector<double> dX3;
    std::cout << "RK4Solver points: " << std::endl;
    for (auto i : SolPoints3)
    {
        std::cout << i << std::endl;
        T3.push_back(i.GetTime());
        X3.push_back(i.GetX(0));
        dX3.push_back(i.GetX(1));
    }
    std::cout << std::endl;

    TCanvas *C1 = new TCanvas("C1", "Multigraph", 500, 500, 600, 600);
    C1->SetGrid();

    TGraph *G2 = new TGraph(T2.size(), &T2[0], &X2[0]);
    G2->SetLineColor(kGreen);
    G2->SetLineWidth(5);
    G2->SetMarkerStyle(20);
    G2->SetMarkerColor(kGreen);
    G2->SetTitle("Leap-Frog");

    TGraph *G3 = new TGraph(T3.size(), &T3[0], &X3[0]);
    G3->SetLineColor(kRed);
    G3->SetLineWidth(2);
    G3->SetMarkerStyle(20);
    G3->SetMarkerSize(0.3);
    G3->SetMarkerColor(kRed);
    G3->SetTitle("RK4");

    TF1 *F1 = new TF1("F1", "cos(x)", 0., 25.);
    TGraph *G4 = new TGraph(F1);
    G4->SetLineColor(kOrange);
    G4->SetLineWidth(3);
    G4->SetMarkerStyle(20);
    G4->SetMarkerColor(kOrange);
    G4->SetTitle("Exact solution");

    TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(G2, "lp");
    Mg->Add(G3, "lp");
    Mg->Add(G4);
    Mg->Draw("A");
    Mg->GetXaxis()->SetTitle("Time (s)");
    Mg->GetYaxis()->SetTitle("Position (m)");

    /*Mg->GetXaxis()->SetLimits(T1[0] - 1., T1[4] + 1.);
    Mg->SetMinimum(X1[0] - 1.);
    Mg->SetMaximum(X1[4] + 1.);*/

    C1->BuildLegend();
    C1->Modified();
    C1->SaveAs("ExODEOscilações.eps", "AP");
}
