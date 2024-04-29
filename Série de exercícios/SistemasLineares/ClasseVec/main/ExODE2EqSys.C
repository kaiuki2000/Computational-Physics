#include "ODEPoint.h"
#include "ODESolver.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "TF1.h"

int main()
{
    //Testing ODESolver class
    std::vector<TFormula> ArgFormulas;
    TFormula ArgFormula0("Formula0", "cos(x[0])-x[2]");
    TFormula ArgFormula1("Formula1", "sin(x[0])+x[1]");
    ArgFormulas.push_back(ArgFormula0);
    ArgFormulas.push_back(ArgFormula1);

    ODESolver ODE1(ArgFormulas);
    std::vector<double> Point0{0, 0, 0};
    ODEPoint ODE1Point0(2, Point0);

    std::vector<ODEPoint> SolPoints = ODE1.EulerSolver(ODE1Point0, 0.1, 20);
    std::vector<ODEPoint> SolPoints2 = ODE1.PredictorCorrectorSolver(ODE1Point0, 0.1, 20);
    std::vector<ODEPoint> SolPoints3 = ODE1.RK2Solver(ODE1Point0, 0.1, 20);
    std::vector<ODEPoint> SolPoints4 = ODE1.PredictorCorrectorSolver(ODE1Point0, 0.1, 20);

    std::vector<double> X1;
    std::vector<double> Y1;
    std::cout << "EulerSolver points: " << std::endl;
    for (auto i : SolPoints)
    {
        std::cout << i << std::endl;
        X1.push_back(i.GetTime());
        Y1.push_back(i.GetX(0));
    }
    std::cout << std::endl;

    std::vector<double> X2;
    std::vector<double> Y2;
    std::cout << "PredictorCorrectorSolver points: " << std::endl;
    for (auto i : SolPoints2)
    {
        std::cout << i << std::endl;
        X2.push_back(i.GetTime());
        Y2.push_back(i.GetX(0));
    }
    std::cout << std::endl;

    std::vector<double> X3;
    std::vector<double> Y3;
    std::cout << "RK2Solver points: " << std::endl;
    for (auto i : SolPoints3)
    {
        std::cout << i << std::endl;
        X3.push_back(i.GetTime());
        Y3.push_back(i.GetX(0));
    }
    std::cout << std::endl;

    std::vector<double> X4;
    std::vector<double> Y4;
    std::vector<double> Z4;
    std::cout << "RK4Solver points: " << std::endl;
    for (auto i : SolPoints4)
    {
        std::cout << i << std::endl;
        X4.push_back(i.GetTime());
        Y4.push_back(i.GetX(0));
        Z4.push_back(i.GetX(1));
    }
    std::cout << std::endl;

    TCanvas *C1 = new TCanvas("C1", "Multigraph", 500, 500, 600, 600);
    C1->SetGrid();

    TGraph *G1 = new TGraph(X1.size(), &X1[0], &Y1[0]);
    G1->SetLineColor(kSpring);
    G1->SetLineWidth(1);
    G1->SetMarkerStyle(20);
    G1->SetMarkerColor(kSpring);
    G1->SetTitle("Euler");

    TGraph *G2 = new TGraph(X2.size(), &X2[0], &Y2[0]);
    G2->SetLineColor(kBlue);
    G2->SetLineWidth(5);
    G2->SetMarkerStyle(20);
    G2->SetMarkerColor(kBlue);
    G2->SetTitle("Predictor-Corrector");

    TGraph *G3 = new TGraph(X3.size(), &X3[0], &Y3[0]);
    G3->SetLineColor(kRed);
    G3->SetLineWidth(3);
    G3->SetMarkerStyle(20);
    G3->SetMarkerColor(kRed);
    G3->SetTitle("RK2");

    TGraph *G4 = new TGraph(X4.size(), &X4[0], &Y4[0]);
    G4->SetLineColor(kMagenta - 7);
    G4->SetLineWidth(2);
    G4->SetMarkerStyle(20);
    G4->SetMarkerColor(kMagenta - 7);
    G4->SetTitle("y(x)");

    TGraph *G5 = new TGraph(X4.size(), &X4[0], &Z4[0]);
    G5->SetLineColor(kMagenta + 7);
    G5->SetLineWidth(2);
    G5->SetMarkerStyle(20);
    G5->SetMarkerColor(kMagenta + 7);
    G5->SetTitle("z(x)");

    TMultiGraph *Mg = new TMultiGraph();
    //Mg->Add(G1, "lp");
    //Mg->Add(G2, "lp");
    //Mg->Add(G3, "lp");
    Mg->Add(G4, "lp");
    Mg->Add(G5, "lp");
    Mg->Draw("A");
    Mg->GetXaxis()->SetTitle("x");
    Mg->GetYaxis()->SetTitle("y/z");

    C1->BuildLegend();
    C1->Modified();
    C1->SaveAs("ExODE2EqSys.eps", "AP");
}