#include "TCanvas.h"
#include "TStyle.h"
#include "TF2.h"
#include "TH1F.h"
#include "TFrame.h"
#include "TGraph.h"
#include "TRandom3.h"
#include "TGraph2DErrors.h"

void Graph2()
{
    //gStyle->SetPalette(kBird);
    /*  auto c1 = new TCanvas("c1", "2D function graph", 500, 250, 800, 500);
    c1->SetFillColor(kBlue - 5);
    c1->SetGrid();

    TH1F *hr = c1->DrawFrame(0, 0, 12, 21);
    hr->SetXTitle("Hahaha");
    hr->SetYTitle("Y Axis");

    c1->GetFrame()->SetFillColor(21);
    c1->GetFrame()->SetBorderSize(12);
    c1->Modified();*/

    /*TF2 *f1 = new TF2("f1", "sin(x)*((1/x)*sin(y))", 0., 1., 0., 1.);
    f1->Draw();*/

    /*  TF1 *f1 = new TF1("f1", "x", 0., 12.);
    auto gr = new TGraph("f1");*/
    //gr->SetMarkerStyle(21);
    //gr->SetLineWidth(2);
    //  gr->Draw("LP");
    //c1->SaveAs("Graph.png");

    gStyle->SetPalette(kBird);
    const double e = 0.3;
    const int nd = 500;

    TRandom3 my_random_generator;
    TF2 f2("f2",
           "1000*(([0]*sin(x)/x)*([1]*sin(y)/y))+200",
           -6, 6, -6, 6);
    f2.SetParameters(1, 1);
    TGraph2DErrors dte(nd);
    // Fill the 2D graph
    double rnd, x, y, z, ex, ey, ez;
    for (Int_t i = 0; i < nd; i++)
    {
        f2.GetRandom2(x, y);
        // A random number in [-e,e]
        rnd = my_random_generator.Uniform(-e, e);
        z = f2.Eval(x, y) * (1 + rnd);
        dte.SetPoint(i, x, y, z);
        ex = 0.05 * my_random_generator.Uniform();
        ey = 0.05 * my_random_generator.Uniform();
        ez = fabs(z * rnd);
        dte.SetPointError(i, ex, ey, ez);
    }
    // Fit function to generated data
    f2.SetParameters(0.7, 1.5); // set initial values for fit
    f2.SetTitle("Fitted 2D function");
    dte.Fit(&f2);
    // Plot the result
    auto c1 = new TCanvas();
    f2.SetLineWidth(1);
    f2.SetLineColor(kBlue - 5);
    TF2 *f2c = (TF2 *)f2.DrawClone("Surf1");
    TAxis *Xaxis = f2c->GetXaxis();
    TAxis *Yaxis = f2c->GetYaxis();
    TAxis *Zaxis = f2c->GetZaxis();
    Xaxis->SetTitle("X Title");
    Xaxis->SetTitleOffset(1.5);
    Yaxis->SetTitle("Y Title");
    Yaxis->SetTitleOffset(1.5);
    Zaxis->SetTitle("Z Title");
    Zaxis->SetTitleOffset(1.5);
    dte.DrawClone("P0 Same");
    // Make the x and y projections
    auto c_p = new TCanvas("ProjCan",
                           "The Projections", 1000, 400);
    c_p->Divide(2, 1);
    c_p->cd(1);
    dte.Project("x")->Draw();
    c_p->cd(2);
    dte.Project("y")->Draw();
}
