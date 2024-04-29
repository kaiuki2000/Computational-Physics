#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int *f1();
int &f2();

int main()
{
    srand(time(NULL));
    int *x = f1();
    cout << "Endereço da variável após passagem para fora da 1ª função: " << x << endl;
    cout << "1º valor aleatório gerado: " << *x << endl;
    int &y = f2();
    cout << "Endereço da variável após passagem para fora da 2ª função: " << &y << endl;
    cout << "2º valor aleatório gerado: " << y << endl;
    delete x;
    delete &y;
    return (0);
}

int *f1()
{
    int *x = new int(rand());
    cout << "Endereço da variável gerada no interior da 1ª função: " << x << endl;
    return x;
}

int &f2()
{
    int *x = new int(rand());
    cout << "Endereço da variável gerada no interior da 2ª função: " << x << endl;
    return *x;
}
