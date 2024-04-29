#include "ODEPoint.h"
#include "ODESolver.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "TF1.h"

int main()
{

    std::vector<double> Times;
    std::vector<double> Ranges;

    //Vou considerar velocidade inicial 72 m/s e ângulo de 30 graus com a horizontal
    std::vector<TFormula> ArgFormulas;
    TFormula ArgFormula0("Formula0", "x[3]");
    TFormula ArgFormula1("Formula1", "x[4]");
    TFormula ArgFormula2("Formula2", "-[0]*x[3]");
    TFormula ArgFormula3("Formula3", "-9.81-[0]*x[4]");
    ArgFormula2.SetParameter(0, 0.);
    ArgFormula3.SetParameter(0, 0.);
    ArgFormulas.push_back(ArgFormula0);
    ArgFormulas.push_back(ArgFormula1);
    ArgFormulas.push_back(ArgFormula2);
    ArgFormulas.push_back(ArgFormula3);

    ODESolver ODE1(ArgFormulas);
    std::vector<double> Point0{0., 0., 0., 72. * sqrt(3.) / 2., 72. * 1. / 2.};
    ODEPoint ODE1Point0(4, Point0);

    //k=0
    std::vector<ODEPoint> SolPoints = ODE1.RK4Solver(ODE1Point0, 72. / (9.81 * 100.), 100);

    std::vector<double> T1;
    std::vector<double> X1;
    std::vector<double> Y1;
    std::vector<double> E1;
    std::cout << "RK4 Points: (k=0)" << std::endl;
    for (auto i : SolPoints)
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

    //k=0.2
    ArgFormulas.clear();
    ArgFormula2.SetParameter(0, 0.2);
    ArgFormula3.SetParameter(0, 0.2);
    ArgFormulas.push_back(ArgFormula0);
    ArgFormulas.push_back(ArgFormula1);
    ArgFormulas.push_back(ArgFormula2);
    ArgFormulas.push_back(ArgFormula3);

    ODESolver ODE2(ArgFormulas);

    SolPoints.clear();
    SolPoints = ODE2.RK4Solver(ODE1Point0, 72. / (9.81 * 100.), 100);

    T1.clear();
    X1.clear();
    Y1.clear();
    E1.clear();
    std::cout << "RK4 Points: (k=0.2)" << std::endl;
    for (auto i : SolPoints)
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

    //k=1
    ArgFormulas.clear();
    ArgFormula2.SetParameter(0, 1.);
    ArgFormula3.SetParameter(0, 1.);
    ArgFormulas.push_back(ArgFormula0);
    ArgFormulas.push_back(ArgFormula1);
    ArgFormulas.push_back(ArgFormula2);
    ArgFormulas.push_back(ArgFormula3);

    ODESolver ODE3(ArgFormulas);

    SolPoints.clear();
    SolPoints = ODE3.RK4Solver(ODE1Point0, 72. / (9.81 * 100.), 100);

    T1.clear();
    X1.clear();
    Y1.clear();
    E1.clear();
    std::cout << "RK4 Points: (k=1)" << std::endl;
    for (auto i : SolPoints)
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

    //k=5
    ArgFormulas.clear();
    ArgFormula2.SetParameter(0, 5.);
    ArgFormula3.SetParameter(0, 5.);
    ArgFormulas.push_back(ArgFormula0);
    ArgFormulas.push_back(ArgFormula1);
    ArgFormulas.push_back(ArgFormula2);
    ArgFormulas.push_back(ArgFormula3);

    ODESolver ODE4(ArgFormulas);

    SolPoints.clear();
    SolPoints = ODE4.RK4Solver(ODE1Point0, 72. / (9.81 * 100.), 100);

    T1.clear();
    X1.clear();
    Y1.clear();
    E1.clear();
    std::cout << "RK4 Points: (k=5)" << std::endl;
    for (auto i : SolPoints)
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

    //k=10
    ArgFormulas.clear();
    ArgFormula2.SetParameter(0, 10.);
    ArgFormula3.SetParameter(0, 10.);
    ArgFormulas.push_back(ArgFormula0);
    ArgFormulas.push_back(ArgFormula1);
    ArgFormulas.push_back(ArgFormula2);
    ArgFormulas.push_back(ArgFormula3);

    ODESolver ODE5(ArgFormulas);

    SolPoints.clear();
    SolPoints = ODE5.RK4Solver(ODE1Point0, 72. / (9.81 * 100.), 100);

    T1.clear();
    X1.clear();
    Y1.clear();
    E1.clear();
    std::cout << "RK4 Points: (k=10)" << std::endl;
    for (auto i : SolPoints)
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
    std::cout << "k=0:   t ≈ " << Times[0] << "; x ≈ " << Ranges[0] << "." << std::endl;
    std::cout << "k=0.2: t ≈ " << Times[1] << "; x ≈ " << Ranges[1] << "." << std::endl;
    std::cout << "k=1:   t ≈ " << Times[2] << "; x ≈ " << Ranges[2] << "." << std::endl;
    std::cout << "k=5:   t ≈ " << Times[3] << "; x ≈ " << Ranges[3] << "." << std::endl;
    std::cout << "k=10:  t ≈ " << Times[4] << "; x ≈ " << Ranges[4] << "." << std::endl;
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
    C1->SaveAs("Prob4_trajectorias.pdf", "AP");

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
    C2->SaveAs("Prob4_energia.pdf", "AP");

    return 0;
}
