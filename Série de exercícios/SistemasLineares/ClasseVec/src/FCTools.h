#ifndef __FCTOOLS_H__
#define __FCTOOLS_H__

#include "FCMatrixAlgorithm.h"

class FCTools
{
public:
    //File name, returns lines...
    static std::vector<std::string> ReadFile2String(std::string);
    //File name, returns vectors of Vec’s...
    static std::vector<Vec> ReadFile2Vec(std::string);
    //File name, returns pointer to array of Vec’s, int provides number of lines...
    static Vec *ReadFile2Vecp(std::string, int &);
};
#endif // __FCTOOLS_H__

//Fica a faltar implementar 'ReadFile2Vec' e 'ReadFile2Vecp' (e eventualmente rever o 'ReadFile2String'...)-> Done!