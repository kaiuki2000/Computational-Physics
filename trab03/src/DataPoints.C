#include "DataPoints.h"

int DataPoints::NPlots = 0;

//#define DEBUGBUILD6

//Should gPoints even be initialized as nullptr?
//Default constructor
DataPoints::DataPoints() : N(0), x(nullptr), y(nullptr), gPoints(nullptr)
{
#ifdef DEBUGBUILD6
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
}

//Constructor 2
DataPoints::DataPoints(int ArgN, double *Argx, double *Argy) : N(ArgN), gPoints(nullptr)
{
#ifdef DEBUGBUILD6
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (N > 0)
    {
        if (Argx && Argy)
        {
            x = new double[N];
            y = new double[N];

            std::copy(Argx, Argx + N, x);
            std::copy(Argy, Argy + N, y);
        }
        else
        {
            throw std::invalid_argument(Form("[%s] Argx and Argy can't be nullptr..!\n", __PRETTY_FUNCTION__));
        }
    }
    else
    {
        if (N == 0)
        {
            x = nullptr;
            y = nullptr;
        }
        else
        {
            throw std::invalid_argument(Form("[%s] Number of elements can't be negative...!\n", __PRETTY_FUNCTION__));
        }
    }
}

//Destructor
DataPoints::~DataPoints()
{
#ifdef DEBUGBUILD6
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (x)
        delete[] x;
    if (y)
        delete[] y;
}

//Additional methods
//Draw method
void DataPoints::Draw()
{
#ifdef DEBUGBUILD6
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    TGraph *g = new TGraph(N, x, y);
    g->SetMarkerStyle(20);
    g->SetMarkerColor(kRed + 1);
    g->SetMarkerSize(2);
    g->SetTitle("Data points plot");
    //g->SetLineWidth(2);

    TApplication *MyRootApp;
    MyRootApp = new TApplication("MyRootApp", nullptr, nullptr);
    MyRootApp->SetReturnFromRun(true);

    TCanvas *C1 = new TCanvas("C1", "Canvas C1", 600, 500);
    g->Draw("PA"); //Add "C" for curve...
    C1->Update();
    gPad->WaitPrimitive();
    delete g;
}

//GetGraph method
const TGraph &DataPoints::GetGraph() const
{
#ifdef DEBUGBUILD6
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    return *gPoints;
}

//Print method
void DataPoints::Print(std::string filename)
{
#ifdef DEBUGBUILD6
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    //printf("[%s]:\n", __PRETTY_FUNCTION__);

    for (int i = 0; i < N; i++)
    {
        printf("(x(%d),y(%d)) = (%f, %f) ", i, i, x[i], y[i]);
        printf("\n");
    }
    printf("\n");
    printf("filename: %s\n", filename.c_str());
}

//operator <<
/*std::ostream &operator<<(std::ostream &, const DataPoints &)
{
}*/
