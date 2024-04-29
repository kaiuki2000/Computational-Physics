#include <iostream>
#include <vector>

#include "TRandom3.h"

#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TMultiGraph.h"
#include "THStack.h"

using namespace std;

int main()
{
    //Alínea a)
    TRandom3 Rgen(0);
    vector<int> Distribution;
    Distribution.reserve(201);
    Distribution[100] = 400;

    TH1F *h2st = new TH1F("h2st", "test hstack", 201, 0, 200);
    for (int i = 0; i < 201; i++)
        h2st->Fill(i, Distribution[i]);
    h2st->SetFillColor(kBlue);
    h2st->SetMarkerStyle(21);
    h2st->SetMarkerColor(kBlue);

    vector<int> XValues;
    for (int i = 0; i < 201; i++)
        XValues.push_back(i);

    //Distribution at t= 0
    TGraph *G0 = new TGraph(XValues.size(), &XValues[0], &Distribution[0]);
    G0->SetLineColor(kBlue + 1);
    G0->SetLineWidth(3);
    G0->SetMarkerStyle(20);
    G0->SetMarkerColor(kBlue + 1);
    G0->SetTitle("t= 0");

    //Calculating distribution at t= 500
    for (int t = 0; t < 501; t++)
    {
        for (int d = 0; d < 201; d++)
        {
            if (Distribution[d] > 0)
            {
                for (int n = 0; n < Distribution[d]; n++)
                {
                    Distribution[d] -= 1;
                    if (Rgen.Uniform() > 0.5)
                        Distribution[d + 1] += 1;
                    else
                        Distribution[d - 1] += 1;
                }
            }
        }
    }

    //Distribution at t= 500
    TGraph *G1 = new TGraph(XValues.size(), &XValues[0], &Distribution[0]);
    G1->SetLineColor(kRed + 1);
    G1->SetLineWidth(3);
    G1->SetMarkerStyle(20);
    G1->SetMarkerColor(kRed + 1);
    G1->SetTitle("t= 500");

    //Graphing results
    TCanvas *C1 = new TCanvas("C1", "Multigraph", 500, 500, 600, 600);
    C1->SetGrid();

    /*TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(G0);
    Mg->Add(G1);
    Mg->Draw("AP");
    Mg->GetXaxis()->SetTitle("X Position");
    Mg->GetYaxis()->SetTitle("Number of particles");

    C1->BuildLegend();
    C1->Modified();
    C1->SaveAs("prob2a1.pdf", "A");*/

    THStack *hs = new THStack("hs", "Stacked 1D histograms");
    //create three 1-d histograms
    TH1F *h1st = new TH1F("h1st", "test hstack", 201, 0, 200);
    for (int i = 0; i < 201; i++)
        h1st->Fill(i, Distribution[i]);
    h1st->SetFillColor(kRed + 1);
    h1st->SetMarkerStyle(21);
    h1st->SetMarkerColor(kRed + 1);
    hs->Add(h1st);
    hs->Add(h2st);

    TCanvas *cst = new TCanvas("cst", "stacked hists", 10, 10, 700, 700);
    cst->Divide(2, 2);
    // in top left pad, draw the stack with defaults
    cst->cd(1);
    hs->Draw();
    // in top right pad, draw the stack in non-stack mode
    // and errors option
    cst->cd(2);
    gPad->SetGrid();
    hs->Draw("nostack,e1p");
    //in bottom left, draw in stack mode with "lego1" option
    cst->cd(3);
    gPad->SetFrameFillColor(17);
    gPad->SetTheta(3.77);
    gPad->SetPhi(2.9);
    hs->Draw("lego1");

    cst->Modified();
    cst->SaveAs("prob2a1.pdf", "A");

    Distribution.clear();
    XValues.clear();

    //Choosing three random particles...
    int Particle1X = 100;
    int Particle2X = 100;
    int Particle3X = 100;

    //Vectors to store postions over time
    vector<int> Particle1XValues;
    vector<int> Particle2XValues;
    vector<int> Particle3XValues;

    //Specific particle's position over time
    //Particle 1
    for (int t = 0; t < 501; t++)
    {
        if (Rgen.Uniform() > 0.5)
            Particle1X += 1;
        else
            Particle1X -= 1;
        Particle1XValues.push_back(Particle1X);
    }

    //Particle 2
    for (int t = 0; t < 501; t++)
    {
        if (Rgen.Uniform() > 0.5)
            Particle2X += 1;
        else
            Particle2X -= 1;
        Particle2XValues.push_back(Particle2X);
    }

    //Particle 3
    for (int t = 0; t < 501; t++)
    {
        if (Rgen.Uniform() > 0.5)
            Particle3X += 1;
        else
            Particle3X -= 1;
        Particle3XValues.push_back(Particle3X);
    }

    //Vector to store time units
    vector<int> Time;
    for (int i = 0; i < 501; i++)
        Time.push_back(i);

    //Particle 1's position over time
    TGraph *GG1 = new TGraph(Time.size(), &Time[0], &Particle1XValues[0]);
    GG1->SetLineColor(kRed + 1);
    GG1->SetLineWidth(3);
    GG1->SetMarkerStyle(20);
    GG1->SetMarkerColor(kRed + 1);
    GG1->SetTitle("Particle 1");

    //Particle 2's position over time
    TGraph *GG2 = new TGraph(Time.size(), &Time[0], &Particle2XValues[0]);
    GG2->SetLineColor(kBlue + 1);
    GG2->SetLineWidth(3);
    GG2->SetMarkerStyle(20);
    GG2->SetMarkerColor(kBlue + 1);
    GG2->SetTitle("Particle 2");

    //Particle 3's position over time
    TGraph *GG3 = new TGraph(Time.size(), &Time[0], &Particle3XValues[0]);
    GG3->SetLineColor(kGreen + 1);
    GG3->SetLineWidth(3);
    GG3->SetMarkerStyle(20);
    GG3->SetMarkerColor(kGreen + 1);
    GG3->SetTitle("Particle 3");

    //Graphing results
    TCanvas *C2 = new TCanvas("C2", "Multigraph", 500, 500, 600, 600);
    C2->SetGrid();

    TMultiGraph *Mg2 = new TMultiGraph();
    Mg2->Add(GG1);
    Mg2->Add(GG2);
    Mg2->Add(GG3);
    Mg2->Draw("AP");
    Mg2->GetXaxis()->SetTitle("Time");
    Mg2->GetYaxis()->SetTitle("X Position");

    C2->BuildLegend();
    C2->Modified();
    C2->SaveAs("prob2a2.pdf", "A");

    Particle1XValues.clear();
    Particle2XValues.clear();
    Particle3XValues.clear();

    //Alínea b)
    vector<int> Distributionb;
    for (int i = 0; i < 101; i++)
        Distributionb.push_back(0);
    Distributionb[50] = 101;

    vector<int> XValuesb;
    for (int i = 0; i < 101; i++)
        XValuesb.push_back(i);

    int c = 0;
    //Calculating distribution at t= 500
    while (1)
    {
        for (int d = 0; d < 101; d++)
        {
            if (Distributionb[d] > 0)
            {
                for (int n = 0; n < Distributionb[d]; n++)
                {
                    Distributionb[d] -= 1;
                    if (Rgen.Uniform() > 0.5)
                        Distributionb[d + 1] += 1;
                    else
                        Distributionb[d - 1] += 1;
                }
            }
        }

        c = 0;
        for (int i = 0; i < 100; i++)
        {
            if (Distributionb[i] == Distributionb[i + 1])
                c += 1;
            else
                c += 0;
        }

        if (c == 100)
            break;
    }

    //Distribution at t= 500
    TGraph *Gb1 = new TGraph(XValuesb.size(), &XValuesb[0], &Distributionb[0]);
    Gb1->SetLineColor(kRed + 1);
    Gb1->SetLineWidth(3);
    Gb1->SetMarkerStyle(20);
    Gb1->SetMarkerColor(kRed + 1);
    Gb1->SetTitle("t= 500");

    //Graphing results
    TCanvas *Cb1 = new TCanvas("Cb1", "Multigraph", 500, 500, 600, 600);
    Cb1->SetGrid();

    TMultiGraph *Mgb = new TMultiGraph();
    Mgb->Add(Gb1);
    Mgb->Draw("AP");
    Mgb->GetXaxis()->SetTitle("X Position");
    Mgb->GetYaxis()->SetTitle("Number of particles");

    Cb1->BuildLegend();
    Cb1->Modified();
    Cb1->SaveAs("prob2b.pdf", "A");

    Distributionb.clear();
    XValuesb.clear();

    return 0;
}