#include "ODEpoint.h"
#include "ODEsolver.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TMultiGraph.h"

// Declaracao da funcao Draw
//void Draw(vector<ODEpoint>, int);

int main()
{
    auto f1 = [](double *x, double *par) {
        return x[2];
    };

    auto f2 = [](double *x, double *par) {
        return -x[1];
    };

    // Vetor com as
    vector<TF1> Sist{
        TF1("f1", f1, 0, 1000, 0),
        TF1("f2", f2, 0, 1000, 0),
    };

    // estado inicial
    double ei[3] = {0., 1., 0.};

    // ponto inicial
    ODEpoint P0(2, ei);

    double h = 0.1;
    double T = 20.;

    ODEsolver solver(Sist);

    vector<ODEpoint> vsol = solver.RK3(P0, h, T);

    std::vector<double> T1;
    std::vector<double> X1;
    for (auto i : vsol)
    {
        cout << i << endl;
        T1.push_back(i.T());
        X1.push_back(i.X(0));
    }
    std::cout << std::endl;

    TCanvas *C1 = new TCanvas("C1", "Multigraph", 500, 500, 600, 600);
    C1->SetGrid();

    TGraph *G1 = new TGraph(T1.size(), &T1[0], &X1[0]);
    G1->SetLineColor(kGreen);
    G1->SetLineWidth(2);
    G1->SetMarkerStyle(20);
    G1->SetMarkerColor(kGreen);
    G1->SetTitle("RK3");

    TF1 *F1 = new TF1("F1", "cos(x)", 0., 20.);
    TGraph *G4 = new TGraph(F1);
    G4->SetLineColor(kOrange);
    G4->SetLineWidth(3);
    G4->SetMarkerStyle(20);
    G4->SetMarkerColor(kOrange);
    G4->SetTitle("Exact solution");

    TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(G1);
    Mg->Add(G4);
    Mg->Draw("ALP");
    Mg->GetXaxis()->SetTitle("Time (s)");
    Mg->GetYaxis()->SetTitle("Position (m)");

    C1->BuildLegend();
    C1->Modified();
    C1->SaveAs("ExODEOscilações.eps", "AP");

    //Draw(vsol, 90);

    Sist.clear();

    return 0;
}
