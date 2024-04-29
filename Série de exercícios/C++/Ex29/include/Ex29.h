#ifndef __pessoa__
#define __pessoa__

#include <iostream>
#include <string>

class pessoa
{
public:
    //constructor (nome do aluno, data de nascimento)
    pessoa(std::string name1 = "Afonso Sequeira Azenha", unsigned int date = 22042001) : name(new std::string(name1)), DataN(new unsigned int(date))
    {
        std::cout << "Construtor chamado (pessoa): (obj:" << this << ")" << std::endl;
    }
    virtual ~pessoa()
    {
        //std::cout << "Destrutor chamado (pessoa): (obj" << this << ")" << std::endl;
        delete name;
        delete DataN;
    }
    void SetName(std::string);
    void SetBornDate(unsigned int);
    std::string GetName();
    unsigned int GetBornDate();
    virtual void Print();

protected:
    std::string *name;   //nome
    unsigned int *DataN; //data de nascimento
};

class alunoIST : public pessoa
{
public:
    //constructor
    alunoIST();
    alunoIST(int number, std::string branch);

    //move constructor
    alunoIST(alunoIST &&) = default;

    //copy constructor
    alunoIST(const alunoIST &) = default;

    //move assignment
    alunoIST &operator=(alunoIST &&) = default;

    //copy assignment
    alunoIST &operator=(const alunoIST &) = default;

    //destructor
    ~alunoIST();

    //methods
    void SetNumber(int);
    int GetNumber();
    void Print();
    void SetBranch(std::string);
    std::string GetBranch();

private:
    int number;
    std::string branch;
};

pessoa **DoArray(int);

#endif
