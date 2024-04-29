#include "Integrator.h"
#include "IntegratorMC.h"
#include "RootFinder.h"

#include <limits>

#include "TMath.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "TTimer.h"
#include "Getline.h"

void AlineaCTF1Draw(TF1 *Zero)
{
    TApplication *MyRootApp;
    MyRootApp = new TApplication("MyRootApp", nullptr, nullptr);
    MyRootApp->SetReturnFromRun(true);

    TCanvas *C1 = new TCanvas("C1", "Grafico de y = int_{x}^{+inf} [f(v)-0.05 dv]", 200, 10, 700, 500);

    C1->SetFillColor(42);
    C1->SetGrid();
    Zero->SetLineColor(2);
    Zero->SetLineWidth(4);
    Zero->SetMarkerColor(4);
    Zero->SetMarkerStyle(21);
    Zero->SetTitle("Grafico de y = int_{x}^{+inf} [f(v)-0.05 dv]");
    Zero->GetXaxis()->SetTitle("x axis");
    Zero->GetYaxis()->SetTitle("y axis");
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
    //Alínea a)
    //Constantes
    const double k = 1.380649e-23;   //Constante de Boltzmann
    const double mH = 1.00784;       //Massa molar do H
    const double NA = 6.02214076e23; //Número de Avogadro
    const double m = (2. * mH) / NA; //Massa de 1 molécula de H2
    const double T = 300;            //Temperatura do gás (300 K)

    const double inf = 1e3; //Definição de +Infinito: A distribuição vale ~0, se considerarmos v>1e3. Por isso, consideramos inf=1e3.

    //Verificação do que foi dito acima. f(1e3)~0
    std::cout << "f(1e3)= " << 4 * TMath::Pi() * pow(m / (2 * TMath::Pi() * k * T), 3. / 2.) * 1e3 * 1e3 * exp((-1. / 2.) * (m * 1e3 * 1e3) / (k * T)) << std::endl;
    std::cout << std::endl;

    //Lambda function que define a distribuição de Maxwell-Boltzmann
    auto MBD = [&k, &m, &T](double *v, double *par = nullptr) {
        return 4 * TMath::Pi() * pow(m / (2 * TMath::Pi() * k * T), 3. / 2.) * v[0] * v[0] * exp((-1. / 2.) * (m * v[0] * v[0]) / (k * T));
    };

    //Definição da 'TF1'
    TF1 *MBDTF1 = new TF1("MBDTF1", MBD, 0., inf, 0);

    //Instanciamento de um objeto 'Integrator'
    Integrator MBD_Int(0., inf, MBDTF1);

    //Definição das variáveis 'Integral' e 'Error'
    double Integral = 0.;
    double Error = 0.;

    //Cálculo do integral da alínea 1. a), com erro relativo inferior a 1e-3 (Método de Romberg)
    int nRomberg = MBD_Int.RombergRelativeError(Integral, Error, 1e-3);

    //Impressão dos resultados obtidos com o método de Romberg
    std::cout << "Romberg integral= " << Integral << " (Matrix size (integration order)= " << nRomberg << ") (Number of slices= 2^" << nRomberg << " = " << pow(2, nRomberg) << ")" << std::endl;
    std::cout << "Romberg error= " << Error << std::endl;
    std::cout << "Romberg relative error= " << Error / Integral << std::endl;
    std::cout << std::endl;

    //Instanciamento de um objeto 'IntegratorMC'
    IntegratorMC MBD_Int2(0, inf, MBDTF1);

    //Cálculo do integral da alínea 1. a), com erro relativo inferior a 1e-3 (Monte-Carlo "Simples" (Sem "Importance Sampling"))
    int nSamples = MBD_Int2.UniformRandomRelativeError(Integral, Error, 1e-3);

    //Impressão dos resultados obtidos com Monte-Carlo "Simples"
    std::cout << "Monte-Carlo integral: " << Integral << " (Nsamples= " << nSamples << ")" << std::endl;
    std::cout << "Monte-Carlo error: " << Error << std::endl;
    std::cout << "Monte-Carlo relative error: " << Error / Integral << std::endl;
    std::cout << std::endl;

    //Valor exato, obtido com TF1->Integral(x0,x1)
    std::cout << "Exact value= " << MBDTF1->Integral(0., inf) << " (Obtained with ROOT's 'Integral' method for TF1's)" << std::endl;
    std::cout << std::endl;

    //Desenho do gráfico da distribuição de Maxwell-Boltzmann
    TCanvas *C2 = new TCanvas("C2", "Multigraph", 500, 500, 600, 600);
    C2->SetGrid();

    //Criação do gráfico da distribuição de Maxwell-Boltzmann
    TGraph *G1 = new TGraph(MBDTF1);
    G1->SetLineColor(kOrange);
    G1->SetLineWidth(3);
    G1->SetTitle("MB Distribution");

    //Criação de um Multigraph
    TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(G1);
    Mg->Draw("A");
    Mg->GetXaxis()->SetTitle("v");
    Mg->GetYaxis()->SetTitle("f(v)");
    Mg->GetYaxis()->SetLabelSize(0.02);
    Mg->GetXaxis()->SetLabelSize(0.02);
    Mg->SetMaximum(MBDTF1->Eval(sqrt(2 * k * T / m)));
    Mg->GetXaxis()->SetLimits(0., inf);

    //Legenda
    C2->BuildLegend();
    C2->Modified();
    //Gravação do gráfico da distribuição de Maxwell-Boltzmann
    C2->SaveAs("trab03_1a.pdf", "AP");

    //Alínea c)
    //Definição de um vetor de erros para obter erro máximo
    std::vector<double> ErrorsVector;

    //Definição da função cujo zero pretendemos calcular: lambda function
    auto AlineaC = [&MBDTF1, &inf, &ErrorsVector](double *v, double *par = nullptr) {
        Integrator MBDInt(v[0], inf, MBDTF1);

        double Integral = 0.;
        double Error = 0.;

        MBDInt.Trapezoidal(1e4, Integral, Error);
        //Introdução dos erros no vetor de erros
        ErrorsVector.push_back(Error);

        return Integral - 0.05;
    };

    //Definição da função cujo zero pretendemos calcular: TF1
    TF1 *AlineaCTF1 = new TF1("AlineaCTF1", AlineaC, 0., inf, 0);

    //Instanciamento de um objeto 'RootFinder' para cálculo do zero da função definida anteriormente
    RootFinder C(0., inf, AlineaCTF1);

    //Parâmetros do método Quasi-Newton
    double Delta = 1e-8;
    double Argx0 = 80.;
    int N_Max = 100;
    double Epslon = 1e-8;

    //Cálculo do zero
    double ZeroAlineaC = C.QuasiN(Delta, Argx0, N_Max, Epslon);

    std::cout << std::endl;
    //Desenho do gráfico da função cujo zero acabámos de calcular
    AlineaCTF1Draw(AlineaCTF1);

    //Impressão do valor do zero
    std::cout << std::endl;
    std::cout << "Zero de AlineaCTF1= " << std::setprecision(10) << ZeroAlineaC << std::endl;

    //Cálculo do erro (parte 1): máximo dos erros do vetor 'ErrorsVector'
    //Este erro vem do cálculo do integral com a regra dos trapézios, na função AlineaC (lambda function)
    auto ErrorsVectorMax = *std::max_element(std::begin(ErrorsVector), std::end(ErrorsVector));

    //Impressão de um majorante do erro: O erro verdadeiro corresponde à soma do 'ErrorsVectorMax' com o erro proveniente do cálculo...
    //Do zero com o método Quasi-Newton.
    std::cout << "Erro= " << ErrorsVectorMax + Epslon << std::endl;
    std::cout << "Erro relativo= " << (ErrorsVectorMax + Epslon) / (ZeroAlineaC) << std::endl;
    std::cout << std::endl;

    //Alínea b)

    //Lambda function: v*f(v)
    auto MBD2 = [&k, &m, &T](double *v, double *par = nullptr) {
        return v[0] * 4 * TMath::Pi() * pow(m / (2 * TMath::Pi() * k * T), 3. / 2.) * v[0] * v[0] * exp((-1. / 2.) * (m * v[0] * v[0]) / (k * T));
    };

    //Definição da 'TF1' de v*f(v)
    TF1 *MBD2TF1 = new TF1("MBD2TF1", MBD2, 0., inf, 0);

    //Cálculo do K da Pdf auxiliar (para normalização da mesma)
    double K = 1 / (9 * (atan(1877. / 20.) + atan(123. / 20.)));

    //Lambda function: Pdf
    auto Pdf = [&K](double *x, double *par = nullptr) {
        return K * (.9 / (1. + (0.1 * x[0] - 6.15) * (0.1 * x[0] - 6.15)));
    };

    //Definição da 'TF1' de Pdf
    TF1 *PdfTF1 = new TF1("Pdf", Pdf, 0., inf, 0);

    //Testar a normalização da Pdf
    Integrator PdfNormalized(0., inf, PdfTF1);
    PdfNormalized.Trapezoidal(1e4, Integral, Error);
    std::cout << "Pdf integral= " << Integral << std::endl;
    std::cout << "Pdf integral error= " << Error << std::endl;
    std::cout << std::endl;

    //Lambda function: xy
    auto xy = [&K](double *y, double *par = nullptr) {
        return 61.5 + 10 * tan((y[0]) / (9 * K) - atan(123. / 20.));
    };

    //Definição da 'TF1' de  xy
    TF1 *xyTF1 = new TF1("xy", xy, 0., inf, 0);

    //Instanciamento de um objeto 'IntegratorMC', para integrar a função v*f(v)
    IntegratorMC MBD2_Int(0, inf, MBD2TF1);

    //Aplicação do método de "Importance Sampling", para o cálculo da velocidade média
    nSamples = MBD2_Int.ImportanceSamplingRelativeError(PdfTF1, xyTF1, Integral, Error, 1e-3);
    //Impressão dos resultados
    std::cout << "Importance Sampling: " << Integral << " (Nsamples= " << nSamples << ")" << std::endl;
    std::cout << "Importance Sampling Error: " << Error << std::endl;
    std::cout << "Importance Sampling Relative Error: " << Error / Integral << std::endl;
    std::cout << std::endl;

    //Desenho do gráfico de v*f(v) e Pdf (normalizada)
    //Definição de um TCanvas
    TCanvas *C3 = new TCanvas("C3", "Multigraph2", 500, 500, 600, 600);
    C3->SetGrid();

    //Criação do gráfico da Pdf
    TGraph *G2 = new TGraph(PdfTF1);
    G2->SetLineColor(kPink);
    G2->SetLineWidth(3);
    G2->SetTitle("Normalized Pdf");

    //Criação do gráfico de v*f(v)
    TGraph *G3 = new TGraph(MBD2TF1);
    G3->SetLineColor(kTeal);
    G3->SetLineWidth(3);
    G3->SetTitle("f(v)*v");

    //Definição de um multigraph onde serão guardados os gráficos de v*f(v) e da Pdf
    TMultiGraph *Mg2 = new TMultiGraph();
    Mg2->Add(G2);
    Mg2->Add(G3);
    Mg2->Draw("A");
    Mg2->GetXaxis()->SetTitle("x Axis");
    Mg2->GetYaxis()->SetTitle("y Axis");
    Mg2->GetYaxis()->SetLabelSize(0.02);
    Mg2->GetXaxis()->SetLabelSize(0.02);
    Mg2->SetMaximum(1 + MBD2TF1->Eval(sqrt(2 * k * T / m)));
    Mg2->GetXaxis()->SetLimits(0., inf);

    //Legenda
    C3->BuildLegend();
    C3->Modified();
    //Gravação dos gráficos de v*f(v) e da Pdf (normalizada)
    C3->SaveAs("trab03_1b.pdf", "AP");

    return (0);
}