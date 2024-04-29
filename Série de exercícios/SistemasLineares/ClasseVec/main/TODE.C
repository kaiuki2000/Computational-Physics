#include "ODEPoint.h"
#include "ODESolver.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "TF1.h"

int main()
{
    //Testing ODEPoint class
    /*std::vector<double> Vec;
    Vec.push_back(0);
    Vec.push_back(1);
    Vec.push_back(2);

    ODEPoint A(2, Vec);
    std::cout << A << std::endl;

    ODEPoint B(A);
    std::cout << B << std::endl;

    std::cout << (B * 2) << std::endl;

    std::cout << (A + (B * 2)) << std::endl;

    std::cout << (A - (B * 2)) << std::endl;

    std::cout << std::endl;
    double cArray[3] = {5, 6, 7};
    ODEPoint C(2, cArray);

    std::cout << C << std::endl;
    C = A;
    std::cout << C << std::endl;

    std::cout << std::endl;
    for (int i = 0; i < 4; i++)
        std::cout << C[i] << std::endl;
    std::cout << std::endl;*/

    //Testing ODESolver class
    /*std::vector<TFormula> ArgFormulas;
    TFormula ArgFormula0("Formula0", "x[2]");
    TFormula ArgFormula1("Formula0", "x[0]/(x[1]*x[1]+1)");
    ArgFormulas.push_back(ArgFormula0);
    ArgFormulas.push_back(ArgFormula1);

    ODESolver ODE1(ArgFormulas);
    std::vector<double> Point0{0, 2, 10};
    ODEPoint ODE1Point0(2, Point0);

    std::vector<ODEPoint> SolPoints = ODE1.EulerSolver(ODE1Point0, 1, 5);
    std::vector<ODEPoint> SolPoints2 = ODE1.PredictorCorrectorSolver(ODE1Point0, 1, 5);

    for (auto i : SolPoints)
        std::cout << i << std::endl;
    std::cout << std::endl;

    for (auto i : SolPoints2)
        std::cout << i << std::endl;*/

    //Testing ODESolver class
    std::vector<TFormula> ArgFormulas;
    TFormula ArgFormula0("Formula0", "x[1]");
    ArgFormulas.push_back(ArgFormula0);

    ODESolver ODE1(ArgFormulas);
    std::vector<double> Point0{0, 1};
    ODEPoint ODE1Point0(1, Point0);

    std::vector<ODEPoint> SolPoints = ODE1.EulerSolver(ODE1Point0, 0.1, 20);
    std::vector<ODEPoint> SolPoints2 = ODE1.PredictorCorrectorSolver(ODE1Point0, 0.1, 20);
    std::vector<ODEPoint> SolPoints3 = ODE1.RK2Solver(ODE1Point0, 0.1, 20);
    std::vector<ODEPoint> SolPoints4 = ODE1.RK4Solver(ODE1Point0, 0.1, 20);

    std::vector<double> X1;
    std::vector<double> Y1;
    for (auto i : SolPoints)
    {
        std::cout << i << std::endl;
        X1.push_back(i.GetTime());
        Y1.push_back(i.GetX(0));
    }
    std::cout << std::endl;

    std::vector<double> X2;
    std::vector<double> Y2;
    for (auto i : SolPoints2)
    {
        std::cout << i << std::endl;
        X2.push_back(i.GetTime());
        Y2.push_back(i.GetX(0));
    }
    std::cout << std::endl;

    std::vector<double> X3;
    std::vector<double> Y3;
    for (auto i : SolPoints3)
    {
        std::cout << i << std::endl;
        X3.push_back(i.GetTime());
        Y3.push_back(i.GetX(0));
    }
    std::cout << std::endl;

    std::vector<double> X4;
    std::vector<double> Y4;
    for (auto i : SolPoints4)
    {
        std::cout << i << std::endl;
        X4.push_back(i.GetTime());
        Y4.push_back(i.GetX(0));
    }
    std::cout << std::endl;

    //Exact solution values
    TF1 *F1 = new TF1("F1", "exp(x)", 0., 2.);
    std::cout << "Exact solution values: " << std::endl;
    for (int i = 0; i < 21; i++)
        std::cout << "(" << 0.1 * i << ", " << F1->Eval(0.1 * i) << ")" << std::endl;
    std::cout << std::endl;

    TCanvas *C1 = new TCanvas("C1", "Multigraph", 500, 500, 600, 600);
    C1->SetGrid();

    TGraph *G1 = new TGraph(X1.size(), &X1[0], &Y1[0]);
    G1->SetLineColor(kRed);
    G1->SetLineWidth(1);
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
    G3->SetLineWidth(3);
    G3->SetMarkerStyle(20);
    G3->SetMarkerColor(kGreen);
    G3->SetTitle("RK2");

    TGraph *G4 = new TGraph(X4.size(), &X4[0], &Y4[0]);
    G4->SetLineColor(kMagenta - 10);
    G4->SetLineWidth(1);
    G4->SetMarkerStyle(20);
    G4->SetMarkerColor(kMagenta - 10);
    G4->SetTitle("RK4");

    TGraph *G5 = new TGraph(F1);
    G5->SetLineColor(kOrange);
    G5->SetLineWidth(3);
    G5->SetMarkerStyle(20);
    G5->SetMarkerColor(kOrange);
    G5->SetTitle("Exact solution");

    TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(G1, "lp");
    Mg->Add(G2, "lp");
    Mg->Add(G3, "lp");
    Mg->Add(G4, "lp");
    Mg->Add(G5);
    Mg->Draw("A");
    Mg->GetXaxis()->SetTitle("x Axis");
    Mg->GetYaxis()->SetTitle("y Axis");

    /*Mg->GetXaxis()->SetLimits(X1[0] - 1., X1[4] + 1.);
    Mg->SetMinimum(Y1[0] - 1.);
    Mg->SetMaximum(Y1[4] + 1.);*/

    C1->BuildLegend();
    C1->Modified();
    C1->SaveAs("EulerVsPredictorCorrectorVsRK2VsRK4.eps", "AP");
}