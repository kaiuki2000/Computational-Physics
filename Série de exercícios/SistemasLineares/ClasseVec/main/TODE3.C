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
    TFormula ArgFormula0("Formula0", "x[3]");
    TFormula ArgFormula1("Formula1", "x[4]");
    TFormula ArgFormula2("Formula2", "0");
    TFormula ArgFormula3("Formula3", "-10.");
    ArgFormulas.push_back(ArgFormula0);
    ArgFormulas.push_back(ArgFormula1);
    ArgFormulas.push_back(ArgFormula2);
    ArgFormulas.push_back(ArgFormula3);

    ODESolver ODE1(ArgFormulas);
    std::vector<double> Point0{0., 0., 500., 5., 0.};
    ODEPoint ODE1Point0(4, Point0);

    std::vector<ODEPoint> SolPoints = ODE1.EulerSolver(ODE1Point0, 1., 10);
    std::vector<ODEPoint> SolPoints2 = ODE1.PredictorCorrectorSolver(ODE1Point0, 1., 10);
    std::vector<ODEPoint> SolPoints3 = ODE1.RK4Solver(ODE1Point0, 1., 10);

    std::vector<double> T1;
    std::vector<double> X1;
    std::vector<double> Y1;
    std::cout << "EulerSolver points: " << std::endl;
    for (auto i : SolPoints)
    {
        std::cout << i << std::endl;
        T1.push_back(i.GetTime());
        X1.push_back(i.GetX(0));
        Y1.push_back(i.GetX(1));
    }
    std::cout << std::endl;

    std::vector<double> T2;
    std::vector<double> X2;
    std::vector<double> Y2;
    std::cout << "PredictorCorrectorSolver points: " << std::endl;
    for (auto i : SolPoints2)
    {
        std::cout << i << std::endl;
        T2.push_back(i.GetTime());
        X2.push_back(i.GetX(0));
        Y2.push_back(i.GetX(1));
    }
    std::cout << std::endl;

    std::vector<double> T3;
    std::vector<double> X3;
    std::vector<double> Y3;
    std::cout << "RK4Solver points: " << std::endl;
    for (auto i : SolPoints3)
    {
        std::cout << i << std::endl;
        T3.push_back(i.GetTime());
        X3.push_back(i.GetX(0));
        Y3.push_back(i.GetX(1));
    }
    std::cout << std::endl;

    TCanvas *C1 = new TCanvas("C1", "Multigraph", 500, 500, 600, 600);
    C1->SetGrid();

    TGraph *G1 = new TGraph(X1.size(), &X1[0], &Y1[0]);
    G1->SetLineColor(kRed);
    G1->SetLineWidth(3);
    G1->SetMarkerStyle(20);
    G1->SetMarkerColor(kRed);
    G1->SetTitle("Euler");

    TGraph *G2 = new TGraph(X2.size(), &X2[0], &Y2[0]);
    G2->SetLineColor(kBlue);
    G2->SetLineWidth(5);
    G2->SetMarkerStyle(20);
    G2->SetMarkerColor(kBlue);
    G2->SetTitle("Predictor-Corrector");

    TGraph *G3 = new TGraph(X3.size(), &X3[0], &Y3[0]);
    G3->SetLineColor(kGreen);
    G3->SetLineWidth(2);
    G3->SetMarkerStyle(20);
    G3->SetMarkerColor(kGreen);
    G3->SetTitle("RK4");

    /*TF1 *F1 = new TF1("F1", "0.5*x*x", 0., 25.);
    TGraph *G4 = new TGraph(F1);
    G4->SetLineColor(kOrange);
    G4->SetLineWidth(3);
    G4->SetMarkerStyle(20);
    G4->SetMarkerColor(kOrange);
    G4->SetTitle("Exact solution");*/

    TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(G1, "lp");
    Mg->Add(G2, "lp");
    Mg->Add(G3, "lp");
    //Mg->Add(G4);
    Mg->Draw("A");
    Mg->GetXaxis()->SetTitle("x-Position (m)");
    Mg->GetYaxis()->SetTitle("y-Position (m)");

    /*Mg->GetXaxis()->SetLimits(T1[0] - 1., T1[4] + 1.);
    Mg->SetMinimum(X1[0] - 1.);
    Mg->SetMaximum(X1[4] + 1.);*/

    C1->BuildLegend();
    C1->Modified();
    C1->SaveAs("Trajetória de teste.eps", "AP");
}
