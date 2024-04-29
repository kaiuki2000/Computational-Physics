#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    cout << fixed << setprecision(20);
    cout << "Valor de Pi com precisão de 'float':  " << (float) atan2(0,-1) << endl;
    cout << "Valor de Pi com precisão de 'double': " << (double) atan2(0,-1) << endl;
    cout << "Valor verdadeiro de Pi:               " << M_PI << endl;
    return(0);
}