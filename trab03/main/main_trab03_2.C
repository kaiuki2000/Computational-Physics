#include "Atoms.h"

using namespace std;

const double k = 1.380649e-23;

//Unidades adimensionais
const double Epslon = 1.;
const double Sigma = 1.;
const double t = 0.001;
const double d = 1.;
const double L = 22.;

//Constantes reais
const double SigmaC = 34e-9;
const double mC = 6.69e-26;
const double EpslonC = 120 * k;

int PNGS = 50000;
int ATOMS = 100;

auto LJForce = [](double *r, double *par = nullptr) {
    //const double E = k * 120.;
    //const double o = 34.0e-9;
    return (24. * Epslon * ((pow(Sigma, 6)) / pow(fabs(r[0]), 7) - 2. * (pow(Sigma, 12)) / pow(fabs(r[0]), 13)));
};

TF1 *func = new TF1("", LJForce, 0.5, 22.);

void PPair(std::pair<double, double> &pair)
{
    cout << "First,Second: " << pair.first << "," << pair.second << endl;
}

void CalcR(std::vector<Atoms> &atom) //Calcula o vetor Distância de cada átomo em relação a todos os átomos.
{
    for (int i = 0; i < atom.size(); i++)
    {
        for (int j = i; j < atom.size(); j++)
        {
            double dx = atom[j].pos.first - atom[i].pos.first;
            double dy = atom[j].pos.second - atom[i].pos.second;
            std::pair<double, double> pair = std::make_pair(dx, dy);
            atom[i].SetR(pair, j);
            pair = std::make_pair(-dx, -dy);
            atom[j].SetR(pair, i);
        }
    }
}
void CalcForce(std::vector<Atoms> &atom) //Calcula o vetor força de cada átomo.
{
    for (int i = 0; i < atom.size(); i++)
    {
        for (int j = i + 1; j < atom.size(); j++)
        {
            double dx = (atom[i].r)[j].first, dy = (atom[i].r)[j].second;
            double modr = sqrt((dx * dx + dy * dy));
            double F = func->Eval(modr);
            double Fx = F * dx / modr;
            double Fy = F * dy / modr;

            std::pair<double, double> pair = std::make_pair(Fx, Fy);
            atom[i].SetForce(pair, modr);

            pair = std::make_pair(-Fx, -Fy);
            atom[j].SetForce(pair, modr);
        }
        atom[i].SetAce();
    }
}

int main()
{
    auto watch = TStopwatch();
    watch.Start(kTRUE);
    double sumKEnergy = 0;
    double sumPEnergy = 0;
    vector<Atoms> vec;
    int n = 0;
    vector<double> Energia, xiteracao, EnergiaTotal, EnergiaTotalRel, RMSqVec;
    vector<vector<double>> PosX(PNGS, vector<double>(ATOMS, 0)), PosY(PNGS, vector<double>(ATOMS, 0));
    vector<int> XY(ATOMS, 0);
    double E0 = 0.;
    int ITER_STABILIZED = 0.;
    int ITER_STABILIZED_FLAG = 0.;
    double STABILIZED_TEMP = 0.;
    double RMSq = 0.;

    vector<pair<double, double>> POSINIT(ATOMS, std::make_pair(0, 0));

    for (int i = 0; i < ATOMS; i++)
    {
        Atoms a;
        double x = 6. + d * (i % 10);
        double y = 6. + d * (int)(i / 10);
        a.SetPos(x, y);
        vec.push_back(a);
    }

    CalcR(vec);
    CalcForce(vec);

    cout << "VALORES INICIAIS: " << endl;
    for (auto &i : vec)
    {
        std::pair<double, double> a = i.pos;
        std::pair<double, double> c = i.vel;
        std::pair<double, double> b = i.ace;
        cout << "Position do átomo :  ";
        PPair(a);
        cout << "Velocity do átomo :  ";
        PPair(c);
        cout << "Aceleration do átomo :  ";
        PPair(b);
        cout << "\n";
    }

    do
    {
        cout << "\nITERAÇÃO: " << n << endl;
        sumKEnergy = 0;
        sumPEnergy = 0;
        vector<std::pair<double, double>> AceAtual, VelAtual;
        for (int i = 0; i < vec.size(); i++)
        {
            AceAtual.push_back(vec[i].ace);
            VelAtual.push_back(vec[i].vel);
        }
        for (int i = 0; i < vec.size(); i++)
        {

            vec[i].pos.first = vec[i].pos.first + VelAtual[i].first * t + (AceAtual[i].first * t * t) / (2.);
            vec[i].pos.second = vec[i].pos.second + VelAtual[i].second * t + (AceAtual[i].second * t * t) / (2.);

            //Boundary Check;
            if (vec[i].pos.first < 0.)
            {
                double x = -vec[i].pos.first;
                vec[i].SetPos(x, vec[i].pos.second);
                XY[i] = 1;
            }
            if (vec[i].pos.first > L)
            {
                double x = L - (vec[i].pos.first - L);
                vec[i].SetPos(x, vec[i].pos.second);
                XY[i] = 1;
            }
            if (vec[i].pos.second < 0.)
            {
                double y = -vec[i].pos.second;
                vec[i].SetPos(vec[i].pos.first, y);
                XY[i] = 2;
            }
            if (vec[i].pos.second > L)
            {
                double y = L - (vec[i].pos.second - L);
                vec[i].SetPos(vec[i].pos.first, y);
                XY[i] = 2;
            }
        }
        CalcR(vec);
        CalcForce(vec);
        for (int i = 0; i < vec.size(); i++)
        {
            if (XY[i] == 1)
            {
                VelAtual[i].first = -VelAtual[i].first;
            }
            if (XY[i] == 2)
            {
                VelAtual[i].second = -VelAtual[i].second;
            }

            VelAtual[i].first = VelAtual[i].first + (1. / 2.) * (AceAtual[i].first + vec[i].ace.first) * t;
            VelAtual[i].second = VelAtual[i].second + (1. / 2.) * (AceAtual[i].second + vec[i].ace.second) * t;

            sumKEnergy += (VelAtual[i].first * VelAtual[i].first + VelAtual[i].second * VelAtual[i].second);
            sumPEnergy += vec[i].FinalPot;
            vec[i].vel = VelAtual[i];

            PosX[n][i] = vec[i].pos.first;
            PosY[n][i] = vec[i].pos.second;

            if (n == 0)
            {
                POSINIT[i].first = vec[i].pos.first;
                POSINIT[i].second = vec[i].pos.second;
            }
            else
            {
                RMSq += (vec[i].pos.first - POSINIT[i].first) * (vec[i].pos.first - POSINIT[i].first) + (vec[i].pos.second - POSINIT[i].second) * (vec[i].pos.second - POSINIT[i].second);
            }
        }

        RMSqVec.push_back(RMSq / ATOMS);

        sumKEnergy = m * sumKEnergy / 2.;

        cout << "Energia Cinética(Adimensional) ~ T(K): " << sumKEnergy << endl;
        cout << "Energia Potencial(Adimensional): " << sumPEnergy << endl;
        cout << "Energia Total(Adimensional): " << sumPEnergy + sumKEnergy << endl;
        cout << "Variação Relativa da energia total(%): " << (100 * (sumPEnergy + sumKEnergy - E0) / E0) << " %" << endl;
        n++;

        xiteracao.push_back(n);
        Energia.push_back(sumKEnergy);
        EnergiaTotal.push_back(sumKEnergy + sumPEnergy);

        if (n == 1)
            E0 = sumKEnergy + sumPEnergy;

        EnergiaTotalRel.push_back(100 * (sumKEnergy + sumPEnergy - E0) / (E0));

        if (ITER_STABILIZED_FLAG == 0)
        {
            if (n > 20000) //Verificámos que estabilizava ~ a partir de 20000 iterações
            {
                //Definimos que foi atingido o equilíbrio quando a variação percentual da enegia é <10%
                if ((100 * (sumPEnergy + sumKEnergy - E0) / E0) < 10)
                {
                    STABILIZED_TEMP = sumKEnergy;
                    ITER_STABILIZED = n;
                    ITER_STABILIZED_FLAG = 1;
                }
            }
        }

        //Reset da FinalForce.
        for (int i = 0; i < vec.size(); i++)
        {
            vec[i].FinalForce.first = 0.;
            vec[i].FinalForce.second = 0.;
            vec[i].FinalPot = 0.;
            vec[i].r.clear();
        }

        //Reset do vector que checka as boundaries.
        for (auto i : XY)
            i = 0;
    } while (n < PNGS);
    cout << endl;
    watch.Stop();
    watch.Print("m");
    cout << endl;

    ////////////////////////////////////////////////////////////////////
    ///////////////////////////// CRIAÇÃO  /////////////////////////////
    /////////////////////////////   DOS    /////////////////////////////
    ///////////////////////////// GRÁFICOS /////////////////////////////
    ////////////////////////////////////////////////////////////////////

    //Gráfico posições iniciais
    TCanvas *C11 = new TCanvas("C11", "C11", 500, 500, 600, 600);
    C11->SetGrid();
    TGraph G22(ATOMS, &(PosX[0])[0], &(PosY[0])[0]);
    G22.SetMarkerColor(kBlue);
    G22.SetMarkerSize(1);
    G22.SetMarkerStyle(20);
    G22.GetXaxis()->SetLimits(0., 22.);
    G22.SetMaximum(22.);
    G22.SetMinimum(0.);
    G22.SetTitle("Posicoes iniciais (Adimensionais)");
    G22.GetXaxis()->SetTitle("X Axis");
    G22.GetYaxis()->SetTitle("Y Axis");
    G22.Draw("AP");
    C11->SaveAs("trab03_2a_sistema.pdf");

    //Gráfico energia total e sua variação relativa
    TCanvas *C3 = new TCanvas("C3", "Multigraph2", 500, 500, 600, 600);
    C3->SetGrid();

    //Criação do gráfico
    TGraph *G2 = new TGraph(PNGS, &xiteracao[0], &EnergiaTotal[0]);
    G2->SetLineColor(kBlue);
    G2->SetLineWidth(3);
    G2->SetTitle("Energia Total");

    TGraph *G3 = new TGraph(PNGS, &xiteracao[0], &EnergiaTotalRel[0]);
    G3->SetLineColor(kTeal);
    G3->SetLineWidth(3);
    G3->SetTitle("Variacao relativa da energia total");

    // Criação de um Multigraph
    TMultiGraph *Mg2 = new TMultiGraph();
    Mg2->Add(G2);
    Mg2->Add(G3);
    Mg2->Draw("A");
    Mg2->GetXaxis()->SetTitle("Iteracao");
    Mg2->GetYaxis()->SetTitle("Energia total (Adimensional) e variacao percentual da mesma (%)");
    Mg2->GetYaxis()->SetTitleSize(0.03);
    Mg2->GetYaxis()->SetLabelSize(0.02);
    Mg2->GetXaxis()->SetLabelSize(0.02);
    Mg2->GetXaxis()->SetLimits(0., PNGS);

    //Legenda
    C3->BuildLegend();
    C3->Modified();

    //Gravação em pdf
    C3->SaveAs("trab03_2a_energiatotal.pdf", "AP");

    //Gráfico temperatura
    TGraph *G1 = new TGraph(PNGS, &xiteracao[0], &Energia[0]);

    TCanvas *C2 = new TCanvas("C2", "Multigraph", 500, 500, 600, 600);
    C2->SetGrid();

    //Criação do gráfico
    G1->SetLineColor(kOrange);
    G1->SetLineWidth(3);
    G1->SetTitle("Temperatura");

    // Criação de um Multigraph
    TMultiGraph *Mg = new TMultiGraph();
    Mg->Add(G1);
    Mg->Draw("A");
    Mg->GetXaxis()->SetTitle("Iteracao");
    Mg->GetYaxis()->SetTitle("Temperatura");
    Mg->GetYaxis()->SetLabelSize(0.02);
    Mg->GetXaxis()->SetLabelSize(0.02);
    Mg->GetXaxis()->SetLimits(0., PNGS);

    //Legenda
    C2->BuildLegend();
    C2->Modified();

    C2->SaveAs("trab03_2a_temperatura.pdf", "AP");

    //Gráfico do desvio quadrático médio
    TCanvas *C4 = new TCanvas("C4", "Multigraph3", 500, 500, 600, 600);
    C4->SetGrid();

    //Criação do gráfico
    TGraph *G4 = new TGraph(PNGS, &xiteracao[0], &RMSqVec[0]);
    G4->SetLineColor(kSpring);
    G4->SetLineWidth(3);
    G4->SetTitle("Desvio quadratico medio (Adimensional)");

    // Criação de um Multigraph
    TMultiGraph *Mg3 = new TMultiGraph();
    Mg3->Add(G4);
    Mg3->Draw("A");
    Mg3->GetXaxis()->SetTitle("Iteracao");
    Mg3->GetYaxis()->SetTitle("Desvio quadratico medio (Adimensional)");
    Mg3->GetYaxis()->SetTitleSize(0.03);
    Mg3->GetYaxis()->SetLabelSize(0.02);
    Mg3->GetXaxis()->SetLabelSize(0.02);
    Mg3->GetXaxis()->SetLimits(0., PNGS);

    //Legenda
    C4->BuildLegend();
    C4->Modified();

    //Gravação em pdf
    C4->SaveAs("trab03_2a_desvioquadratico.pdf", "AP");

    //Este ciclo pode ser usado para gerar 1 .png por iteração e fazer gifs
    /*TCanvas *C11 = new TCanvas("C11", "C11", 500, 500, 600, 600);
    for (int i = 0; i < 1; i = i + 100) //Apenas a posição inicial (até i<1)
    {
        C11->SetGrid();
        TGraph G2(ATOMS, &(PosX[i])[0], &(PosY[i])[0]);
        G2.SetMarkerColor(kBlue);
        G2.SetMarkerSize(1);
        G2.SetMarkerStyle(20);
        G2.GetXaxis()->SetLimits(0., 22.);
        G2.SetMaximum(22.);
        G2.SetMinimum(0.);
        G2.Draw("AP");

        if (i < 10)
        {
            std::string S = "img00" + std::to_string(i) + ".png";
            C11->SaveAs(S.c_str());
        }
        else
        {
            if (10 <= i < 100)
            {
                std::string S = "img0" + std::to_string(i) + ".png";
                C11->SaveAs(S.c_str());
            }
        }
    }*/

    cout << endl;
    cout << "Estabilizou ao fim de " << ITER_STABILIZED << " iterações, ou seja, após " << ITER_STABILIZED * t << " unidades de tempo adimensionais, ou "
         << ITER_STABILIZED * t * SigmaC * sqrt(mC / EpslonC) << " s, à temperatura de aproximadamente " << STABILIZED_TEMP
         << " K (com uma incerteza máxima de 10%)." << endl;

    return 0;
}