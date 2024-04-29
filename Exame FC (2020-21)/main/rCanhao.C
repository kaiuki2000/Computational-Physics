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
    TFormula ArgFormula3("Formula3", "-9.81");
    ArgFormulas.push_back(ArgFormula0);
    ArgFormulas.push_back(ArgFormula1);
    ArgFormulas.push_back(ArgFormula2);
    ArgFormulas.push_back(ArgFormula3);

    ODESolver ODE1(ArgFormulas);
    std::vector<double> Point0{0., 0., 0., 720. * sqrt(3.) / 2., 720. * 1. / 2.};
    ODEPoint ODE1Point0(4, Point0);

    std::vector<ODEPoint> SolPoints = ODE1.RK4Solver(ODE1Point0, 720. / (9.81 * 100.), 100);

    std::vector<double> T1;
    std::vector<double> X1;
    std::vector<double> Y1;
    std::cout << "RK4 points: (theta= 30 graus)" << std::endl;
    for (auto i : SolPoints)
    {
        std::cout << i << std::endl;
        T1.push_back(i.GetTime());
        X1.push_back(i.GetX(0));
        Y1.push_back(i.GetX(1));
    }
    std::cout << std::endl;

    TCanvas *C1 = new TCanvas("C1", "Multigraph", 500, 500, 600, 600);
    C1->SetGrid();

    TGraph *G1 = new TGraph(X1.size(), &X1[0], &Y1[0]);
    G1->SetLineColor(kRed);
    G1->SetLineWidth(3);
    G1->SetMarkerStyle(20);
    G1->SetMarkerColor(kRed);
    G1->SetTitle("RK4");

    /*TF1 *F1 = new TF1("F1", "0.5*x*x", 0., 25.);
    TGraph *G4 = new TGraph(F1);
    G4->SetLineColor(kOrange);
    G4->SetLineWidth(3);
    G4->SetMarkerStyle(20);
    G4->SetMarkerColor(kOrange);
    G4->SetTitle("Exact solution");*/

    TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(G1, "lp");
    //Mg->Add(G4);
    Mg->Draw("A");
    Mg->GetXaxis()->SetTitle("x-Position (m)");
    Mg->GetYaxis()->SetTitle("y-Position (m)");

    /*Mg->GetXaxis()->SetLimits(T1[0] - 1., T1[4] + 1.);
    Mg->SetMinimum(X1[0] - 1.);
    Mg->SetMaximum(X1[4] + 1.);*/

    std::cout << "Quando lançado com um ângulo de 30 graus (com a horizontal), o corpo aterra a uma distância x= " << X1[X1.size() - 1] << " m\n"
              << std::endl;

    C1->BuildLegend();
    C1->Modified();
    C1->SaveAs("TrajetóriaRK4.pdf", "AP");

    auto F_Lambda = [&](double *theta, double *par) {
        std::vector<double> Point1{0., 0., 0., 720. * cos(theta[0] * TMath::Pi() / 180.), 720. * sin(theta[0] * TMath::Pi() / 180.)};
        ODEPoint ODE1Point1(4, Point1);

        std::vector<ODEPoint> SolPoints12 = ODE1.RK4Solver(ODE1Point1, (2. * 720. * sin(theta[0] * TMath::Pi() / 180.)) / (9.81 * 100.), 100);

        return SolPoints12[SolPoints12.size() - 1][1] - 200.;
    };

    //Ângulo varia entre 0 graus e 90 graus
    TF1 *F = new TF1("F", F_Lambda, 0., 90., 0);

    RootFinder FRoot(0., 90., F);
    double ArgTheta0 = 15.;
    double ThetaResult = 0.;

    FRoot.QuasiN(1e-5, ArgTheta0, 100, 1e-5, ThetaResult);

    std::cout << "\nO ângulo que faz com que o alcance seja x=200 m é theta= " << ThetaResult << " graus, ou o seu complementar: (90 - theta)= "
              << 90 - ThetaResult << " graus" << std::endl;
    std::cout << "\nVerificação: " << std::endl;

    std::vector<TFormula> ArgFormulas2;
    TFormula ArgFormula02("Formula02", "x[3]");
    TFormula ArgFormula12("Formula12", "x[4]");
    TFormula ArgFormula22("Formula22", "0");
    TFormula ArgFormula32("Formula32", "-9.81");
    ArgFormulas2.push_back(ArgFormula02);
    ArgFormulas2.push_back(ArgFormula12);
    ArgFormulas2.push_back(ArgFormula22);
    ArgFormulas2.push_back(ArgFormula32);

    ODESolver ODE12(ArgFormulas2);
    std::vector<double> Point02{0., 0., 0., 720. * cos(ThetaResult * TMath::Pi() / 180.), 720. * sin(ThetaResult * TMath::Pi() / 180.)};
    ODEPoint ODE1Point02(4, Point02);

    std::vector<ODEPoint> SolPoints2 = ODE12.RK4Solver(ODE1Point02, (2. * 720. * sin(ThetaResult * TMath::Pi() / 180.)) / (9.81 * 100.), 100);

    std::vector<double> T12;
    std::vector<double> X12;
    std::vector<double> Y12;
    std::cout << "RK4 points: (theta= " << ThetaResult << " graus)" << std::endl;
    for (auto i : SolPoints2)
    {
        std::cout << i << std::endl;
        T12.push_back(i.GetTime());
        X12.push_back(i.GetX(0));
        Y12.push_back(i.GetX(1));
    }
    std::cout << std::endl;

    return 0;
}
