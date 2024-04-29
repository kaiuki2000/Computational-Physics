#ifndef __DATAMANIP_H__
#define __DATAMANIP_H__

#include "DataReader.h"

class DataManip : public DataReader
{
public:
    DataManip(const std::string &filename_ = "SunspotNumberDATA2020.txt"); //Default constructor
    DataManip(const DataManip &);                                          //Copy constructor
    DataManip &operator=(const DataManip &);                               //Copy assignment
    ~DataManip();                                                          //Destructor

    std::vector<std::pair<double, double>> &GetDataVectorSorted(const bool &); //Função que é chamada na main para dar sort ao vector;
    std::vector<std::pair<double, double>> &GetDataVector();                   //Função que dá a qualquer momento o vetor Data.
    TGraph *GetDataGraph();
    std::vector<std::pair<double, double>> &GetDataDerivativeVector();
    TGraph *GetDataDerivativeGraph();
    TH1F *GetDataDerivativeHisto();
    std::vector<std::pair<double, double>> &GetMovingAverage(int);
    TGraph *GetMovingAverageGraph(int, std::string);

private:
    std::string filename; //Nome do ficheiro, que recebe quando se chama o construtor.
    std::vector<std::pair<double, double>> Derivatives;
    std::vector<std::pair<double, double>> MAvalues;
};

#endif // __DATAMANIP_H__