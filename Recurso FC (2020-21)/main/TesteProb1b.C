#include "ODEPoint.h"
#include "ODESolver.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TMultiGraph.h"

using namespace std;

//Converts degrees to radians
double Deg2Rad(double deg)
{
    return deg * TMath::Pi() / 180.;
}

//Converts radians to degrees
double Rad2Deg(double rad)
{
    return rad * 180. / TMath::Pi();
}

int main()
{
    //Obtained from the previous question: T = 4.87863;
    const double Period = 4.87863;

    const double l = 5.;
    const double g = 9.8;

    auto f1 = [](double *x, double *par) {
        return x[2];
    };

    auto f2 = [&](double *x, double *par) {
        return -(g / l) * sin(x[1]);
    };

    // Vector containing the used functions
    vector<TF1> Sist{
        TF1("f1", f1, 0, 1000, 0),
        TF1("f2", f2, 0, 1000, 0),
    };

    // Initial state
    double IState[3] = {0., Deg2Rad(65.), 0.};

    // Initial point
    ODEPoint P0(2, IState);

    double h = 0.1;
    double t = 10. * Period;

    ODESolver Solver(Sist);

    //Fourth order Runge-Kutta
    vector<ODEPoint> VecSol = Solver.RK4(P0, h, t);

    std::vector<double> T1;
    std::vector<double> Theta1;
    std::vector<double> Omega1;
    std::vector<double> E1;

    cout << "RK4Points:" << endl;
    for (auto i : VecSol)
    {
        cout << i << endl;
        T1.push_back(i.GetTime());
        Theta1.push_back(Rad2Deg(i.GetX(0)));
        Omega1.push_back(Rad2Deg(i.GetX(1)));
        E1.push_back(0.5 * 1 * l * l * (i.GetX(1) * i.GetX(1)) + 1 * 9.8 * l * (1 - cos(i.GetX(0))));
    }
    std::cout << std::endl;

    //Theta(t) graph
    TCanvas *C1 = new TCanvas("C1", "Multigraph", 500, 500, 600, 600);
    C1->SetGrid();

    TGraph *G1 = new TGraph(T1.size(), &T1[0], &Theta1[0]);
    G1->SetLineColor(kRed - 3);
    G1->SetLineWidth(3);
    G1->SetMarkerStyle(20);
    G1->SetMarkerColor(kRed - 3);
    G1->SetTitle("Runge-Kutta 4: #theta(t)");

    TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(G1);
    Mg->Draw("AL");
    Mg->GetXaxis()->SetTitle("Time (s)");
    Mg->GetYaxis()->SetTitle("#theta (Degrees)");

    C1->BuildLegend();
    C1->Modified();
    C1->SaveAs("TesteProb1b_theta.pdf", "A");

    //Theta(Omega) graph
    TCanvas *C2 = new TCanvas("C2", "Multigraph", 500, 500, 600, 600);
    C2->SetGrid();

    TGraph *G2 = new TGraph(Omega1.size(), &Omega1[0], &Theta1[0]);
    G2->SetLineColor(kGreen - 3);
    G2->SetLineWidth(3);
    G2->SetMarkerStyle(20);
    G2->SetMarkerColor(kGreen - 3);
    G2->SetTitle("Runge-Kutta 4: #theta(#omega)");

    TMultiGraph *Mg2 = new TMultiGraph();
    Mg2->Add(G2);
    Mg2->Draw("AL");
    Mg2->GetXaxis()->SetTitle("#omega (Degrees s^{-1})");
    Mg2->GetYaxis()->SetTitle("#theta (Degrees)");

    Mg2->GetXaxis()->SetLimits(-90., 90.);
    Mg2->SetMinimum(-90.);
    Mg2->SetMaximum(90.);

    C2->BuildLegend();
    C2->Modified();
    C2->SaveAs("TesteProb1b_diagramafase.pdf", "A");

    //Energy(t)
    TCanvas *C3 = new TCanvas("C3", "Multigraph", 500, 500, 600, 600);
    C3->SetGrid();

    TGraph *G3 = new TGraph(T1.size(), &T1[0], &E1[0]);
    G3->SetLineColor(kYellow - 3);
    G3->SetLineWidth(3);
    G3->SetMarkerStyle(20);
    G3->SetMarkerColor(kYellow - 3);
    G3->SetTitle("Runge-Kutta 4: Energy(t)");

    TMultiGraph *Mg3 = new TMultiGraph();
    Mg3->Add(G3);
    Mg3->Draw("AL");
    Mg3->GetXaxis()->SetTitle("Time (s)");
    Mg3->GetYaxis()->SetTitle("Energy (J)");
    Mg3->GetXaxis()->SetLabelSize(0.03);
    Mg3->GetYaxis()->SetLabelSize(0.03);

    Mg3->SetMinimum(28.);
    Mg3->SetMaximum(29.);

    C3->BuildLegend();
    C3->Modified();
    C3->SaveAs("TesteProb1b_energia.pdf", "A");

    Sist.clear();

    return 0;
}
