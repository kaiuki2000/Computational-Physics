#include "DataReader.h"

//Default constructor
DataReader::DataReader()
{
    printf("[%s] Default constructor called...\n", __PRETTY_FUNCTION__);
    std::vector<std::pair<double, double>> Data;
}

//Copy constructor
DataReader::DataReader(const DataReader &Obj)
{
    printf("[%s] Copy constructor called...\n", __PRETTY_FUNCTION__);
    std::vector<std::pair<double, double>> Data(Obj.Data);
}

//Copy assignment
DataReader &DataReader::operator=(const DataReader &Obj)
{
    if (this != &Obj)
    {
        printf("[%s] Copy assignment called...\n", __PRETTY_FUNCTION__);
        Data.assign(Obj.Data.begin(), Obj.Data.end());
    }
    return (*this);
}

//Destructor
DataReader::~DataReader()
{
    printf("[%s] Destructor called...\n", __PRETTY_FUNCTION__);
    Data.clear();
}

//FileExists...
bool DataReader::FileExists(std::string &&filename_)
{
    printf("[%s] FileExists called...\n", __PRETTY_FUNCTION__);
    std::ifstream myfile(filename_);

    if (!myfile.is_open())
    {
        std::cout << "*****" << std::endl;
        std::cout << "Erro na abertura do ficheiro '" << filename_ << "'"
                  << "! Assegure-se de que o ficheiro está na diretoria correta..." << std::endl;
        std::cout << "O programa vai agora terminar... " << std::endl;
        std::cout << "*****" << std::endl;
        return (0);
    }
    myfile.close();
    return (1);
}

void DataReader::FileReader(const char *filename_)
{
    printf("[%s] FileReader called...\n", __PRETTY_FUNCTION__);

    int nlinhas = 74053;

    //Creates graph from data file: reading 4th and 5th columns...
    auto Gr = new TGraph(filename_, "%*lg %*lg %*lg %lg %lg %*lg %*lg", " ");

    for (int i = 0; i < nlinhas; i++)
    {
        if ((double)Gr->GetPointX(i) >= 1849)
            Data.push_back(std::make_pair(Gr->GetPointX(i), Gr->GetPointY(i)));
    }
    delete Gr;
}