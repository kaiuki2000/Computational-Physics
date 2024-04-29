#include "NewtonInterpolator.h"

#include "TROOT.h"
#include <TStyle.h>

//#define DEBUGBUILD8

//Constructor
NewtonInterpolator::NewtonInterpolator(int ArgN, double *Argx, double *Argy, TF1 *ArgF0) : DataPoints(ArgN, Argx, Argy)
{
#ifdef DEBUGBUILD8
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    F0 = ArgF0;
    FInterpolator = new TF1("FInterpolator", this, &NewtonInterpolator::fInterpolator, x[0] - 0.001, x[N - 1] + 0.001, 0); //Associar uma função interpoladora a um objeto
}

//Destructor
NewtonInterpolator::~NewtonInterpolator() //Seems to be working fine...
{
#ifdef DEBUGBUILD8
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    /*if (FInterpolator)
        delete FInterpolator;
    if (F0)
        delete F0;*/
}

//DiffTable method for calculating divided differences
double NewtonInterpolator::DiffTable(int i, int j)
{
    if (i == j)
    {
        return y[i];
    }
    else
    {
        return ((DiffTable(i + 1, j) - DiffTable(i, j - 1)) / (x[j] - x[i]));
    }
}

//Interpolate method
double NewtonInterpolator::Interpolate(double Argx)
{
#ifdef DEBUGBUILD8
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    double result = y[0];
    double tempx;

    for (int k = 1; k < N; k++)
    {
        tempx = 1.0;
        for (int i = 0; i < k; i++)
        {
            tempx = tempx * (Argx - x[i]); //Calculating the intermidiate interpolated points
        }
        result = result + DiffTable(0, k) * tempx; //Calling the DiffTable method to calculate the interpolated points
    }

    return result;
}

//Draw method
void NewtonInterpolator::Draw()
{
#ifdef DEBUGBUILD8
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (NPlots == 0)
    {
        TApplication *MyRootApp3;
        MyRootApp3 = new TApplication("MyRootApp3", nullptr, nullptr);
        MyRootApp3->SetReturnFromRun(true);
    }

    TCanvas *C3 = new TCanvas("C3", "Canvas C3", 700, 200, 600, 500);
    C3->SetGrid();

    gPad->Clear();
    gStyle->SetLabelSize(0.05, "X");
    gStyle->SetLabelSize(0.05, "Y");
    TGraph *g = new TGraph(N, x, y);
    g->SetMarkerStyle(20);
    g->SetMarkerColor(kRed + 1);
    g->SetMarkerSize(2);

    FInterpolator->SetLineColor(214);
    FInterpolator->SetLineWidth(4);
    FInterpolator->SetTitle("Newton interpolator");

    if (F0 != nullptr)
    {
        F0->SetLineColor(215);
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

    C3->Update();
    //C3->SaveAs("plot_Newton.pdf"); //Uncomment to save in .pdf file.

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
        C3->Update();
    } while (!done);

    delete g;
    delete C3;
    NPlots++;
}

//GetInterpolationFunction method
TF1 *NewtonInterpolator::GetInterpolationFunction()
{
#ifdef DEBUGBUILD8
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    return FInterpolator;
}

//SetFunction method: sets underlying function
void NewtonInterpolator::SetFunction(TF1 *f)
{
#ifdef DEBUGBUILD8
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    F0 = f;
}

//GetInterpolationFunctionExpression method: gives InterpolationFunction's explicit formula. Doesn't work...
/*TString NewtonInterpolator::GetInterpolationFunctionExpression()
{
    return FInterpolator->GetExpFormula();
}
*/