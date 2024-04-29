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
    TFormula ArgFormula1("Formula1", "1");
    ArgFormulas.push_back(ArgFormula0);
    ArgFormulas.push_back(ArgFormula1);

    ODESolver ODE1(ArgFormulas);
    std::vector<double> Point0{0, 0, 0};
    ODEPoint ODE1Point0(2, Point0);

    std::vector<ODEPoint> SolPoints = ODE1.EulerSolver(ODE1Point0, 1, 25);
    std::vector<ODEPoint> SolPoints2 = ODE1.PredictorCorrectorSolver(ODE1Point0, 1, 25);
    std::vector<ODEPoint> SolPoints3 = ODE1.LeapFrogSolver(ODE1Point0, 1, 25);

    std::vector<double> T1;
    std::vector<double> X1;
    for (auto i : SolPoints)
    {
        std::cout << i << std::endl;
        T1.push_back(i.GetTime());
        X1.push_back(i.GetX(0));
    }
    std::cout << std::endl;

    std::vector<double> T2;
    std::vector<double> X2;
    for (auto i : SolPoints2)
    {
        std::cout << i << std::endl;
        T2.push_back(i.GetTime());
        X2.push_back(i.GetX(0));
    }
    std::cout << std::endl;

    std::vector<double> T3;
    std::vector<double> X3;
    for (auto i : SolPoints3)
    {
        std::cout << i << std::endl;
        T3.push_back(i.GetTime());
        X3.push_back(i.GetX(0));
    }
    std::cout << std::endl;

    TCanvas *C1 = new TCanvas("C1", "Multigraph", 500, 500, 600, 600);
    C1->SetGrid();

    TGraph *G1 = new TGraph(T1.size(), &T1[0], &X1[0]);
    G1->SetLineColor(kRed);
    G1->SetLineWidth(3);
    G1->SetMarkerStyle(20);
    G1->SetMarkerColor(kRed);
    G1->SetTitle("Euler");

    TGraph *G2 = new TGraph(T2.size(), &T2[0], &X2[0]);
    G2->SetLineColor(kBlue);
    G2->SetLineWidth(5);
    G2->SetMarkerStyle(20);
    G2->SetMarkerColor(kBlue);
    G2->SetTitle("Predictor-Corrector");

    TGraph *G3 = new TGraph(T3.size(), &T3[0], &X3[0]);
    G3->SetLineColor(kGreen);
    G3->SetLineWidth(4);
    G3->SetMarkerStyle(20);
    G3->SetMarkerColor(kGreen);
    G3->SetTitle("Leap-Frog");

    TF1 *F1 = new TF1("F1", "0.5*x*x", 0., 25.);
    TGraph *G4 = new TGraph(F1);
    G4->SetLineColor(kOrange);
    G4->SetLineWidth(3);
    G4->SetMarkerStyle(20);
    G4->SetMarkerColor(kOrange);
    G4->SetTitle("Exact solution");

    TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(G1, "lp");
    Mg->Add(G2, "lp");
    Mg->Add(G3, "lp");
    Mg->Add(G4);
    Mg->Draw("A");
    Mg->GetXaxis()->SetTitle("Time (s)");
    Mg->GetYaxis()->SetTitle("x-Position (m)");

    /*Mg->GetXaxis()->SetLimits(T1[0] - 1., T1[4] + 1.);
    Mg->SetMinimum(X1[0] - 1.);
    Mg->SetMaximum(X1[4] + 1.);*/

    C1->BuildLegend();
    C1->Modified();
    C1->SaveAs("EulerVsPredictorCorrectorVsLeapFrog.eps", "AP");
}
