#include "ODEPoint.h"
#include "ODESolver.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "TF1.h"

int main()
{
    std::vector<TFormula> ArgFormulas;
    TFormula ArgFormula0("Formula0", "x[2]");
    TFormula ArgFormula1("Formula1", "2*x[1]");
    ArgFormulas.push_back(ArgFormula0);
    ArgFormulas.push_back(ArgFormula1);

    ODESolver ODE1(ArgFormulas);
    std::vector<double> Point0{0., 1., -1.};
    ODEPoint ODE1Point0(2, Point0);

    std::vector<ODEPoint> SolPoints = ODE1.ShootingMethodBVPSolver1(ODE1Point0, 1., 0., 1, 20);

    std::vector<double> X1;
    std::vector<double> Y1;
    std::cout << "ShootingMethodBVPSolver points: " << std::endl;
    for (auto i : SolPoints)
    {
        std::cout << i << std::endl;
        X1.push_back(i.GetTime());
        Y1.push_back(i.GetX(0));
    }
    std::cout << std::endl;

    TCanvas *C1 = new TCanvas("C1", "Multigraph", 500, 500, 600, 600);
    C1->SetGrid();

    TGraph *G1 = new TGraph(X1.size(), &X1[0], &Y1[0]);
    G1->SetLineColor(kRed);
    G1->SetLineWidth(3);
    G1->SetMarkerStyle(20);
    G1->SetMarkerColor(kRed);
    G1->SetTitle("Shooting method");

    TF1 *F1 = new TF1("F1", "0.05581*TMath::Exp(sqrt(2)*x)+0.94419*TMath::Exp(-1*sqrt(2)*x)", 0., 1.);
    TGraph *G2 = new TGraph(F1);
    G2->SetLineColor(kOrange);
    G2->SetLineWidth(3);
    G2->SetMarkerStyle(20);
    G2->SetMarkerColor(kOrange);
    G2->SetTitle("Exact solution");

    TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(G1, "lp");
    Mg->Add(G2);
    Mg->Draw("A");
    Mg->GetXaxis()->SetTitle("X");
    Mg->GetYaxis()->SetTitle("Y");

    /*Mg->GetXaxis()->SetLimits(T1[0] - 1., T1[4] + 1.);
    Mg->SetMinimum(X1[0] - 1.);
    Mg->SetMaximum(X1[4] + 1.);*/

    C1->BuildLegend();
    C1->Modified();
    C1->SaveAs("BVP Testing.eps", "AP");
}
