#include "Ex29.h"

void pessoa::SetName(std::string name1) //set name
{
    std::cout << "pessoa::SetName(std::string name1)" << std::endl;
    *name = name1;
}
void pessoa::SetBornDate(unsigned int date) //nascimento
{
    std::cout << "pessoa::SetBornDate(unsigned int date)" << std::endl;
    *DataN = date;
}
std::string pessoa::GetName() //get name
{
    std::cout << "pessoa::GetName()" << std::endl;
    return *name;
}
unsigned int pessoa::GetBornDate() //get born date
{
    std::cout << "pessoa::GetBornDate()" << std::endl;
    return *DataN;
}
void pessoa::Print() // print
{
    std::cout << "pessoa::Print()" << std::endl;
    std::cout << "Nome: " << *name << "\nData de nascimento: " << *DataN << std::endl;
}

//função para criar array de N ponteiros para pessoas
pessoa **DoArray(int N)
{
    pessoa **PP = new pessoa *[N];
    for (int i = 0; i < N; i++)
    {
        PP[i] = new pessoa("Haha", 123);
    }
    return PP;
}

void alunoIST::SetNumber(int n)
{
    std::cout << "alunoIST::SetNumber(int n)" << std::endl;
    number = n;
}

int alunoIST::GetNumber()
{
    std::cout << "alunoIST::GetNumber()" << std::endl;
    return number;
}

void alunoIST::Print()
{
    std::cout << "pessoa::alunoIST()" << std::endl;
    std::cout << "Nome: " << *name << "\nData de nascimento: " << *DataN << std::endl;
    std::cout << "Número: " << number << "\nCurso: " << branch << std::endl;
}

void alunoIST::SetBranch(std::string s)
{
    std::cout << "alunoIST::SetBranch(std::string s)" << std::endl;
    branch = s;
}

alunoIST::alunoIST() : pessoa(), number(96502), branch("MEFT")
{
    std::cout << "Construtor chamado (alunoIST)" << std::endl;
}

alunoIST::alunoIST(int number_, std::string branch_) : pessoa(), number(number_), branch(branch_)
{
    std::cout << "Construtor chamado (alunoIST)" << std::endl;
}

std::string alunoIST::GetBranch()
{
    std::cout << "alunoIST::GetBranch()" << std::endl;
    return branch;
}
