#include "Ex29.h"

int main()
{
    pessoa P[10];
    std::cout << "Impressão de P[O]:" << std::endl;
    P[0].Print();
    std::cout << std::endl;
    pessoa **PP = DoArray(3);
    for (int i = 0; i < 3; i++)
        PP[i]->Print();
    std::cout << "\n\n"
              << std::endl;
    alunoIST *Al = new alunoIST[5];
    for (int i = 0; i < 5; i++)
    {
        Al[i].Print();
    }
    return (0);
}
