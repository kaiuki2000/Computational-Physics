#include "DataReader.h"
#include "DataManip.h"

#include "TH1F.h"
#include "TRandom3.h"
#include "TCanvas.h"
#include "TPaveText.h"
#include <iostream>
#include <TFile.h>
#include <TF1.h>
#include "TFrame.h"

void macro3()
{
    auto c1 = new TCanvas("c", "Teste de Histogramas 2", 500, 250, 900, 500);
    c1->SetFillColor(21);
    c1->SetGrid();

    DataManip D("SunspotNumberDATA2020.txt");

    auto Vderiv = D.GetDataDerivativeVector();
    auto HdataDeriv = D.GetDataDerivativeHisto();

    //HdataDeriv->SetFillColor(kRed - 3);
    HdataDeriv->Draw();

    c1->cd();
}