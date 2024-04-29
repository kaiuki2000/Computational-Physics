#include "DataReader.h"
#include "DataManip.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
#include <complex>
#include <vector>
#include "TObject.h"
#include "TFile.h"
#include "TGraph.h"
#include "TMultiGraph.h"

int main()
{
    /*
    for (int i = 0; i < 10; i++)
    {
        std::cout << std::setprecision(7) << V[i].first << " " << V[i].second << std::endl;
    }
    */

    std::vector<TObject *> ROOTmanager;

    if (!DataReader::FileExists("SunspotNumberDATA2020.txt"))
        exit(1);

    DataManip D("SunspotNumberDATA2020.txt");

    auto V = D.GetDataVector();
    std::cout << "number of data points read: " << V.size() << std::endl;

    // get a graph (ROOT TGraph) with all data
    auto Gdata = D.GetDataGraph(); // use marker style 20, marker size 0.4 and color kBlue+1. the TGraph should be named 'Gdata'
    ROOTmanager.emplace_back(Gdata);

    auto Vsort = D.GetDataVectorSorted(1);
    int c = 0;
    for (auto const &x : Vsort)
    {
        std::cout << c << " | "
                  << "(" << std::setprecision(7) << x.first << ", " << x.second << ")" << std::endl;
        c++;
        if (c == 10)
            break;
    }

    // get and plot the data time derivatives: df/dx(xi) = [s(i+1) - s(i)] / Delta t_i
    // use STL to make differences
    // use again TGraph
    auto Vderiv = D.GetDataDerivativeVector();    // (time, derivative)
    auto GdataDeriv = D.GetDataDerivativeGraph(); // use marker style 20, marker size 0.4 and color kGreen+2. the TGraph should be named 'GdataDeriv'
    auto HdataDeriv = D.GetDataDerivativeHisto(); // the Histogram should be named 'HdataDeriv'
    ROOTmanager.emplace_back(GdataDeriv);
    ROOTmanager.emplace_back(HdataDeriv);

    // A way of smoothing a signal (get rid of very high frequencies) is making a moving average
    // Get a vector with the moving average time array (time, moving average signals)
    auto Vsmooth181 = D.GetMovingAverage(181);
    auto Gsmooth11 = D.GetMovingAverageGraph(11, "g11");    // args: números de dias, nome do objecto. LineColor=kYellow
    auto Gsmooth181 = D.GetMovingAverageGraph(181, "g181"); // args: números de dias, nome do objecto. LineColor=kMagenta

    // make a new graph superimposing the two graphs: Gdata and Gsmooth
    TMultiGraph *G1 = new TMultiGraph("Gmult1", "Gmult1");
    G1->Add(Gdata, "P");      //only points
    G1->Add(Gsmooth11, "L");  // lines
    G1->Add(Gsmooth181, "L"); // lines

    // make a new graph superimposing the two graphs: Gdata and Gsmooth
    TMultiGraph *G2 = new TMultiGraph("Gmult2", "Gmult2");
    G2->Add(Gsmooth11, "L");  // lines
    G2->Add(Gsmooth181, "L"); // lines

    ROOTmanager.emplace_back(G1);
    ROOTmanager.emplace_back(G2);
    ROOTmanager.emplace_back(Gsmooth11);
    ROOTmanager.emplace_back(Gsmooth181);

    return (0);
}