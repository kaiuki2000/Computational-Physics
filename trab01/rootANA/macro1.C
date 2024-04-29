#include "DataReader.h"
#include "DataManip.h"

#include <TCanvas.h>
#include <TH1F.h>
#include <TFrame.h>
#include <TPaveText.h>
#include <TGraph.h>

void macro1()
{
    TCanvas *c1 = new TCanvas("c1", "Macro1", 600, 150, 800, 700);
    c1->SetFillColor(kBlue - 8);

    auto title = new TPaveText(0.35, 0.930, 0.65, 0.980);
    title->SetFillColor(33);
    title->AddText("Macro1");
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

    DataManip D("SunspotNumberDATA2020.txt");
    /*auto V = D.GetDataVector();
    std::cout << "number of data points read: " << V.size() << std::endl;
    int c = 0;
    for (auto const &x : V)
    {
        std::cout << c << " | "
                  << "(" << std::setprecision(7) << x.first << ", " << x.second << ")" << std::endl;
        c++;
        if (c == 10)
            break;
    }*/

    auto Gdata = D.GetDataGraph(); // use marker style 20, marker size 0.4 and color kBlue+1. the TGraph should be named 'Gdata'
    Gdata->SetMarkerStyle(20);
    Gdata->SetMarkerSize(0.4);
    Gdata->SetMarkerColor(kBlue + 1);
    Gdata->Draw("LP");

    c1->cd();
}