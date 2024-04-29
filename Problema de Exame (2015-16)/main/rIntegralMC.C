#include "IntegratorMC.h"
#include "TAxis.h"
#include "TTimer.h"
#include "Getline.h"

using namespace std;

void SimpleDraw(TF1 *Zero)
{
    TApplication *MyRootApp;
    MyRootApp = new TApplication("MyRootApp", nullptr, nullptr);
    MyRootApp->SetReturnFromRun(true);

    TCanvas *C1 = new TCanvas("C1", "Grafico do erro em funcao de a", 200, 10, 7000, 5000);

    C1->SetFillColor(42);
    C1->SetGrid();
    Zero->SetLineColor(2);
    Zero->SetLineWidth(4);
    Zero->SetMarkerColor(4);
    Zero->SetMarkerStyle(21);
    Zero->SetTitle("Grafico do erro em funcao de a");
    Zero->GetXaxis()->SetTitle("a");
    Zero->GetYaxis()->SetTitle("Error");
    Zero->Draw("ACP");
    const char *Input;
    Bool_t Done = kFALSE;
    TTimer *Timer = new TTimer("gSystem->ProcessEvents();", 50, kFALSE);
    std::string Exit;
    Zero->Draw();
    C1->Update();
    C1->SetFillColor(21);
    C1->SetBorderSize(12);
    C1->Modified();
    do
    {
        Timer->TurnOn();
        Timer->Reset();
        Input = Getline("Type something to continue... ");
        Exit = Input;
        Timer->TurnOff();
        if (Input)
            Done = kTRUE;
        if (Exit == "exit\n")
            //exit(0);
            C1->Update();
    } while (!Done);
}

int main()
{
    double x1 = 0.;
    double x2 = TMath::Pi();

    TF1 *F = new TF1("F", "1/(x*x+cos(x)*cos(x))", x1, x2);

    IntegratorMC FIntegrator(x1, x2, F);

    double Integral = 0.;
    double Error = 0.;

    FIntegrator.UniformRandom(Integral, Error, 1000);

    cout << "Standard Monte-Carlo (nSamples= 1000):\nIntegral= " << Integral << endl
         << "Error= " << Error << endl;

    //Special case: a=0
    double a = 0.;
    double C = 1 / (x2 - x1);

    //Pdf
    auto PDF_Lambda = [&](double *x, double *par = nullptr) {
        return C;
    };

    TF1 *PDF = new TF1("PDF", PDF_Lambda, x1, x2, 0);

    //Checking pdf normalization
    Integrator PDFIntegrator(x1, x2, PDF);
    PDFIntegrator.RombergRelativeError(Integral, Error, 1e-3);
    cout << "\nChecking PDF normalization:\nIntegral = " << Integral << endl;

    //Xy
    auto Xy_Lambda = [&](double *y, double *par = nullptr) {
        return x1 + TMath::Pi() * y[0];
    };

    TF1 *Xy = new TF1("Xy", Xy_Lambda, x1, x2, 0);

    FIntegrator.ImportanceSampling(PDF, Xy, Integral, Error, 1000);

    cout << "\nMonte-Carlo with importance sampling (nSamples= 1000 && a=0):\nIntegral= " << Integral << endl
         << "Error= " << Error << "\n"
         << endl;

    //General case
    double C2 = 0.;
    double Integral2 = 0.;
    double Error2 = 0.;

    auto MCIntError = [&](double *a, double *par = nullptr) {
        C2 = a[0] / (exp(-a[0] * x1) - exp(-a[0] * x2));

        //Pdf2
        auto PDF2_Lambda = [&](double *x, double *par = nullptr) {
            return C2 * exp(-a[0] * x[0]);
        };

        TF1 *PDF2 = new TF1("PDF2", PDF2_Lambda, x1, x2, 0);

        //Xy2
        auto Xy2_Lambda = [&](double *y, double *par = nullptr) {
            return log(exp(-a[0] * x1) - (a[0] * y[0]) / (C2)) / (-a[0]);
        };

        TF1 *Xy2 = new TF1("Xy2", Xy2_Lambda, x1, x2, 0);

        double ErrorMean = 0.;
        for (int i = 0; i < 10; i++)
        {
            FIntegrator.ImportanceSampling(PDF2, Xy2, Integral2, Error2, 1000);
            ErrorMean += Error2;
        }

        if (a[0] != 0)
            return ErrorMean / 10.;

        if (a[0] == 0)
            return Error;
        else
        {
            return 10.;
        }
    };

    TF1 *MCIntErrorFunc = new TF1("MCIntErrorFunc", MCIntError, 0., 1.5, 0);

    SimpleDraw(MCIntErrorFunc);

    cout << "\nO valor de a que minimiza o erro é: a= " << MCIntErrorFunc->GetMinimumX() << "\nPara esse valor de a, Error= "
         << MCIntErrorFunc->GetMinimum() << endl;

    return 0;
}