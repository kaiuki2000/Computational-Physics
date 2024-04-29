#include "ODEPoint.h"
#include "ODESolver.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "TF1.h"

int main()
{
    //Alínea a)
    auto f1 = [](double *x, double *par) {
        return x[2];
    };

    auto f2 = [](double *x, double *par) {
        return 0.;
    };

    // Vector containing the used functions
    vector<TF1> Sist{
        TF1("f1", f1, 0, 1000, 0),
        TF1("f2", f2, 0, 1000, 0),
    };

    // Initial state
    double IState[3] = {0., 40., 0.};

    // Initial point
    ODEPoint P0(2, IState);

    ODESolver solver(Sist);

    //s= 10cm
    std::vector<ODEPoint> SolPoints = solver.ShootingMethodBVPSolver2(P0, 100., 10., 0, 10);

    std::vector<double> X1;
    std::vector<double> Y1;
    std::cout << "ShootingMethodBVPSolver points: (s= 10cm)" << std::endl;
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
    G1->SetTitle("Shooting method s= 10 cm");

    //s= 2cm
    SolPoints = solver.ShootingMethodBVPSolver2(P0, 100., 10., 0, 50);

    X1.clear();
    Y1.clear();

    std::cout << "ShootingMethodBVPSolver points: (s= 2cm)" << std::endl;
    for (auto i : SolPoints)
    {
        std::cout << i << std::endl;
        X1.push_back(i.GetTime());
        Y1.push_back(i.GetX(0));
    }
    std::cout << std::endl;

    TGraph *G2 = new TGraph(X1.size(), &X1[0], &Y1[0]);
    G2->SetLineColor(kTeal);
    G2->SetLineWidth(3);
    G2->SetMarkerStyle(20);
    G2->SetMarkerColor(kTeal);
    G2->SetTitle("Shooting method s= 2 cm");

    TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(G2, "lp");
    Mg->Add(G1, "lp");
    Mg->Draw("A");
    Mg->GetXaxis()->SetTitle("X (cm)");
    Mg->GetYaxis()->SetTitle("T (Degrees Celsius)");

    /*Mg->GetXaxis()->SetLimits(T1[0] - 1., T1[4] + 1.);
    Mg->SetMinimum(X1[0] - 1.);
    Mg->SetMaximum(X1[4] + 1.);*/

    C1->BuildLegend();
    C1->Modified();
    C1->SaveAs("Exercicio74a.pdf", "AP");
    cout << endl;

    //Alínea b)
    const double h = 17.;
    const double k = 206.;
    const double D = 1.01;
    const double Ta = 23.;

    auto f3 = [](double *x, double *par) {
        return x[2];
    };

    auto f4 = [&](double *x, double *par) {
        return (4 * h) / (k * D) * (x[1] - Ta);
    };

    // Vector containing the used functions
    vector<TF1> Sist2{
        TF1("f1", f3, 0, 1000, 0),
        TF1("f2", f4, 0, 1000, 0),
    };

    // Initial state
    double IState2[3] = {0., 40., 0.};

    // Initial point
    ODEPoint P02(2, IState2);

    ODESolver solver2(Sist2);

    //s= 10cm
    std::vector<ODEPoint> SolPoints2 = solver2.ShootingMethodBVPSolver1(P02, 1., 0., 1, 50);

    std::vector<double> X2;
    std::vector<double> Y2;
    std::cout << "ShootingMethodBVPSolver points: (Alínea b) (s= 2cm)" << std::endl;
    for (auto i : SolPoints2)
    {
        std::cout << i << std::endl;
        X2.push_back(i.GetTime());
        Y2.push_back(i.GetX(0));
    }
    std::cout << std::endl;

    TCanvas *C2 = new TCanvas("C2", "Multigraph2", 500, 500, 600, 600);
    C2->SetGrid();

    TGraph *G3 = new TGraph(X2.size(), &X2[0], &Y2[0]);
    G3->SetLineColor(kRed);
    G3->SetLineWidth(3);
    G3->SetMarkerStyle(20);
    G3->SetMarkerColor(kRed);
    G3->SetTitle("Shooting method s= 2 cm");

    TMultiGraph *Mg2 = new TMultiGraph();
    Mg2->Add(G3, "lp");
    Mg2->Draw("A");
    Mg2->GetXaxis()->SetTitle("X (m)");
    Mg2->GetYaxis()->SetTitle("T (Degrees Celsius)");

    C2->BuildLegend();
    C2->Modified();
    C2->SaveAs("Exercicio74b.pdf", "AP");
}