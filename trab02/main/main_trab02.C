#include "Vandermonde.h"

int main()
{
    unsigned Argn = 10;
    double ArgXmin = 0.;
    double ArgXmax = 1.;
    TF1 *Argf = new TF1("Argf", "sin(2*TMath::Pi()*x)+0.002*cos(100*x)", ArgXmin, ArgXmax);

    Vandermonde v(Argn, ArgXmin, ArgXmax, *Argf);
    Vandermonde vEmpty; //Testing default constructor

    std::cout << "Coefficient vector: " << v.GetCoefficients() << std::endl;

    auto gPoints = v.GetGraphPoints();
    auto fPoly = v.GetPolyFunc();

    //Testing graphs
    TApplication *MyRootApp;
    MyRootApp = new TApplication("MyRootApp", nullptr, nullptr);
    MyRootApp->SetReturnFromRun(true);

    TCanvas *cPoly = new TCanvas("cPoly", "Canvas cPoly", 300, 200, 600, 500);

    gPad->Clear();
    gStyle->SetLabelSize(0.03, "X");
    gStyle->SetLabelSize(0.03, "Y");

    gPad->DrawFrame(fPoly.GetXmin(), fPoly.GetMinimum(),
                    fPoly.GetXmax(), fPoly.GetMaximum(), fPoly.GetTitle());

    fPoly.Draw("SAME");
    gPoints.Draw("PSAME");

    cPoly->Update();
    cPoly->SaveAs("cPoly.eps");

    const char *input;
    Bool_t done = kFALSE;
    TTimer *timer = new TTimer("gSystem->ProcessEvents();", 50, kFALSE);
    std::string Exit;

    do
    {
        timer->TurnOn();
        timer->Reset();
        input = Getline("Type something to continue (or 'exit' to exit)... ");
        Exit = input;
        timer->TurnOff();
        if (input)
            done = kTRUE;
        if (Exit == "exit\n")
            exit(0);
        cPoly->Update();
    } while (!done);

    std::cout << std::endl;

    double *nValues = new double[16];
    double *logEValues = new double[16];
    unsigned n = 0;

    for (int i = 0; i < 16; i++)
    {
        n = 4 * (1 + i);
        Vandermonde v(n, ArgXmin, ArgXmax, *Argf);
        std::cout << "Error: " << v.GetCoeffError() << std::endl;
        nValues[i] = n;
        logEValues[i] = log10(v.GetCoeffError());
    }

    std::cout << std::endl;

    auto gErrors = new TGraph(16, nValues, logEValues);
    gErrors->SetMarkerStyle(21);
    gErrors->SetMarkerColor(39);
    gErrors->SetMarkerSize(2);
    gErrors->SetLineColor(kGreen + 2);
    gErrors->SetLineWidth(2);
    gErrors->SetTitle("gErrors");
    gErrors->SetName("gErrors");

    //Testing gErrors
    TCanvas *cErrors = new TCanvas("cErrors", "Canvas cErrors", 1000, 200, 600, 500);

    gPad->Clear();
    gStyle->SetLabelSize(0.03, "X");
    gStyle->SetLabelSize(0.03, "Y");

    gErrors->Draw("ALP");

    cErrors->Update();
    cErrors->SaveAs("cErrors.eps");

    const char *inputB;
    Bool_t doneB = kFALSE;
    TTimer *timerB = new TTimer("gSystem->ProcessEvents();", 50, kFALSE);
    std::string ExitB;

    do
    {
        timerB->TurnOn();
        timerB->Reset();
        inputB = Getline("Type something to continue (or 'exit' to exit)... ");
        ExitB = inputB;
        timerB->TurnOff();
        if (inputB)
            doneB = kTRUE;
        if (ExitB == "exit\n")
            exit(0);
        cErrors->Update();
    } while (!doneB);

    //Writing in .root file (saving ROOT objects)
    TFile F("trab02.root", "recreate");
    cPoly->Write();
    gPoints.Write();
    fPoly.Write();
    gErrors->Write();
    F.Close();

    std::cout << std::endl;
    FCmatrixFull inv;
    v.GetInverseMatrix(inv);
    std::cout << inv << std::endl;

    delete Argf;
    delete cPoly;
    delete cErrors;
    delete timer;
    delete timerB;
    delete[] nValues;
    delete[] logEValues;
    delete gErrors;

    return (0);
}