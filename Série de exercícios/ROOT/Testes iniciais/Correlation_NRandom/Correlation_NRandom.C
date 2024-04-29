#include <ctime>
#include <vector>
#include <algorithm>
#include <iostream>
#include "TRandom3.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TText.h"
#include "TH1D.h"

void Correlation_NRandom()
{
    // random generator
    // https://root.cern.ch/doc/v606/classTRandom.html
    // TRandom3 is the best: period of about 10**6000

    // gRandom: is a pointer to the current random number generator.
    // By default, it points to a TRandom3 object.
    gRandom->SetSeed(0); // random seed

    // vectors with 1000 elements
    int N = 10000;
    vector<Double_t> vrand1(10000);

    // generate values
    std::generate(vrand1.begin(), vrand1.end(), []() -> Double_t { return gRandom->Uniform(); });

    // output
    std::copy(vrand1.begin(), vrand1.begin() + 100, std::ostream_iterator<double>(std::cout, " "));
    cout << '\n';

    // ROOT text
    TText *t = new TText();
    t->SetTextAlign(22);
    t->SetTextColor(kRed + 2);
    t->SetTextFont(43);
    t->SetTextSize(40);
    t->SetTextAngle(0);

    // look to correlations between elements
    // i, i+1
    TGraph *g = nullptr;
    TCanvas *c = new TCanvas("c", "random correlation", 10, 10, 800, 600);
    for (int k = 0; k < 10; ++k)
    { // element lag
        if (g)
            delete g;
        g = new TGraph(N - k, vrand1.data(), vrand1.data() + k);
        g->SetTitle("");
        g->SetMarkerStyle(20);
        g->SetMarkerSize(0.2);
        g->Draw("AP");
        t->DrawTextNDC(0.5, 0.95, Form("lag = %d", k));
        c->Update();
        c->WaitPrimitive();
    }

    // look now to differences and make histogram
    /*y0 = x0
    y1 = x1 - x0
    y2 = x2 - x1
    y3 = x3 - x2
    y4 = x4 - x3
  */
    vector<double> vdif(N);
    std::adjacent_difference(vrand1.begin(), vrand1.end(), vdif.begin());
    auto h = new TH1D("h", "", 200, -1., 1.);
    std::for_each(vdif.begin() + 1, vdif.end(), [h](double x) { h->Fill(x); });
    h->SetFillColor(kGreen + 2);
    h->SetMarkerStyle(20);
    h->SetLineWidth(3);
    h->SetMarkerColor(kBlue + 2);
    t->DrawTextNDC(0.3, 0.95, Form("histo entries = %7.1f", h->GetEntries()));
    h->DrawCopy("E");
    c->Modified();
    c->Update();
    c->SaveAs("FIG_diff.png");
}