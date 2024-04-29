#include "Ex28,29,30.h"

//Exercício 28***
pessoa::pessoa(std::string Name_, unsigned int DataN_) : Name(new std::string(Name_)), DataN(new unsigned int(DataN_))
{
    printf("[%s] 'Criação' de uma pessoa...(%p)\n", __PRETTY_FUNCTION__, this);
}

pessoa::~pessoa()
{
    printf("[%s] 'Destrução' de uma pessoa...(%p)\n", __PRETTY_FUNCTION__, this);
    delete Name;
    delete DataN;
}

void pessoa::Print() const
{
    printf("[%s] 'Impressão' de uma pessoa...()%p\n\n", __PRETTY_FUNCTION__, this);
    std::cout << "Nome: " << *Name << std::endl;
    std::cout << "Data de nascimento: " << *DataN << std::endl;
}

void pessoa::SetName(std::string Name_)
{
    *Name = Name_;
}

void pessoa::SetDataN(unsigned int DatanN_)
{
    *DataN = DatanN_;
}

std::string pessoa::GetName() const
{
    return *Name;
}

unsigned int pessoa::GetDataN() const
{
    return *DataN;
}

pessoa **DoArray(int N)
{
    pessoa **P_Array = new pessoa *[N];
    for (int i = 0; i < N; i++)
    {
        P_Array[i] = new pessoa("Nome de teste(P_Array)", 123);
    }
    return P_Array;
}

//Exercício 29***
AlunoIST::AlunoIST(std::string Nome_, unsigned int DataN_, int Number_, std::string Major_) : pessoa(Nome_, DataN_),
                                                                                              Number(new int(Number_)), Major(new std::string(Major_))
{
    printf("[%s] 'Criação' de um AlunoIST...(%p)\n", __PRETTY_FUNCTION__, this);
}

AlunoIST::~AlunoIST()
{
    printf("[%s] 'Destrução' de um AlunoIST...(%p)\n", __PRETTY_FUNCTION__, this);
    delete Number;
    delete Major;
}

void AlunoIST::Print() const
{
    printf("[%s] 'Impressão' de um AlunoIST...(%p)\n\n", __PRETTY_FUNCTION__, this);
    std::cout << "Nome: " << *Name << std::endl;
    std::cout << "Data de nascimento: " << *DataN << std::endl;
    std::cout << "Número: " << *Number << std::endl;
    std::cout << "Curso: " << *Major << std::endl;
}

void AlunoIST::SetNumber(int Number_)
{
    *Number = Number_;
}

void AlunoIST::SetMajor(std::string Major_)
{
    *Major = Major_;
}

int AlunoIST::GetNumber() const
{
    return *Number;
}

std::string AlunoIST::GetMajor() const
{
    return *Major;
}

void Dummy(std::vector<pessoa *> pObj)
{
    for (auto i : pObj)
    {
        i->Print();
        std::cout << std::endl;
    }
}

//Exercício 30***

Turma::Turma(std::string Tnome_, int nAlunos_) : Tnome(Tnome_), nAlunos(nAlunos_)
{
    printf("[%s] 'Criação' de uma Turma...(%p)\n", __PRETTY_FUNCTION__, this);
    T.reserve(nAlunos_);

    /*for (int i = 0; i < nAlunos_; i++)
    {
        T[i] = new AlunoIST;
    }*/
}

Turma::~Turma()
{
    printf("[%s] 'Destruição' de uma Turma...(%p)\nTamanho de T (nº de alunos da turma): %ld\n", __PRETTY_FUNCTION__, this, T.size());

    /*for (int i = 0; i < nAlunos; i++)
    {
        delete T[i];
    }
    delete[] T;*/

    T.clear();
}

Turma::Turma(const Turma &Turma_) : Tnome(Turma_.Tnome), nAlunos(Turma_.nAlunos)
{
    printf("[%s] 'Criação' de uma Turma com o 'copy constructor'...(%p)\n", __PRETTY_FUNCTION__, this);
    T.reserve(Turma_.nAlunos);
}

Turma &Turma::operator=(const Turma &Turma_)
{
    printf("[%s] Utilização do copy assignment...(%p)\n", __PRETTY_FUNCTION__, this);

    if (this != &Turma_)
    {
        T = Turma_.T;
        Tnome = Turma_.Tnome;
        nAlunos = Turma_.nAlunos;
    }
    return (*this);
}

void Turma::AddAlunoIST(AlunoIST *const A)
{
    T.push_back(A);
}

void Turma::Print() const
{
    printf("[%s] 'Impressão' de uma Turma...(%p)\n\n", __PRETTY_FUNCTION__, this);
    std::cout << "Nome da turma: " << Tnome << std::endl;
    std::cout << "Número de alunos: " << T.size() << std::endl;
    std::cout << "Alunos:\n\n";
    if (T.size() != 0)
    {
        for (int i = 0; i < (int)T.size(); i++)
            T[i]->Print();
    }
}

void Turma::SetTname(std::string name_)
{
    printf("[%s] Utilização da função SetTname...(%p)\n", __PRETTY_FUNCTION__, this);
    Tnome = name_;
}

AlunoIST *Turma::FindAluno(int Number_)
{
    printf("[%s] Utilização da função FindAluno...(%p)\n", __PRETTY_FUNCTION__, this);
    for (auto i : T)
    {
        if (i->GetNumber() == Number_)
        {
            return (i);
        }
    }
}
