#include "TH1F.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TF1.h"

void Exercicio33()
{
    auto c1 = new TCanvas("c1", "Exercicio 33", 500, 250, 1000, 500);
    auto tpad1 = new TPad("tpad1", "TPad1", 0., 0., 0.5, 1., kTeal - 5, 5, 1);
    auto tpad2 = new TPad("tpad2", "TPad2", 0.5, 0., 1., 1, kSpring - 5, 5, 1);
    tpad1->Draw();
    tpad2->Draw();

    /*Hs[0] = TH1F("Histograma 0", "Hist0;Eixo dos xx;Eixo dos yy", 100., -10., 10.);
    Hs[1] = TH1F("Histograma 1", "Hist1;Eixo dos xx;Eixo dos yy", 200., -20., 20.);*/

    /*auto Hs = new TH1F[2]{TH1F("Histograma 0", "Hist0;Eixo dos xx;Eixo dos yy", 10., 0.5, 10.5),
                          TH1F("Histograma 1", "Hist1;Eixo dos xx;Eixo dos yy", 10., 0.5, 10.5)};*/

    double BinsValues[] = {0, 0.5, 2., 6.5, 8.5, 9.5};
    auto Hs = new TH1F[2]{TH1F("Histograma 0", "Hist0;Eixo dos xx;Eixo dos yy", 5., BinsValues),
                          TH1F("Histograma 1", "Hist1;Eixo dos xx;Eixo dos yy", 5., BinsValues)};

    auto f1 = new TF1("f1", "x", 0., 9.5);
    Hs[0].FillRandom("f1", 1e3);
    Hs[1].FillRandom("f1", 1e3);

    /*for (int i = 0; i < 1e3; i++)
    {
        Hs[0].Fill(f1->GetRandom());
        Hs[1].Fill(f1->GetRandom());
    }*/

    tpad1->cd();
    Hs[0].SetFillColor(kRed - 2.5);
    Hs[0].Draw();

    tpad2->cd();
    Hs[1].SetFillColor(kRed + 2.5);
    Hs[1].Draw();

    std::cout << "Hs[0] bins: " << Hs[0].GetNbinsX() << std::endl;
    std::cout << "Hs[1] bins: " << Hs[1].GetNbinsX() << std::endl;

    c1->cd();
}