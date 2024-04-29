#include <iostream>
#include <cmath>
//#include <cstdio> //getchar()
using namespace std;

//Pré-declaração das funções utilizadas
double f1(double);
void f2(double, double &);
void f3(double, double *);

int main()
{
    double x, fx;
    cout << "Cálculo da expressão:\nf(x)= sqrt(sin(2x))\n..." << endl;
    cout << "Introduza um valor para x (em graus): ";
    cin >> x;
    cout << "Valor lido para x: " << x << "° = " << (double)((x / 180) * M_PI) << " rad" << endl;
    cout << "\n1ºMétodo (passagem de x por cópia):\nf(x)= " << f1((double)((x / 180) * M_PI)) << endl;
    f2((double)((x / 180) * M_PI), fx);
    cout << "\n2ºMétodo (passagem de f(x) por referência):\nf(x)= " << fx << endl;
    f3((double)((x / 180) * M_PI), &fx);
    cout << "\n3ºMétodo (passagem de f(x) através de um ponteiro):\nf(x)= " << fx << endl;
    cout << "\nO programa vai agora terminar...\nPressione uma tecla..." << endl;
    getchar();
    getchar();
    return (0);
}

//Declaração das funções utilizadas
//f1(x é passado para dentro da função por cópia)
double f1(double const x)
{
    return (sqrt(sin(2 * x)));
}

//f2(fx1 é passado para dentro da função por referência)
void f2(double const x, double &fx)
{
    fx = sqrt(sin(2 * x));
}

//f3(fx2 é passado para dentro da função através de um ponteiro)
void f3(double const x, double *const fx) //o 'const' faz com que não seja possível alterar o ponteiro para fx (&fx))
{
    *fx = sqrt(sin(2 * x));
}