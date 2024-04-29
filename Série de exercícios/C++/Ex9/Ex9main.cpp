#include <iostream>
using namespace std;

double sum(int *, int *);

int main()
{
    int *vi = new int[2];
    int *vj = new int[2];

    cout << "Introduza os limites de i: (Escreva na forma: 'vi[0] vi[1]') ";
    cin >> vi[0] >> vi[1];
    cout << "Valores lidos: " << vi[0] << " " << vi[1] << endl;

    cout << "Introduza agora os limites de j: (Escreva na forma: 'vj[0] vj[1]') ";
    cin >> vj[0] >> vj[1];
    cout << "Valores lidos: " << vj[0] << " " << vj[1] << endl;

    double sum1 = sum(vi, vj);

    cout << "O resultado deu: " << sum1 << endl;

    delete[] vi;
    delete[] vj;
    return (0);
}