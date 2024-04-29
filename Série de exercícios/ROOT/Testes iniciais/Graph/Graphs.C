#include <TCanvas.h>
#include <TH1F.h>
#include <TFrame.h>
#include <TPaveText.h>
#include <TGraph.h>

void Graphs()
{
    TCanvas *c1 = new TCanvas("c1", "Teste ao Graph", 600, 150, 500, 700);
    c1->SetFillColor(kBlue - 8);
    //c1->SetGrid();

    auto title = new TPaveText(0.35, 0.930, 0.65, 0.980);
    title->SetFillColor(33);
    title->AddText("Teste ao Graph");
    title->Draw();

    // draw a frame to define the range

    auto tpad1 = new TPad("tpad1", "Tpad1Haha", 0.01, 0.01, 0.99, 0.99 - 0.07, 33, 5, 1);
    tpad1->Draw();

    tpad1->cd();
    tpad1->SetGrid();
    TH1F *hr = tpad1->DrawFrame(0, 0, 12, 22);
    hr->SetXTitle("X Axis");
    hr->SetYTitle("Y Axis");
    tpad1->GetFrame()->SetFillColor(21);
    tpad1->GetFrame()->SetBorderSize(12);
    tpad1->Modified();

    // create graph from data file: reading 1st and 2nd columns
    auto gr = new TGraph("gdata.txt", "%lg %lg %*lg", ",");
    gr->SetMarkerColor(kBlue);
    gr->SetMarkerStyle(21);
    gr->SetLineWidth(2);
    gr->Draw("LP");
    c1->SaveAs("Graph.png"); // can save any extension (.png, .eps, .jpg, ...)

    c1->WaitPrimitive();
    auto gr2 = new TGraph("gdata.txt", "%lg %*lg %lg", ",");
    gr2->SetMarkerColor(kRed);
    gr2->SetMarkerStyle(21);
    gr2->SetLineWidth(2);
    gr2->GetXaxis()->SetTitle("X Axis");
    gr2->GetYaxis()->SetTitle("Y Axis");
    gr2->Draw("ACP");
    c1->Update();
    tpad1->GetFrame()->SetFillColor(21);
    tpad1->GetFrame()->SetBorderSize(12);
    tpad1->Modified();
    c1->SaveAs("Graph2.png");

    c1->cd();
}