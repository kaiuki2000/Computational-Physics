#include "IntegratorMC.h"

#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TMultiGraph.h"

using namespace std;

// Constantes
const double tauBi = 7.5;
const double tauPo = 200.;

// Valores iniciais
const double NBi_0 = 500.;
const double NPo_0 = 0.;
const double NPb_0 = 0.;

// t_max= 1000. dias
const double t_max = 1000.;

/*Double_t N_Bi(Double_t *t, Double_t *par)
{
    auto f1_Lambda = [&](double *t, double *par) {
        return -1 / tauBi;
    };

    auto f1_TF1 = new TF1("f1", f1_Lambda, 0., t_max, 0);

    IntegratorMC f1Integrator(0., t[0], f1_TF1);

    double Integral = 0.;
    double Error = 0.;

    // nSamples= 1000
    f1Integrator.UniformRandom(Integral, Error, 1000);

    return NBi_0 * TMath::Exp(Integral);
}*/

Double_t N_Bi(Double_t *t, Double_t *par)
{
    auto f1_Lambda = [&](double *t, double *par) {
        return -N_Bi(t, par) / tauBi;
    };

    auto f1_TF1 = new TF1("f1", f1_Lambda, 0., t_max, 0);

    IntegratorMC f1Integrator(0., t[0], f1_TF1);

    double Integral = 0.;
    double Error = 0.;

    // nSamples= 1000
    f1Integrator.UniformRandom(Integral, Error, 1000);

    if (t[0] != 0)
        return Integral;
    else
        return 500.;
}

Double_t N_Po(Double_t *t, Double_t *par)
{
    auto f2_Lambda = [&](double *t, double *par) {
        return N_Bi(t, par) / tauBi - N_Po(t, par) / tauPo;
    };

    auto f2_TF1 = new TF1("f2", f2_Lambda, 0., t_max, 0);

    IntegratorMC f2Integrator(0., t[0], f2_TF1);

    double Integral = 0.;
    double Error = 0.;

    // nSamples= 1000
    f2Integrator.UniformRandom(Integral, Error, 1000);

    if (t[0] != 0)
        return Integral;
    else
        return 0;
}

int main()
{
    auto N_Bi_TF1 = new TF1("N_Bi", N_Bi, -5., t_max, 0);
    auto N_Po_TF1 = new TF1("N_Po", N_Po, -5., t_max, 0);

    //N_Bi(t) graph
    TCanvas *C1 = new TCanvas("C1", "Multigraph", 500, 500, 600, 600);
    C1->SetGrid();

    TGraph *G1 = new TGraph(N_Bi_TF1);
    G1->SetLineColor(kBlue + 1);
    G1->SetLineWidth(3);
    G1->SetMarkerStyle(20);
    G1->SetMarkerColor(kBlue + 1);
    G1->SetTitle("N_{Bi}(t)");

    /*TGraph *G2 = new TGraph(N_Po_TF1);
    G2->SetLineColor(kRed + 1);
    G2->SetLineWidth(3);
    G2->SetMarkerStyle(20);
    G2->SetMarkerColor(kRed + 1);
    G2->SetTitle("N_{Po}(t)");*/

    TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(G1);
    //Mg->Add(G2);
    Mg->Draw("AL");
    Mg->GetXaxis()->SetTitle("Time (days)");
    Mg->GetYaxis()->SetTitle("N");
    Mg->SetMaximum(600.);

    C1->BuildLegend();
    C1->Modified();
    C1->SaveAs("prob1a.pdf", "A");

    cout << "NBi(0)= " << N_Bi_TF1->Eval(0) << endl;
    //cout << "NPo(0)= " << N_Po_TF1->Eval(0) << endl;

    return 0;
}