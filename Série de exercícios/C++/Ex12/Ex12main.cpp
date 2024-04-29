#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    cout << "Cálculo do tempo de queda (livre), dada a altura, h, ..." << endl;
    double h = 0, t = 0;
    const double g = 9.8;
    cout << "Introduza a altura, h, da qual o objeto cai: ";
    cin >> h;
    t = sqrt((2 * h) / g);
    cout << "Tempo de queda (livre)= " << t << endl;
    return (0);
}