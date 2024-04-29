#include <iostream>
using namespace std;

double Trace(int[][2], int, int);
int *Mrow(int, int[][3], int, int);

int main()
{
    int mx[][2] = {
        {2, 10},
        {5, 7}};
    double trace = Trace(mx, 2, 2);
    cout << trace << endl;
    int mx1[][3] = {
        {2, 10, 5},
        {3, 2, 7}};
    int *linhai = Mrow(0, mx1, 2, 3);
    for (int i = 0; i < 3; i++)
        cout << linhai[i] << " ";
    return 0;
}

double Trace(int mx[][2], int m, int n)
{
    double trace = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                trace += mx[i][j];
        }
    }
    return trace;
}

int *Mrow(int i, int mx[][3], int m, int n)
{
    return (mx[i]);
}

//Incompleto!