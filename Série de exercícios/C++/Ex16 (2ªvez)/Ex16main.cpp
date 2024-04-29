#include <iostream>
using namespace std;

void fsum(double const *const, int);
double fsumr(double const *const, int);

int main()
{
    double v[] = {1, 2, 3, 4, 5};
    fsum(v, 5);
    double sum = fsumr(v, 5);
    cout << "A soma dos elementos no array é: " << sum << ", utilizando a mesma função, após modificação do retorno (ver código)." << endl;
    return 0;
}

void fsum(double const *const v, int n) //A declaração double const* const v, faz com que não seja possível
{                                       //alterar os valores do array, nem as suas posições [dos valores] na memória (ponteiros)
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += v[i];
    cout << "A soma dos elementos no array é: " << sum << endl;
}

double fsumr(double const *const v, int n) //Esta função é exatamente igual à anterior, exceto que retorna o valor da soma, sum.
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += v[i];
    return sum;
}