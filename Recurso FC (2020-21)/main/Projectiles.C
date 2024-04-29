#include "ODEPoint.h"
#include "ODESolver.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "TF1.h"

int main()
{

    //Vou considerar velocidade inicial 72 m/s e ângulo de 30 graus com a horizontal
    std::vector<double> Times;
    std::vector<double> Ranges;

    auto f1 = [](double *x, double *par) {
        return x[3];
    };

    auto f2 = [&](double *x, double *par) {
        return x[4];
    };

    auto f3 = [](double *x, double *par) {
        return -par[0] * x[3];
    };

    auto f4 = [&](double *x, double *par) {
        return -9.81 - par[0] * x[4];
    };

    // Vector containing the used functions
    vector<TF1> Sist{
        TF1("f1", f1, 0, 1000, 0),
        TF1("f2", f2, 0, 1000, 0),
        TF1("f3", f3, 0, 1000, 1),
        TF1("f4", f4, 0, 1000, 1),
    };

    //k=0
    Sist[2].SetParameter(0, 0.);
    Sist[3].SetParameter(0, 0.);

    // Initial state
    double IState[5] = {0., 0., 0., 72. * sqrt(3.) / 2., 72. * 1. / 2.};

    // Initial point
    ODEPoint P0(4, IState);

    //Step: h = 0.01
    double h = 0.01;
    double t = 72. / 9.81;

    ODESolver Solver(Sist);

    //Fourth order Runge-Kutta
    vector<ODEPoint> VecSol = Solver.RK4(P0, h, t);

    std::vector<double> T1;
    std::vector<double> X1;
    std::vector<double> Y1;
    std::vector<double> E1;
    std::cout << "RK4 Points: (k=0)" << std::endl;
    for (auto i : VecSol)
    {
        std::cout << i << std::endl;
        T1.push_back(i.GetTime());
        X1.push_back(i.GetX(0));
        Y1.push_back(i.GetX(1));
        E1.push_back(0.5 * 100 * (i.GetX(2) * i.GetX(2) + i.GetX(3) * i.GetX(3)) + 100 * 9.81 * i.GetX(1));
    }
    std::cout << std::endl;
    Times.push_back(T1[T1.size() - 1]);
    Ranges.push_back(X1[X1.size() - 1]);

    TGraph *G1 = new TGraph(X1.size(), &X1[0], &Y1[0]);
    G1->SetLineColor(kBlack);
    G1->SetLineWidth(2);
    G1->SetMarkerStyle(20);
    G1->SetMarkerSize(0.5);
    G1->SetMarkerColor(kBlack);
    G1->SetTitle("k=0");

    TGraph *G1E = new TGraph(T1.size(), &T1[0], &E1[0]);
    G1E->SetLineColor(kBlack);
    G1E->SetLineWidth(2);
    G1E->SetMarkerStyle(20);
    G1E->SetMarkerSize(0.5);
    G1E->SetMarkerColor(kBlack);
    G1E->SetTitle("k=0");

    //Next graph:
    Sist.clear();
    Sist.push_back(TF1("f1", f1, 0, 1000, 0));
    Sist.push_back(TF1("f2", f2, 0, 1000, 0));
    Sist.push_back(TF1("f3", f3, 0, 1000, 1));
    Sist.push_back(TF1("f4", f4, 0, 1000, 1));

    //k=0.2
    Sist[2].SetParameter(0, 0.2);
    Sist[3].SetParameter(0, 0.2);

    ODESolver ODE2(Sist);

    VecSol.clear();
    VecSol = ODE2.RK4(P0, h, t);

    T1.clear();
    X1.clear();
    Y1.clear();
    E1.clear();
    std::cout << "RK4 Points: (k=0.2)" << std::endl;
    for (auto i : VecSol)
    {
        if (i.GetX(1) > 0)
        {
            std::cout << i << std::endl;
            T1.push_back(i.GetTime());
            X1.push_back(i.GetX(0));
            Y1.push_back(i.GetX(1));
            E1.push_back(0.5 * 100 * (i.GetX(2) * i.GetX(2) + i.GetX(3) * i.GetX(3)) + 100 * 9.81 * i.GetX(1));
        }
    }
    std::cout << std::endl;
    Times.push_back(T1[T1.size() - 1]);
    Ranges.push_back(X1[X1.size() - 1]);

    TGraph *G2 = new TGraph(X1.size(), &X1[0], &Y1[0]);
    G2->SetLineColor(kRed);
    G2->SetLineWidth(2);
    G2->SetMarkerStyle(20);
    G2->SetMarkerSize(0.5);
    G2->SetMarkerColor(kRed);
    G2->SetTitle("k=0.2");

    TGraph *G2E = new TGraph(T1.size(), &T1[0], &E1[0]);
    G2E->SetLineColor(kRed);
    G2E->SetLineWidth(2);
    G2E->SetMarkerStyle(20);
    G2E->SetMarkerSize(0.5);
    G2E->SetMarkerColor(kRed);
    G2E->SetTitle("k=0.2");

    //Next graph:
    Sist.clear();
    Sist.push_back(TF1("f1", f1, 0, 1000, 0));
    Sist.push_back(TF1("f2", f2, 0, 1000, 0));
    Sist.push_back(TF1("f3", f3, 0, 1000, 1));
    Sist.push_back(TF1("f4", f4, 0, 1000, 1));

    //k=1
    Sist[2].SetParameter(0, 1.);
    Sist[3].SetParameter(0, 1.);

    ODESolver ODE3(Sist);

    VecSol.clear();
    VecSol = ODE3.RK4(P0, h, t);

    T1.clear();
    X1.clear();
    Y1.clear();
    E1.clear();
    std::cout << "RK4 Points: (k=1)" << std::endl;
    for (auto i : VecSol)
    {
        if (i.GetX(1) > 0)
        {
            std::cout << i << std::endl;
            T1.push_back(i.GetTime());
            X1.push_back(i.GetX(0));
            Y1.push_back(i.GetX(1));
            E1.push_back(0.5 * 100 * (i.GetX(2) * i.GetX(2) + i.GetX(3) * i.GetX(3)) + 100 * 9.81 * i.GetX(1));
        }
    }
    std::cout << std::endl;
    Times.push_back(T1[T1.size() - 1]);
    Ranges.push_back(X1[X1.size() - 1]);

    TGraph *G3 = new TGraph(X1.size(), &X1[0], &Y1[0]);
    G3->SetLineColor(kGreen);
    G3->SetLineWidth(2);
    G3->SetMarkerStyle(20);
    G3->SetMarkerSize(0.5);
    G3->SetMarkerColor(kGreen);
    G3->SetTitle("k=1");

    TGraph *G3E = new TGraph(T1.size(), &T1[0], &E1[0]);
    G3E->SetLineColor(kGreen);
    G3E->SetLineWidth(2);
    G3E->SetMarkerStyle(20);
    G3E->SetMarkerSize(0.5);
    G3E->SetMarkerColor(kGreen);
    G3E->SetTitle("k=1");

    //Next graph:
    Sist.clear();
    Sist.push_back(TF1("f1", f1, 0, 1000, 0));
    Sist.push_back(TF1("f2", f2, 0, 1000, 0));
    Sist.push_back(TF1("f3", f3, 0, 1000, 1));
    Sist.push_back(TF1("f4", f4, 0, 1000, 1));

    //k=5
    Sist[2].SetParameter(0, 5.);
    Sist[3].SetParameter(0, 5.);

    ODESolver ODE4(Sist);

    VecSol.clear();
    VecSol = ODE4.RK4(P0, h, t);

    T1.clear();
    X1.clear();
    Y1.clear();
    E1.clear();
    std::cout << "RK4 Points: (k=5)" << std::endl;
    for (auto i : VecSol)
    {
        if (i.GetX(1) > 0)
        {
            std::cout << i << std::endl;
            T1.push_back(i.GetTime());
            X1.push_back(i.GetX(0));
            Y1.push_back(i.GetX(1));
            E1.push_back(0.5 * 100 * (i.GetX(2) * i.GetX(2) + i.GetX(3) * i.GetX(3)) + 100 * 9.81 * i.GetX(1));
        }
    }
    std::cout << std::endl;
    Times.push_back(T1[T1.size() - 1]);
    Ranges.push_back(X1[X1.size() - 1]);

    TGraph *G4 = new TGraph(X1.size(), &X1[0], &Y1[0]);
    G4->SetLineColor(kBlue);
    G4->SetLineWidth(2);
    G4->SetMarkerStyle(20);
    G4->SetMarkerSize(0.5);
    G4->SetMarkerColor(kBlue);
    G4->SetTitle("k=5");

    TGraph *G4E = new TGraph(T1.size(), &T1[0], &E1[0]);
    G4E->SetLineColor(kBlue);
    G4E->SetLineWidth(2);
    G4E->SetMarkerStyle(20);
    G4E->SetMarkerSize(0.5);
    G4E->SetMarkerColor(kBlue);
    G4E->SetTitle("k=5");

    //Next graph
    Sist.clear();
    Sist.push_back(TF1("f1", f1, 0, 1000, 0));
    Sist.push_back(TF1("f2", f2, 0, 1000, 0));
    Sist.push_back(TF1("f3", f3, 0, 1000, 1));
    Sist.push_back(TF1("f4", f4, 0, 1000, 1));

    //k=10
    Sist[2].SetParameter(0, 10.);
    Sist[3].SetParameter(0, 10.);

    ODESolver ODE5(Sist);

    VecSol.clear();
    VecSol = ODE5.RK4(P0, h, t);

    T1.clear();
    X1.clear();
    Y1.clear();
    E1.clear();
    std::cout << "RK4 Points: (k=10)" << std::endl;
    for (auto i : VecSol)
    {
        if (i.GetX(1) > 0)
        {
            std::cout << i << std::endl;
            T1.push_back(i.GetTime());
            X1.push_back(i.GetX(0));
            Y1.push_back(i.GetX(1));
            E1.push_back(0.5 * 100 * (i.GetX(2) * i.GetX(2) + i.GetX(3) * i.GetX(3)) + 100 * 9.81 * i.GetX(1));
        }
    }
    std::cout << std::endl;
    Times.push_back(T1[T1.size() - 1]);
    Ranges.push_back(X1[X1.size() - 1]);

    TGraph *G5 = new TGraph(X1.size(), &X1[0], &Y1[0]);
    G5->SetLineColor(kBlue);
    G5->SetLineWidth(2);
    G5->SetMarkerStyle(20);
    G5->SetMarkerSize(0.5);
    G5->SetMarkerColor(kBlue);
    G5->SetLineStyle(kDashed);
    G5->SetTitle("k=10");

    TGraph *G5E = new TGraph(T1.size(), &T1[0], &E1[0]);
    G5E->SetLineColor(kBlue);
    G5E->SetLineWidth(2);
    G5E->SetMarkerStyle(20);
    G5E->SetMarkerSize(0.5);
    G5E->SetMarkerColor(kBlue);
    G5E->SetLineStyle(kDashed);
    G5E->SetTitle("k=10");

    //Impressão de resultados
    std::cout << "Tempo gasto e espaço percorrido, que o corpo demora a atingir o solo nas diferentes situações de atrito:" << std::endl
              << "(Em todo o problema, foi considerada uma velocidade inicial de 72 m/s e ângulo de 30 graus com a horizontal)" << std::endl;
    std::cout << "k=0:   t ≈ " << Times[0] << "s; x ≈ " << Ranges[0] << "m." << std::endl;
    std::cout << "k=0.2: t ≈ " << Times[1] << "s; x ≈ " << Ranges[1] << "m." << std::endl;
    std::cout << "k=1:   t ≈ " << Times[2] << "s; x ≈ " << Ranges[2] << "m." << std::endl;
    std::cout << "k=5:   t ≈ " << Times[3] << "s; x ≈ " << Ranges[3] << "m." << std::endl;
    std::cout << "k=10:  t ≈ " << Times[4] << "s; x ≈ " << Ranges[4] << "m." << std::endl;
    std::cout << std::endl;

    TCanvas *C1 = new TCanvas("C1", "Multigraph", 500, 500, 600, 600);
    C1->SetGrid();

    TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(G1, "l");
    Mg->Add(G2, "l");
    Mg->Add(G3, "l");
    Mg->Add(G4, "l");
    Mg->Add(G5, "l");
    Mg->Draw("A");
    Mg->GetXaxis()->SetTitle("x-Position (m)");
    Mg->GetYaxis()->SetTitle("y-Position (m)");

    C1->BuildLegend();
    C1->Modified();
    C1->SaveAs("Projectiles_trajectorias.pdf", "AP");

    TCanvas *C2 = new TCanvas("C2", "Multigraph2", 500, 500, 600, 600);
    C2->SetGrid();

    TMultiGraph *Mg2 = new TMultiGraph();
    Mg2->Add(G1E, "l");
    Mg2->Add(G2E, "l");
    Mg2->Add(G3E, "l");
    Mg2->Add(G4E, "l");
    Mg2->Add(G5E, "l");
    Mg2->Draw("A");
    Mg2->GetXaxis()->SetTitle("Time (s)");
    Mg2->GetYaxis()->SetTitle("Energy (J)");

    C2->BuildLegend();
    C2->Modified();
    C2->SaveAs("Projectiles_energia.pdf", "AP");

    return 0;
}
