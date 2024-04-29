#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"

void TGraphsMacro()
{
    TFile F("trab02.root");
    TGraph *gPoints = (TGraph *)F.Get("gPoints");
    TGraph *gErrors = (TGraph *)F.Get("gErrors");
    TCanvas *cPoly = (TCanvas *)F.Get("cPoly");
    TF1 *fPoly = (TF1 *)F.Get("fPoly");

    auto C2 = new TCanvas("cErrors", "Canvas cErrors", 1000, 200, 600, 500);

    gErrors->Draw("APL");
    C2->Update();

    auto legend = new TLegend(0.1, 0.8, 0.28, 0.9);
    legend->AddEntry(gErrors, "Error points", "P");
    legend->Draw();

    cPoly->Draw();
    cPoly->Update();

    auto legendB = new TLegend(0.6, 0.75, 0.9, 0.9);
    legendB->AddEntry(gPoints, "Points", "P");
    legendB->AddEntry((TObject *)fPoly, "Polynomial function", "l");
    legendB->Draw();

    auto C1 = new TCanvas("cPoints", "Canvas cPoints", 700, 400, 600, 500);

    gPoints->Draw("AP");
    C1->Update();

    auto legendC = new TLegend(0.1, 0.8, 0.28, 0.9);
    legendC->AddEntry(gPoints, "Points", "P");
    legendC->Draw();
}