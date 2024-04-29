#ifndef __DATAREADER_H__
#define __DATAREADER_H__

#include <cstdio>
#include <vector>
#include <TGraph.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <TFile.h>
#include <numeric>
#include "TH1F.h"
#include "math.h"

//Data reader class
class DataReader
{
public:
    DataReader();                              //Default constructor
    DataReader(const DataReader &);            //Copy constructor
    DataReader &operator=(const DataReader &); //Copy assignment
    ~DataReader();                             //Destructor

    static bool FileExists(std::string &&); //Tests if the file exists
    void FileReader(const char *);          //Reads the file contents and writes them into a vector of pairs of doubles

protected:
    std::vector<std::pair<double, double>> Data; //Data vector
};

#endif // __DATAREADER_H__
