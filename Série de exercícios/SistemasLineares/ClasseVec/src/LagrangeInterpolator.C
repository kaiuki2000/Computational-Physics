#include "LagrangeInterpolator.h"

#include "TROOT.h"
#include <TStyle.h>

//#define DEBUGBUILD7

//Constructor
LagrangeInterpolator::LagrangeInterpolator(int ArgN, double *Argx, double *Argy, TF1 *ArgF0) : DataPoints(ArgN, Argx, Argy)
{
#ifdef DEBUGBUILD7
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    F0 = ArgF0;
    FInterpolator = new TF1("FInterpolator", this, &LagrangeInterpolator::fInterpolator, x[0] - 0.001, x[N - 1] + 0.001, 0); //Associar uma função interpoladora a um objeto
}

//Destructor
LagrangeInterpolator::~LagrangeInterpolator() //Seems to be working fine...
{
#ifdef DEBUGBUILD7
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    /*if (FInterpolator)
        delete FInterpolator;
    if (F0)
        delete F0;*/
}

//Interpolate method
double LagrangeInterpolator::Interpolate(double Argx)
{
#ifdef DEBUGBUILD7
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    double result = 0.;
    double lx;

    for (int i = 0; i < N; i++)
    {
        lx = 1.;
        for (int k = 0; k < N; k++)
        {
            if (k != i)
                lx *= (Argx - x[k]) / (x[i] - x[k]); //Calculating the interpolated points
        }
        result += y[i] * lx;
    }

    return result;
}

//Draw method
void LagrangeInterpolator::Draw()
{
#ifdef DEBUGBUILD7
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (NPlots == 0)
    {
        TApplication *MyRootApp2;
        MyRootApp2 = new TApplication("MyRootApp2", nullptr, nullptr);
        MyRootApp2->SetReturnFromRun(true);
    }

    TCanvas *C2 = new TCanvas("C2", "Canvas C2", 700, 200, 600, 500);

    gPad->Clear();
    gStyle->SetLabelSize(0.05, "X");
    gStyle->SetLabelSize(0.05, "Y");
    TGraph *g = new TGraph(N, x, y);
    g->SetMarkerStyle(20);
    g->SetMarkerColor(kRed + 1);
    g->SetMarkerSize(2);

    FInterpolator->SetLineColor(42);
    FInterpolator->SetLineWidth(4);
    FInterpolator->SetTitle("Lagrange interpolator");

    if (F0 != nullptr)
    {
        F0->SetLineColor(41);
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

    /*auto legend2 = new TLegend(0.6, 0.7, 0.9, 0.9);
    legend2->AddEntry((TObject *)0, "Type 'next' to see next graph", "");
    legend2->AddEntry((TObject *)0, "Type 'exit' to exit", "");
    legend2->Draw();*/

    FInterpolator->Draw("SAME");
    if (F0 != NULL) //Tests whether underlying function exists...
        F0->Draw("SAME");
    g->Draw("PSAME"); //Draw more than one TF1 in one canvas

    C2->Update();
    C2->SaveAs("plot_Lagrange.eps");

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
        C2->Update();
    } while (!done);

    delete g;
    delete C2;
    NPlots++;
}

//GetInterpolationFunction method
TF1 *LagrangeInterpolator::GetInterpolationFunction()
{
#ifdef DEBUGBUILD7
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    return FInterpolator;
}

//SetFunction method: sets underlying function
void LagrangeInterpolator::SetFunction(TF1 *f)
{
#ifdef DEBUGBUILD7
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    F0 = f;
}

//GetInterpolationFunctionExpression method: gives InterpolationFunction's explicit formula. Doesn't work...
/*TString LagrangeInterpolator::GetInterpolationFunctionExpression()
{
    return FInterpolator->GetExpFormula();
}
*/