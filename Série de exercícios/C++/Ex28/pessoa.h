#include <iostream>
#include <string>

#ifndef __pessoa__
#define __pessoa__
class pessoa
{
public:
    //constructor (nome do aluno, data de nascimento)
    pessoa(std::string name1 = "Afonso Sequeira Azenha", unsigned int date = 22042001) : name(new std::string(name1)), DataN(new unsigned int(date))
    {
        std::cout << "Construtor chamado: (obj:" << this << ")" << std::endl;
    }
    ~pessoa()
    {
        std::cout << "Destrutor chamado: (obj" << this << ")" << std::endl;
        delete name;
        delete DataN;
    }
    void SetName(std::string);      //set name
    void SetBornDate(unsigned int); //nascimento
    std::string GetName();          //get name
    unsigned int GetBornDate();
    void Print(); // print
private:
    std::string *name;   //nome
    unsigned int *DataN; //data de nascimento
};

pessoa **DoArray(int);

#endif
