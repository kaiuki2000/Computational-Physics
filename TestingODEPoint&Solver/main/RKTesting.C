#include "ODEPoint.h"
#include "ODESolver.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TMultiGraph.h"

int main()
{
    auto f1 = [](double *x, double *par) {
        return x[2];
    };

    auto f2 = [](double *x, double *par) {
        return -x[1];
    };

    // Vector containing the used functions
    vector<TF1> Sist{
        TF1("f1", f1, 0, 1000, 0),
        TF1("f2", f2, 0, 1000, 0),
    };

    // Initial state
    double IState[3] = {0., 1., 0.};

    // Initial point
    ODEPoint P0(2, IState);

    double h = 0.1;
    double T = 20.;

    ODESolver solver(Sist);

    //RK3
    vector<ODEPoint> vsol = solver.RK3(P0, h, T);

    std::vector<double> T1;
    std::vector<double> X1;

    cout << "RK3Points:" << endl;
    for (auto i : vsol)
    {
        cout << i << endl;
        T1.push_back(i.GetTime());
        X1.push_back(i.GetX(0));
    }
    std::cout << std::endl;

    TCanvas *C1 = new TCanvas("C1", "Multigraph", 500, 500, 600, 600);
    C1->SetGrid();

    TGraph *G1 = new TGraph(T1.size(), &T1[0], &X1[0]);
    G1->SetLineColor(kGreen);
    G1->SetLineWidth(12);
    G1->SetMarkerStyle(20);
    G1->SetMarkerColor(kGreen);
    G1->SetTitle("RK3");

    //RK4
    vsol = solver.RK4(P0, h, T);

    T1.clear();
    X1.clear();

    cout << "RK4Points:" << endl;
    for (auto i : vsol)
    {
        cout << i << endl;
        T1.push_back(i.GetTime());
        X1.push_back(i.GetX(0));
    }
    std::cout << std::endl;

    TGraph *G2 = new TGraph(T1.size(), &T1[0], &X1[0]);
    G2->SetLineColor(kRed);
    G2->SetLineWidth(8);
    G2->SetMarkerStyle(20);
    G2->SetMarkerColor(kRed);
    G2->SetTitle("RK4");

    //RK2
    vsol = solver.RK2(P0, h, T);

    T1.clear();
    X1.clear();

    cout << "RK2Points:" << endl;
    for (auto i : vsol)
    {
        cout << i << endl;
        T1.push_back(i.GetTime());
        X1.push_back(i.GetX(0));
    }
    std::cout << std::endl;

    TGraph *G3 = new TGraph(T1.size(), &T1[0], &X1[0]);
    G3->SetLineColor(kBlue);
    G3->SetLineWidth(4);
    G3->SetMarkerStyle(20);
    G3->SetMarkerColor(kBlue);
    G3->SetTitle("RK3");

    TF1 *F1 = new TF1("F1", "cos(x)", 0., T);
    F1->SetNpx(int(T / h));
    TGraph *G4 = new TGraph(F1);
    G4->SetLineColor(kOrange);
    G4->SetLineWidth(2);
    G4->SetMarkerStyle(20);
    G4->SetMarkerColor(kOrange);
    G4->SetTitle("Exact solution");

    TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(G1);
    Mg->Add(G2);
    Mg->Add(G3);
    Mg->Add(G4);
    Mg->Draw("AL");
    Mg->GetXaxis()->SetTitle("Time (s)");
    Mg->GetYaxis()->SetTitle("Position (m)");

    C1->BuildLegend();
    C1->Modified();
    C1->SaveAs("RK2&3&4Testing.pdf", "A");

    Sist.clear();

    return 0;
}
