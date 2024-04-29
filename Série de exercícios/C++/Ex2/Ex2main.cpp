#include "funcEx2.h"
#include <iostream>
using namespace std;

int main ()
{
    double x;
    cout << "Introduza o valor de x para calcular a expressão:\nz(x)= x + f(x),\ncom f(x)= sin²(x)"<< endl;
    cin >> x;
    cout << "z(" << x << ")= " << x+ function(x)<< endl;
    return(0);
}