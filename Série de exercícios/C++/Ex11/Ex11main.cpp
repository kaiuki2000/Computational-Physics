#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
    double sum = 0;
    cout << "Soma de 0.1 + 0.2 + 0.3 + ... + 5.2 + 5.3 + 5.4" << endl;
    for (double x = 0; abs(x - 5.5) > 0.09; x += 0.1)
    {
        sum += x;
        //cout << "sum= " << sum << endl;
    }
    cout << "sum= " << sum << endl;
    cout << "O programa vai agora terminar..." << endl;
    return (0);
}