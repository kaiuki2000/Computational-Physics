#include "pessoa.h"

//constructor (nome do aluno, data de nascimento)
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
