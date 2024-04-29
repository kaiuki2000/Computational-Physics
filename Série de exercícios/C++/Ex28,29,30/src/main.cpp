#include "Ex28,29,30.h"

int main()
{
	//Exercício 28***
	std::cout << "***(Ex.28)***\n"
			  << std::endl;
	pessoa Afonso;
	Afonso.Print();
	std::cout << "\nTeste das funções GetName() e GetDataN():\nNome do objeto criado: " << Afonso.GetName()
			  << "\nDataN do objeto criado: " << Afonso.GetDataN() << std::endl;
	std::cout << "\nAlteração do Nome e DataN..." << std::endl;
	Afonso.SetName("Afuzzy");
	Afonso.SetDataN(420);
	std::cout << "\nTeste das funções GetName() e GetDataN():\nNome do objeto criado: " << Afonso.GetName()
			  << "\nDataN do objeto criado: " << Afonso.GetDataN() << "\n"
			  << std::endl;
	std::cout << "Criação de um array de 10 pessoas..." << std::endl;
	pessoa *PP = new pessoa[10];
	std::cout << "\nDestruição de um array de 10 pessoas..." << std::endl;
	delete[] PP;

	std::cout << "\nCriação de um array de 3 ponteiros para pessoas..." << std::endl;
	pessoa **Teste = DoArray(3);

	std::cout << "\nImpressão das pessoas criadas..." << std::endl;
	for (int i = 0; i < 3; i++)
	{
		Teste[i]->Print();
		std::cout << std::endl;
	}

	std::cout << "Destruição das pessoas criadas..." << std::endl;
	for (int i = 0; i < 3; i++)
	{
		delete Teste[i];
	}
	delete[] Teste;

	//Exercício 29***
	std::cout << "\n***(Ex.29)***\n"
			  << std::endl;
	AlunoIST NunoMEFT;
	NunoMEFT.Print();
	std::cout << std::endl;

	AlunoIST *BoysMEFT = new AlunoIST[2]{{"Afonso Azenha", 22042001, 1, "MEFT"}, {"Guilherme Gaspar", 12345678, 3, "MEFT"}};
	BoysMEFT[0].Print();
	BoysMEFT[1].Print();
	std::cout << std::endl;

	//Teste ao polimorfismo?
	pessoa *Carolina = new AlunoIST("Carolina Azenha", 22042001, 4, "MEBiol");
	Carolina->Print();
	std::cout << std::endl;

	std::vector<pessoa *> pp = {Carolina};
	pp.push_back(&BoysMEFT[0]);
	pp.push_back(&BoysMEFT[1]);
	Dummy(pp);

	//delete Carolina;
	//delete[] BoysMEFT;
	pp.clear();

	//Exercício 30***
	std::cout << "\n***(Ex.30)***\n"
			  << std::endl;

	Turma *MEFT_T1 = new Turma;
	std::cout << std::endl;
	MEFT_T1->Print();
	std::cout << "Fim da 1ª impressão...\n"
			  << std::endl;
	MEFT_T1->AddAlunoIST(&BoysMEFT[0]);
	MEFT_T1->Print();
	std::cout << "Fim da 2ª impressão...\n"
			  << std::endl;
	MEFT_T1->AddAlunoIST(&BoysMEFT[1]);
	MEFT_T1->Print();
	std::cout << "Fim da 3ª impressão...\n"
			  << std::endl;
	MEFT_T1->SetTname("Nome de Teste 123");
	MEFT_T1->AddAlunoIST((AlunoIST *)Carolina);
	Turma *MEFT_T2 = new Turma;
	std::cout << std::endl;
	*MEFT_T2 = *MEFT_T1;
	std::cout << std::endl;
	MEFT_T2->Print();
	std::cout << std::endl;
	(MEFT_T2->FindAluno(4))->Print();
	std::cout << std::endl;
	delete MEFT_T1;
	std::cout << std::endl;
	delete MEFT_T2;
	std::cout << std::endl;
	delete[] BoysMEFT;
	delete Carolina;

	/*Turma *MEFT_T2 = new Turma("MEFT_T2", 1);
	std::cout << std::endl;

	Turma *MEFT_T3 = new Turma;
	std::cout << std::endl;
	*MEFT_T3 = *MEFT_T2; //Equivalente a: MEFT_T3->operator=(*MEFT_T2); (copy assignment)
	std::cout << std::endl;

	delete MEFT_T1;
	std::cout << std::endl;
	delete MEFT_T2;
	delete MEFT_T3;*/

	//Destruição de objetos em memória 'heap'
	std::cout << "\nDestruição de objetos em memória 'heap'..." << std::endl;
	return 0;
}

//Ficou a faltar implementar o copy constructor, o copy assignment
//e os outros 3 métodos referidos no enunciado,
//bem como fazer as alíneas b) e c) do exercício 30.