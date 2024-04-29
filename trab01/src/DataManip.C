#include "DataManip.h"

//Data Manipulation

//Default constructor
DataManip::DataManip(const std::string &filename_) : DataReader(), filename(filename_)
{
    printf("[%s] Default constructor called...\n", __PRETTY_FUNCTION__);

    const char *Buffer = filename_.data();
    this->FileReader(Buffer);

    std::vector<std::pair<double, double>> Derivatives;
    std::vector<std::pair<double, double>> MAvalues;
}

//Copy constructor
DataManip::DataManip(const DataManip &Obj) : DataReader(Obj), filename(Obj.filename)
{
    printf("[%s] Copy constructor called...\n", __PRETTY_FUNCTION__);

    std::vector<std::pair<double, double>> Derivatives;
    std::vector<std::pair<double, double>> MAvalues;
}

//Copy assignment
//Falta copiar Derivatives? Mavalues?
DataManip &DataManip::operator=(const DataManip &Obj)
{
    if (this != &Obj)
    {
        printf("[%s] Copy assignment called...\n", __PRETTY_FUNCTION__);
        Data.assign(Obj.Data.begin(), Obj.Data.end());
        filename = Obj.filename;
    }
    return (*this);
}

//Destructor
DataManip::~DataManip()
{
    printf("[%s] Destructor called...\n", __PRETTY_FUNCTION__);
    Data.clear();
}

//Função que quando chamada dá sort dependendo de ser chamada com 0 ou 1.
std::vector<std::pair<double, double>> &DataManip::GetDataVectorSorted(const bool &testb)
{
    //Descendente
    if (testb == 0)
    {
        sort(DataManip::Data.begin(), DataManip::Data.end(), [](const std::pair<double, double> &a, const std::pair<double, double> &b) { return (a.second > b.second); });
        /*
        for (int i = 0; i < 10; i++)
        {
            //Print nos 10 maiores.
            std::cout << std::setprecision(7) << DataManip::Data[i].first << " " << DataManip::Data[i].second << std::endl;
        }
        */
    }

    //Ascendente
    else if (testb == 1)
    {
        sort(DataManip::Data.begin(), DataManip::Data.end(), [](const std::pair<double, double> &a, const std::pair<double, double> &b) { return (a.second < b.second); });
        /*
        for (int i = 0; i < 10; i++)
        {
            //Print nos 10 menores.
            std::cout << std::setprecision(7) << DataManip::Data[i].first << " " << DataManip::Data[i].second << std::endl;
        }
        */
    }
    return (Data);
}

//Obter vector data
std::vector<std::pair<double, double>> &DataManip::GetDataVector()
{
    return (Data);
}

TGraph *DataManip::GetDataGraph()
{
    auto Graph1 = new TGraph;
    for (int i = 0; i < (int)Data.size(); i++)
    {
        Graph1->SetPoint(i, Data[i].first, Data[i].second);
    }

    /*TFile F("fstorage.root", "recreate");
    Graph1->Write();
    F.Close();*/

    return (Graph1);
}

//DataDerivativeVector
std::vector<std::pair<double, double>> &DataManip::GetDataDerivativeVector()
{
    std::vector<double> Vx;
    std::vector<double> Vy;

    for (int i = 0; i < (int)Data.size(); i++)
    {
        Vx.push_back(Data[i].first);
        Vy.push_back(Data[i].second);
    }

    std::vector<double> Xdif(Data.size());
    std::vector<double> Ydif(Data.size());

    std::adjacent_difference(Vx.begin(), Vx.end(), Xdif.begin());
    std::adjacent_difference(Vy.begin(), Vy.end(), Ydif.begin());

    Vx.clear();
    Vy.clear();

    std::vector<double> Result;
    for (int i = 0; i < (int)Xdif.size(); i++)
    {
        Result.push_back(Ydif[i] / Xdif[i]);
    }
    Xdif.clear();
    Ydif.clear();

    for (int i = 0; i < (int)Result.size(); i++)
    {
        Derivatives.push_back(std::make_pair(Data[i].first, Result[i]));
    }
    //std::cout << "Result size: " << Result.size() << std::endl;
    Result.clear();

    //std::cout << "Derivatives size: " << Derivatives.size() << std::endl;

    return (Derivatives);
}

TGraph *DataManip::GetDataDerivativeGraph()
{
    //std::cout << "Derivatives size: " << Derivatives.size() << std::endl;

    auto Graph1 = new TGraph;
    for (int i = 0; i < (int)Derivatives.size(); i++)
    {
        Graph1->SetPoint(i, Derivatives[i].first, Derivatives[i].second);
    }

    /*TFile F("fstorage.root", "recreate");
    Graph1->Write();
    F.Close();*/

    return (Graph1);
}

TH1F *DataManip::GetDataDerivativeHisto()
{
    auto Histo1 = new TH1F("HdataDeriv",
                           "HdataDeriv;Year;Derivative",
                           1e4,   // Number of Bins
                           1844,  // Lower X Boundary
                           2025); // Upper X Boundary
    for (int i = 0; i < (int)Derivatives.size(); i++)
    {
        Histo1->Fill(Derivatives[i].first, Derivatives[i].second);
    }

    /*TFile F("fstorage.root", "recreate");
    Graph1->Write();
    F.Close();*/

    return (Histo1);
}

std::vector<std::pair<double, double>> &DataManip::GetMovingAverage(int M)
{
    std::vector<double> MovingAverage;
    int c = 0;
    double sum = 0;

    for (int i = 0; i < (int)Data.size(); i++)
    {

        if ((i > floor(((double)M / 2) - 1)) && (i < floor(((int)Data.size() - M / 2))))
        {
            sum = 0;
            for (int j = (0 + c); j < (M - 1 + c); j++)
            {
                sum += Data[j].second;
            }
            c++;
            sum /= M;
            MovingAverage.push_back(sum);
        }

        else
        {
            MovingAverage.push_back(Data[i].second);
        }
    }

    for (int i = 0; i < (int)MovingAverage.size(); i++)
    {
        MAvalues.push_back(std::make_pair(Data[i].first, MovingAverage[i]));
    }
    //std::cout << MovingAverage.size() << std::endl;
    return (MAvalues);
}

TGraph *DataManip::GetMovingAverageGraph(int M, std::string TGraphname)
{
    auto Gsmooth11 = GetMovingAverage(M);

    auto Graph1 = new TGraph;
    for (int i = 0; i < (int)Gsmooth11.size(); i++)
    {
        Graph1->SetPoint(i, Gsmooth11[i].first, Gsmooth11[i].second);
    }

    /*TFile F("fstorage.root", "recreate");s
    Graph1->Write();
    F.Close();*/

    const char *Buffer = TGraphname.data();
    Graph1->SetName(Buffer);

    return (Graph1);
}
