#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    srand(time(NULL));
    vector<double> vx(1000);
    vector<double> vy;
    double y, sum, mean, sumdesv, desviopadrao;

    for (auto &i : vx)
    {
        i = ((double)rand() / (double)RAND_MAX) * 50 + 5;
        y = i / (i - 10);
        vy.push_back(y);
    }

    for (auto i = vx.begin(); i != vx.end(); i++)
    {
        cout << setw(8) << fixed;
        cout << "vx[" << i - vx.begin() << "]= " << vx[i - vx.begin()] << "   ";
        if ((int)(i - vx.begin() + 1) % 3 == 0)
            cout << endl;
    }

    cout << endl;

    for (auto i = vy.begin(); i != vy.end(); i++)
    {
        cout << setw(8) << fixed;
        cout << "vy[" << i - vy.begin() << "]= " << vy[i - vy.begin()] << "   ";
        if ((int)(i - vx.begin() + 1) % 3 == 0)
            cout << endl;
    }

    cout << endl;

    for (auto i : vx)
        sum += i;

    for (auto i : vx)
        sumdesv += pow(i - mean, 2);

    desviopadrao = sqrt(sumdesv / 1000);
    mean = (double)(sum / 1000);
    cout << "Média dos valores de x: " << mean << endl;
    cout << "sumdesv=                " << sumdesv << endl;
    cout << "Desvio padrão de x:     " << desviopadrao << endl;

    return (0);
}
