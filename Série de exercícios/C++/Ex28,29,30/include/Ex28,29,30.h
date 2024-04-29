#ifndef __EX282930__
#define __EX282930__

#include <string>
#include <iostream>
#include <cstdio>
#include <vector>

//Exercício 28***
class pessoa
{
public:
    pessoa(std::string Name_ = "Afonso Azenha", unsigned int DataN_ = 22042001); //Construtor
    virtual ~pessoa();                                                           //Destrutor
    virtual void Print() const;                                                  //Print
    void SetName(std::string);                                                   //SetName
    void SetDataN(unsigned int);                                                 //SetDataN
    std::string GetName() const;                                                 //GetName
    unsigned int GetDataN() const;                                               //GetDataN

protected:
    std::string *Name;
    unsigned int *DataN;
};

pessoa **DoArray(int N);

//Exercício 29***
class AlunoIST : public pessoa
{
public:
    AlunoIST(std::string Nome_ = "Nuno", unsigned int DataN_ = 17102001, int Number_ = 2, std::string Major_ = "MEFT"); //Construtor
    ~AlunoIST();                                                                                                        //Destrutor
    void Print() const;                                                                                                 //Print
    void SetNumber(int);                                                                                                //SetNumber
    void SetMajor(std::string);                                                                                         //SetMajor
    int GetNumber() const;                                                                                              //GetNumber
    std::string GetMajor() const;                                                                                       //GetMajor                                                                                               //GetMajor

protected:
    int *Number;
    std::string *Major;
};

void Dummy(std::vector<pessoa *>);

//Exercício 30***

class Turma
{
public:
    Turma(std::string Tnome_ = "MEFT_T1", int nAlunos_ = 2); //Construtor
    ~Turma();                                                //Destrutor
    Turma(const Turma &);                                    //Copy constructor
    Turma &operator=(const Turma &);                         //Copy assignment
    void AddAlunoIST(AlunoIST *const);
    void Print() const;
    void SetTname(std::string);
    AlunoIST *FindAluno(int);

private:
    std::vector<AlunoIST *> T;
    std::string Tnome;
    int nAlunos;
};

#endif // __EX28,29,30_H__