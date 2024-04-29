#include "TH1F.h"
#include "TRandom3.h"
#include "TCanvas.h"
//#include "TText.h"
#include "TPaveText.h"
#include <iostream>
#include <TFile.h>
#include <TF1.h>

void Histogramas()
{
    auto cnt_r_h = new TH1F("count_rate",
                            "Count Rate;N_{Counts};# occurrence",
                            100,   // Number of Bins
                            -0.5,  // Lower X Boundary
                            10.5); // Upper X Boundary

    auto hist2 = new TH1F("hist2",
                          "Hist2;N_{Counts};# occurrence",
                          100,  // Number of Bins
                          -10., // Lower X Boundary
                          10.); // Upper X Boundary

    auto mean_count = 3.6f;
    TRandom3 rndgen;

    auto fx = new TF1("f1", "x*x", -10., 10.);

    // simulate the measurements
    for (int imeas = 0; imeas < 5500; imeas++)
    {
        cnt_r_h->Fill(rndgen.Poisson(mean_count));
        hist2->Fill(fx->GetRandom());
    }

    auto c = new TCanvas("c", "Teste de Pads", 500, 250, 1000, 500);
    c->SetFillColor(kGreen - 5);
    //cnt_r_h->Draw();

    /*TText *t = new TText(0.5, 0.96, "Hello World !");
    t->SetTextAlign(22);
    t->SetTextColor(kRed - 2);
    t->SetTextFont(43);
    t->SetTextSize(20);
    t->SetTextAngle(0);
    t->Draw();*/

    auto title = new TPaveText(.2, 0.945, .8, .985);
    title->SetFillColor(33);
    title->AddText("Teste de Pads");
    title->Draw();

    auto tpad1 = new TPad("tpad1", "Tpad1Haha", 0.01, 0.01, 0.49, 0.99 - 0.07, kRed - 15, 5, 1);
    tpad1->Draw();

    auto tpad2 = new TPad("tpad1", "Tpad2Haha", 0.01 + 0.50, 0.01, 0.99, 0.99 - 0.07, kBlue - 5, 5, 1);
    tpad2->Draw();

    tpad1->cd();
    cnt_r_h->SetFillColor(kTeal - 5);
    cnt_r_h->Draw();
    tpad1->Modified();

    tpad2->cd();
    hist2->SetFillColor(kSpring - 5);
    hist2->Draw();

    auto f1 = new TF1("f1", "-[0]*(x-[1])*(x-[2])+[3]", -10., 10.);
    hist2->Fit("f1");
    /*TF1 *fg = hist2->GetFunction("f1");
    fg->SetLineWidth(4);
    fg->SetLineStyle(1);
    fg->SetLineColor(kBlue + 0.5);
    fg->DrawCopy("same"); //superimpose plots*/

    tpad2->Modified();

    c->cd();
    //c->Modified(); What?

    // Print summary
    std::cout << "Moments of Distribution:\n"
              << " - Mean     = " << cnt_r_h->GetMean() << " +- "
              << cnt_r_h->GetMeanError() << "\n"
              << " - Std Dev  = " << cnt_r_h->GetStdDev() << " +- "
              << cnt_r_h->GetStdDevError() << "\n"
              << " - Skewness = " << cnt_r_h->GetSkewness() << "\n"
              << " - Kurtosis = " << cnt_r_h->GetKurtosis() << "\n";

    // store my histogram into ROOT file
    TFile F("fstorage.root", "recreate");
    cnt_r_h->Write();
    F.Close();
}