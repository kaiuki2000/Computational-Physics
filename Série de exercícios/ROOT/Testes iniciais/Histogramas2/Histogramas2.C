#include "TH1F.h"
#include "TRandom3.h"
#include "TCanvas.h"
//#include "TText.h"
#include "TPaveText.h"
#include <iostream>
#include <TFile.h>
#include <TF1.h>
#include "TFrame.h"

void Histogramas2()
{
    auto c = new TCanvas("c", "Teste de Histogramas 2", 500, 250, 1000, 500);
    c->SetFillColor(kGreen - 5);
    c->SetGrid();

    /*TH1F *hr = c->DrawFrame(0., 0., 12., 12.);
    c->GetFrame()->SetFillColor(21);
    c->Modified();*/

    auto h1 = new TH1F("count_rate",
                       "Count Rate;N_{Counts};# occurrence",
                       100,   // Number of Bins
                       -0.5,  // Lower X Boundary
                       10.5); // Upper X Boundary

    auto mean_count = 3.6f;
    TRandom3 rndgen;

    // simulate the measurements
    for (int imeas = 0; imeas < 5500; imeas++)
    {
        h1->Fill(rndgen.Poisson(mean_count));
    }

    h1->SetFillColor(kRed - 3);
    h1->Draw();
}