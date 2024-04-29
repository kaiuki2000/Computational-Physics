#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"

void Exercicio33()
{
    TCanvas *c = new TCanvas("c", "Phys Comput canvas", 0, 0, 900, 500);
    TF1 *f1 = new TF1("f1", "exp([0]*x)", 0., 10.);
    f1->SetParameter(0, 1.);
    TH1F *hist1 = new TH1F("hist1", "Titulo; Eixo dos x; Eixo dos y", 100, 0., 10.);

    for (int i = 0; i < 1e7; i++)
    {
        hist1->Fill(f1->GetRandom());
    }
    hist1->Draw();
    hist1->SetLineWidth(2);
    hist1->SetLineColor(kRed);
    hist1->Fit("f1");

    TF1 *fg = hist1->GetFunction("f1");
    fg->SetLineWidth(4);
    fg->SetLineStyle(2);
    fg->SetLineColor(kBlue);
    fg->DrawCopy("same"); //superimpose plots

    c->SaveAs("hist1.pdf");
}