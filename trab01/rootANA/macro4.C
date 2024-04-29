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
#include "TMultiGraph.h"

void macro4()
{

    TCanvas *c1 = new TCanvas("c1", "Macro4", 600, 150, 800, 700);
    c1->SetFillColor(kBlue - 8);

    auto title = new TPaveText(0.35, 0.930, 0.65, 0.980);
    title->SetFillColor(33);
    title->AddText("Macro4");
    title->Draw();

    // draw a frame to define the range

    auto tpad1 = new TPad("tpad1", "Tpad1Haha", 0.01, 0.01, 0.99, 0.99 - 0.07, 33, 5, 1);
    tpad1->Draw();

    tpad1->cd();
    tpad1->SetGrid();
    TH1F *hr = tpad1->DrawFrame(1844, 0, 2025, 550);
    hr->SetXTitle("Year");
    hr->SetYTitle("Number of sunspots");
    tpad1->GetFrame()->SetFillColor(21);
    tpad1->GetFrame()->SetBorderSize(12);
    tpad1->Modified();

    //

    DataManip D("SunspotNumberDATA2020.txt");
    auto Gdata = D.GetDataGraph();

    auto Vsmooth181 = D.GetMovingAverage(181);
    auto Gsmooth11 = D.GetMovingAverageGraph(11, "g11");    // args: números de dias, nome do objecto. LineColor=kYellow
    auto Gsmooth181 = D.GetMovingAverageGraph(181, "g181"); // args: números de dias, nome do objecto. LineColor=kMagenta

    // make a new graph superimposing the two graphs: Gdata and Gsmooth
    TMultiGraph *G1 = new TMultiGraph("Gmult1", "Gmult1");
    G1->Add(Gdata, "P");      //only points
    G1->Add(Gsmooth11, "L");  // lines
    G1->Add(Gsmooth181, "L"); // lines

    // make a new graph superimposing the two graphs: Gdata and Gsmooth
    TMultiGraph *G2 = new TMultiGraph("Gmult2", "Gmult2");
    G2->Add(Gsmooth11, "L");  // lines
    G2->Add(Gsmooth181, "L"); // lines

    //auto c2 = new TCanvas;

    tpad1->cd();
    G1->Draw();

    TCanvas *c2 = new TCanvas("c2", "Macro4", 800, 250, 800, 700);
    c2->SetFillColor(kBlue - 8);

    auto title2 = new TPaveText(0.35, 0.930, 0.65, 0.980);
    title2->SetFillColor(33);
    title2->AddText("Macro4");
    title2->Draw();

    auto tpad2 = new TPad("tpad2", "Tpad2Haha", 0.01, 0.01, 0.99, 0.99 - 0.07, 33, 5, 1);
    tpad2->Draw();

    tpad2->cd();
    tpad2->SetGrid();
    TH1F *hr2 = tpad2->DrawFrame(1844, 0, 2025, 550);
    hr2->SetXTitle("Year");
    hr2->SetYTitle("Number of sunspots");
    tpad2->GetFrame()->SetFillColor(21);
    tpad2->GetFrame()->SetBorderSize(12);
    tpad2->Modified();

    tpad2->cd();
    G2->Draw();

    c1->cd();
}