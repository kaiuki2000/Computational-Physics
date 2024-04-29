#include "ODEPoint.h"
#include "ODESolver.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "TF1.h"

int main()
{
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
    double IState[3] = {0., 30., 1.};

    // Initial point
    ODEPoint P0(2, IState);

    ODESolver solver(Sist);

    std::vector<ODEPoint> SolPoints = solver.ShootingMethodBVPSolver2(P0, 1., 10., 0, 20);

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

    TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(G1, "lp");
    Mg->Draw("A");
    Mg->GetXaxis()->SetTitle("X");
    Mg->GetYaxis()->SetTitle("Y");

    /*Mg->GetXaxis()->SetLimits(T1[0] - 1., T1[4] + 1.);
    Mg->SetMinimum(X1[0] - 1.);
    Mg->SetMaximum(X1[4] + 1.);*/

    C1->BuildLegend();
    C1->Modified();
    C1->SaveAs("BoundaryConditionsTesting2.pdf", "AP");
}
