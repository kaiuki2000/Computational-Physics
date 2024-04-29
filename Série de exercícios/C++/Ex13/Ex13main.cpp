#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    cout << "Cálculo da altitude de um satélite, dado o período do seu movimento de translação à volta da Terra..." << endl;
    const double G = 6.67e-11;
    const double M = 5.97e24;
    const double R = 6.371e6;
    double T = 0, h = 0;
    cout << "Introduza o período do satélite em segundos: ";
    cin >> T;
    h = pow((G * M * T * T) / (4 * M_PI * M_PI), 1 / 3.) - R;
    cout << "h= " << h << endl;
    return (0);
}