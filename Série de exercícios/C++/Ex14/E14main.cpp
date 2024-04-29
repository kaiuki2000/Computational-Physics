#include <iostream>
using namespace std;

//Protótipo das funções
int *fintv(int);
double *fdoublev(int);
int **fintvM(int, int);
double ***fdoublevM(int, int, int);
void printtensor(double ***, int, int, int);

//Função main
int main()
{
    int *a = fintv(100);
    double *b = fdoublev(100);
    int **c = fintvM(10, 5);
    double ***d = fdoublevM(10, 5, 2);

    //Imprimir array unidimensional
    /*for (int j = 0; j < 100; j++)
        cout << "a[" << j << "]: " << a[j] << endl;*/

    //Imprimir array bidimensional (matriz)
    /*for (int j = 0; j < 10; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            cout << "c[" << j << "][" << k << "]= " << c[j][k] << "; ";
        }
        cout << endl;
    }*/

    //Imprimir array tridimensional (tensor)
    /*for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                cout << "d[" << i << "][" << j << "][" << k << "]= " << d[i][j][k] << "; ";
            }
            cout << endl;
        }
        cout << endl;
    }*/

    printtensor(d, 10, 5, 2);

    delete[] a;
    delete[] b;
    for (int i = 0; i < 10; i++)
    {
        delete[] c[i];
    }
    delete[] c;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            delete[] d[i][j];
        }
    }

    for (int i = 0; i < 5; i++)
    {
        delete[] d[i];
    }
    delete[] d;

    return (0);
}

//Funções fintv e fdoublev
int *fintv(int n)
{
    int *v = new int[n];
    for (int i = 0; i < 100; i++)
        v[i] = i;
    return (v);
}

double *fdoublev(int n)
{
    double *v = new double[n];
    return (v);
}

//Funções fintvM e fdoubleM
int **fintvM(int m, int n)
{
    int **v = new int *[m];
    for (int i = 0; i < m; i++)
        v[i] = new int[n];

    for (int j = 0; j < m; j++)
    {
        for (int k = 0; k < n; k++)
        {
            v[j][k] = 1;
        }
    }
    return (v);
}

double ***fdoublevM(int m, int n, int l)
{
    double ***v = new double **[m];
    for (int i = 0; i < m; i++)
    {
        v[i] = new double *[n];
        for (int j = 0; j < n; j++)
            v[i][j] = new double[l];
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < l; k++)
            {
                v[i][j][k] = 5;
            }
        }
    }
    return v;
}

//Função printtensor
void printtensor(double ***d, int m, int n, int l)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < l; k++)
            {
                cout << "d[" << i << "][" << j << "][" << k << "]= " << d[i][j][k] << "; ";
            }
            cout << endl;
        }
        cout << endl;
    }
}
