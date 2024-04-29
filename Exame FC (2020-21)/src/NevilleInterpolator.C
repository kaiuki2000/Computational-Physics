#include "NevilleInterpolator.h"

#include "TROOT.h"
#include <TStyle.h>

//#define DEBUGBUILD9

//Constructor
NevilleInterpolator::NevilleInterpolator(int ArgN, double *Argx, double *Argy, TF1 *ArgF0) : DataPoints(ArgN, Argx, Argy)
{
#ifdef DEBUGBUILD9
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    F0 = ArgF0;
    FInterpolator = new TF1("FInterpolator", this, &NevilleInterpolator::fInterpolator, x[0] - 0.001, x[N - 1] + 0.001, 0); //Associar uma função interpoladora a um objeto
}

//Destructor
NevilleInterpolator::~NevilleInterpolator() //Seems to be working fine...
{
#ifdef DEBUGBUILD9
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    /*if (FInterpolator)
        delete FInterpolator;
    if (F0)
        delete F0;*/
}

//Interpolate method
double NevilleInterpolator::Interpolate(double Argx)
{
#ifdef DEBUGBUILD9
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    double *yTemp = new double[N];

    for (int i = 0; i < N; i++)
    {
        yTemp[i] = y[i]; //Auxiliar vector (temporary)
    }

    for (int k = 1; k < N; k++)
    {
        for (int i = 0; i < N - k; i++)
        {
            yTemp[i] = ((Argx - x[i + k]) * yTemp[i] - (Argx - x[i]) * yTemp[i + 1]) / (x[i] - x[i + k]); //Calculating the interpolated values
        }
    }
    //Last value calculated is y[0] when k = N - 1 and i = 0 ...
    double result = yTemp[0];
    delete[] yTemp;
    return result;
}

//Draw method
void NevilleInterpolator::Draw()
{
#ifdef DEBUGBUILD9
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (NPlots == 0)
    {
        TApplication *MyRootApp4;
        MyRootApp4 = new TApplication("MyRootApp4", nullptr, nullptr);
        MyRootApp4->SetReturnFromRun(true);
    }

    TCanvas *C4 = new TCanvas("C4", "Canvas C4", 700, 200, 600, 500);

    gPad->Clear();
    gStyle->SetLabelSize(0.05, "X");
    gStyle->SetLabelSize(0.05, "Y");
    TGraph *g = new TGraph(N, x, y);
    g->SetMarkerStyle(20);
    g->SetMarkerColor(kRed + 1);
    g->SetMarkerSize(2);

    FInterpolator->SetLineColor(226);
    FInterpolator->SetLineWidth(4);
    FInterpolator->SetTitle("Neville interpolator");

    if (F0 != nullptr)
    {
        F0->SetLineColor(227);
        F0->SetLineWidth(4);
        F0->SetLineStyle(2);
    }

    gPad->DrawFrame(FInterpolator->GetXmin(), FInterpolator->GetMinimum(),
                    FInterpolator->GetXmax(), FInterpolator->GetMaximum(), FInterpolator->GetTitle());

    auto legend = new TLegend(0.1, 0.7, 0.48, 0.9);
    legend->AddEntry(FInterpolator, "Interpolator function", "l");
    legend->AddEntry(F0, "Underlying function", "l");
    legend->AddEntry(g, "Points", "lep");
    legend->Draw();

    TText *t = new TText(FInterpolator->GetXmax() - (FInterpolator->GetXmax() / 5), FInterpolator->GetMaximum() - (0.3 * FInterpolator->GetMaximum() / 5), "Type 'next' to see next graph");
    t->SetTextAlign(22);
    t->SetTextColor(kBlack);
    t->SetTextFont(43);
    t->SetTextSize(15);
    t->Draw();

    TText *t2 = new TText(FInterpolator->GetXmax() - (FInterpolator->GetXmax() / 5), FInterpolator->GetMaximum() - (0.7 * FInterpolator->GetMaximum() / 5), "Type 'exit' to exit");
    t2->SetTextAlign(22);
    t2->SetTextColor(kBlack);
    t2->SetTextFont(43);
    t2->SetTextSize(15);
    t2->Draw();

    FInterpolator->Draw("SAME");
    if (F0 != NULL) //Tests whether underlying function exists...
        F0->Draw("SAME");
    g->Draw("PSAME"); //Draw more than one TF1 in one canvas

    C4->Update();
    C4->SaveAs("plot_Neville.eps");

    const char *input;
    Bool_t done = kFALSE;
    TTimer *timer = new TTimer("gSystem->ProcessEvents();", 50, kFALSE);
    std::string Exit;

    do
    {
        timer->TurnOn();
        timer->Reset();
        input = Getline("Type 'next' to see the next graph or 'exit' to exit: ");
        Exit = input;
        timer->TurnOff();
        if (input)
            done = kTRUE;
        if (Exit == "exit\n")
            exit(0);
        C4->Update();

    } while (!done);

    delete g;
    delete C4;
    NPlots++;
}

//GetInterpolationFunction method
TF1 *NevilleInterpolator::GetInterpolationFunction()
{
#ifdef DEBUGBUILD9
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    return FInterpolator;
}

//SetFunction method: sets underlying function
void NevilleInterpolator::SetFunction(TF1 *f)
{
#ifdef DEBUGBUILD9
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    F0 = f;
}

//GetInterpolationFunctionExpression method: gives InterpolationFunction's explicit formula. Doesn't work...
/*TString NevilleInterpolator::GetInterpolationFunctionExpression()
{
    return FInterpolator->GetExpFormula();
}
*/