#include "FCTools.h"
#include <fstream>
#include <sstream>

//#define DEBUGBUILD5

//file name, returns lines
std::vector<std::string> FCTools::ReadFile2String(std::string filename)
{
#ifdef DEBUGBUILD5
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    std::vector<std::string> Lines;
    std::string Line;

    std::ifstream RFile(filename);
    if (RFile.is_open())
    {
        while (getline(RFile, Line))
        {
            Lines.push_back(Line);
        }
        RFile.close();
        return Lines;
    }

    else
    {
        throw std::invalid_argument(Form("[%s] Cannot read file...!\n", __PRETTY_FUNCTION__));
    }
}

//file name, returns vectors of Vec’s
std::vector<Vec> FCTools::ReadFile2Vec(std::string filename)
{
#ifdef DEBUGBUILD5
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    std::vector<Vec> Lines;
    std::string Line;

    double Number = 0.;
    Vec LineN;

    std::ifstream RFile(filename);
    if (RFile.is_open())
    {
        while (getline(RFile, Line))
        {
            std::istringstream fin(Line);
            while (fin >> Number)
            {
                LineN.push_back(Number);
            }

            Lines.push_back(LineN);
            LineN.clear();
        }
        RFile.close();
        //LineN.push_back(0); -> There were errors with double free...
        return Lines;
    }

    else
    {
        throw std::invalid_argument(Form("[%s] Cannot read file...!\n", __PRETTY_FUNCTION__));
    }
}

//file name, returns pointer to array of Vec’s, int provides number of lines
Vec *FCTools::ReadFile2Vecp(std::string filename, int &ll) //This method fails (crashes) if the number of lines provided is smaller than the actual number...
{                                                          //If it is bigger, it doesn't crash but allocates unnecessary memory...
#ifdef DEBUGBUILD5
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    Vec *Lines = new Vec[ll];
    std::string Line;

    double Number = 0.;
    Vec LineN;
    int i = 0;

    std::ifstream RFile(filename);
    if (RFile.is_open())
    {
        while (getline(RFile, Line))
        {
            std::istringstream fin(Line);
            while (fin >> Number)
            {
                LineN.push_back(Number);
            }

            Lines[i] = LineN;
            LineN.clear();
            i++;
        }
        RFile.close();
        //LineN.push_back(0); -> There were errors with double free...
        return Lines;
    }

    else
    {
        throw std::invalid_argument(Form("[%s] Cannot read file...!\n", __PRETTY_FUNCTION__));
    }
}
