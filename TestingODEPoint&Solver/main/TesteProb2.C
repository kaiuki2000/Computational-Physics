#include "DataPoints.h"
#include "NevilleInterpolator.h"
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
    //Calculation of c:
    int n = 4;
    double RVec[n] = {5.75, 12.00, 18.00, 30.00};
    double cVec[n] = {1.2e-3, 1.8e-8, 2.6e-3, 4.0e-3};

    DataPoints Data1(n, RVec, cVec);
    cout << "Pontos usados na interpolação: " << endl;
    Data1.Print("Non-existent");

    //Using NevilleInterpolator:
    NevilleInterpolator NLI_Data1(n, RVec, cVec);

    //Calculating c at R= 15 cm, using Neville interpolation:
    const double c = NLI_Data1.Interpolate(15.);

    cout << "\nRecorrendo à interpolação de Neville, obtive o seguinte valor para c: c= " << c << " Kg/s.\n"
         << endl;

    //Solving differential equation:
    //Obtained from the previous question: T = 4.87863;
    const double Period = 4.87863;

    const double l = 5.;
    const double g = 9.8;

    auto f1 = [](double *x, double *par) {
        return x[2];
    };

    auto f2 = [&](double *x, double *par) {
        return -(g / l) * sin(x[1]) - c * x[2];
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
    std::vector<double> V1;
    std::vector<double> E1;

    std::vector<double> TExp1;
    std::vector<double> Exp1;

    double Ei = 0.;
    double Ef = 0.;

    cout << "RK4Points:" << endl;
    for (auto i : VecSol)
    {
        cout << i << endl;
        T1.push_back(i.GetTime());
        Theta1.push_back(Rad2Deg(i.GetX(0)));
        Omega1.push_back(Rad2Deg(i.GetX(1)));
        V1.push_back(i.GetX(1) * l);
        E1.push_back(0.5 * 1 * l * l * (i.GetX(1) * i.GetX(1)) + 1 * 9.8 * l * (1 - cos(i.GetX(0))));

        if (fabs(i.GetX(1)) < 0.1 && Rad2Deg(i.GetX(0)) > 0)
        {
            TExp1.push_back(i.GetTime());
            Exp1.push_back(Rad2Deg(i.GetX(0)));
        }

        if (fabs(i.GetTime() - 5.5) < 1e-5)
            Ei = 0.5 * 1 * l * l * (i.GetX(1) * i.GetX(1)) + 1 * 9.8 * l * (1 - cos(i.GetX(0)));
        if (fabs(i.GetTime() - 7.2) < 1e-5)
            Ef = 0.5 * 1 * l * l * (i.GetX(1) * i.GetX(1)) + 1 * 9.8 * l * (1 - cos(i.GetX(0)));
    }
    std::cout << std::endl;

    //Theta(t) graph + exponential decay graph
    TCanvas *C1 = new TCanvas("C1", "Multigraph", 500, 500, 600, 600);
    C1->SetGrid();

    TGraph *G1 = new TGraph(T1.size(), &T1[0], &Theta1[0]);
    G1->SetLineColor(kRed - 3);
    G1->SetLineWidth(3);
    G1->SetMarkerStyle(20);
    G1->SetMarkerColor(kRed - 3);
    G1->SetTitle("Runge-Kutta 4: #theta(t)");

    TGraph *G2 = new TGraph(TExp1.size(), &TExp1[0], &Exp1[0]);
    G2->SetLineColor(kOrange - 3);
    G2->SetLineWidth(3);
    G2->SetMarkerStyle(20);
    G2->SetMarkerColor(kOrange - 3);
    G2->SetTitle("Runge-Kutta 4: #theta(t) Maxima");

    //Exponential model used to fit the data set (angular position maxima, in this case)
    auto ExpFit = new TF1("ExpFit", "TMath::Exp(-[0]*x)+[1]");
    G2->Fit(ExpFit);
    cout << endl
         << "Usando a função 'Fit' do Root, obtive o seguinte valor para γ: γ= (0.051348 ± 0.020023) s^-1.\n(Ajuste da forma: Exp(-γ*t)+b)\n"
         << endl;

    TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(G1);
    Mg->Add(G2);
    Mg->Draw("ALP");
    Mg->GetXaxis()->SetTitle("Time (s)");
    Mg->GetYaxis()->SetTitle("#theta (Degrees)");

    C1->BuildLegend(0.6, 0.1, 0.9, 0.3);
    C1->Modified();
    C1->SaveAs("TesteProb2_theta.pdf", "A");

    //Theta(Omega) graph
    TCanvas *C2 = new TCanvas("C2", "Multigraph", 500, 500, 600, 600);
    C2->SetGrid();

    TGraph *G3 = new TGraph(Omega1.size(), &Omega1[0], &Theta1[0]);
    G3->SetLineColor(kGreen - 3);
    G3->SetLineWidth(3);
    G3->SetMarkerStyle(20);
    G3->SetMarkerColor(kGreen - 3);
    G3->SetTitle("Runge-Kutta 4: #theta(#omega)");

    TMultiGraph *Mg2 = new TMultiGraph();
    Mg2->Add(G3);
    Mg2->Draw("AL");
    Mg2->GetXaxis()->SetTitle("#omega (Degrees s^{-1})");
    Mg2->GetYaxis()->SetTitle("#theta (Degrees)");

    Mg2->GetXaxis()->SetLimits(-90., 90.);
    Mg2->SetMinimum(-90.);
    Mg2->SetMaximum(90.);

    C2->BuildLegend();
    C2->Modified();
    C2->SaveAs("TesteProb2_diagramafase.pdf", "A");

    //Linear velocity(t)
    TCanvas *C3 = new TCanvas("C3", "Multigraph", 500, 500, 600, 600);
    C3->SetGrid();

    TGraph *G4 = new TGraph(T1.size(), &T1[0], &V1[0]);
    G4->SetLineColor(kTeal + 3);
    G4->SetLineWidth(3);
    G4->SetMarkerStyle(20);
    G4->SetMarkerColor(kTeal + 3);
    G4->SetTitle("Runge-Kutta 4: Linear velocity(t)");

    TMultiGraph *Mg3 = new TMultiGraph();
    Mg3->Add(G4);
    Mg3->Draw("AL");
    Mg3->GetXaxis()->SetTitle("Time (s)");
    Mg3->GetYaxis()->SetTitle("v (m/s)");
    Mg3->GetXaxis()->SetLabelSize(0.03);
    Mg3->GetYaxis()->SetLabelSize(0.03);

    C3->BuildLegend(0.6, 0.1, 0.9, 0.3);
    C3->Modified();
    C3->SaveAs("TesteProb2_velocidade.pdf", "A");

    //Energy(t)
    TCanvas *C4 = new TCanvas("C4", "Multigraph", 500, 500, 600, 600);
    C4->SetGrid();

    TGraph *G5 = new TGraph(T1.size(), &T1[0], &E1[0]);
    G5->SetLineColor(kYellow - 3);
    G5->SetLineWidth(3);
    G5->SetMarkerStyle(20);
    G5->SetMarkerColor(kYellow - 3);
    G5->SetTitle("Runge-Kutta 4: Energy(t)");

    TMultiGraph *Mg4 = new TMultiGraph();
    Mg4->Add(G5);
    Mg4->Draw("AL");
    Mg4->GetXaxis()->SetTitle("Time (s)");
    Mg4->GetYaxis()->SetTitle("Energy (J)");
    Mg4->GetXaxis()->SetLabelSize(0.03);
    Mg4->GetYaxis()->SetLabelSize(0.03);

    C4->BuildLegend();
    C4->Modified();
    C4->SaveAs("TesteProb2_energia.pdf", "A");

    cout << "\nA energia perdida por atuação da força de atrito no intervalo [5.5, 7.2]s foi: ΔE = |E(t= 7.2s) - E(t= 5.5s)| = |" << Ef << " - " << Ei << "| = "
         << fabs(Ef - Ei) << " J." << endl;

    Sist.clear();

    return (0);
}