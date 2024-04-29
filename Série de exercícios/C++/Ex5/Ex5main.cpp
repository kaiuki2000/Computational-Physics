#include <iostream>
#include <limits>
using namespace std;

int main()
{
    cout << "Limites das variáveis dos tipos <int>, <unsigned int>, <float> e <double>:" << endl;
    cout << "Valor máximo de <int>: " << numeric_limits<int>::max() << endl;
    cout << "Valor mínimo de <int>: " << numeric_limits<int>::min() << endl;
    cout << endl;
    cout << "Valor máximo de <unsigned int>: " << numeric_limits<unsigned int>::max() << endl;
    cout << "Valor mínimo de <unsigned int>: " << numeric_limits<unsigned int>::min() << endl;
    cout << endl;
    cout << "Valor máximo de <float>: " << numeric_limits<float>::max() << endl;
    cout << "Valor mínimo de <float>: " << numeric_limits<float>::min() << endl;
    cout << endl;
    cout << "Valor máximo de <double>: " << numeric_limits<double>::max() << endl;
    cout << "Valor mínimo de <double>: " << numeric_limits<double>::min() << endl;
    cout << "O programa vai agora terminar..." << endl;
    return (0);
}