#include <iostream>
using namespace std;

//Pré-declaração das funções
int *f1(int);
double *f2(int);
int **f3(int, int);
double ***f4(int, int, int);
void printa(int *, int);
void printb(double *, int);
void printc(int **, int, int);
void printd(double ***, int, int, int);

int main()
{
    //Chamada das funções para criação dos arrays
    int *a = f1(100);
    double *b = f2(100);
    int **c = f3(4, 3);
    double ***d = f4(5, 4, 3);

    //Impressão dos resultados
    printa(a, 100);
    cout << endl;
    printb(b, 100);
    cout << endl;
    printc(c, 4, 3);
    cout << endl;
    printd(d, 5, 4, 3);

    //Delete dos arrays
    delete[] a;
    delete[] b;

    //Delete da matriz de ints
    for (int i = 0; i < 4; i++)
    {
        delete[] c[i];
    }
    delete[] c;

    //Delete do tensor de doubles (dimensão 3)
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
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

//Funções para impressão dos resultados
//Impressão de a (array de ints)
void printa(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "a[" << i << "]= " << a[i] << endl;
    }
}

//Impressão de b (array de doubles)
void printb(double *b, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "b[" << i << "]= " << b[i] << endl;
    }
}

//Impressão de c (matriz de ints)
void printc(int **c, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << "c[" << i << "][" << j << "]= " << c[i][j] << "  ";
        }
        cout << endl;
    }
}

//Impressão de d (tensor de doubles (dimensão 3))
void printd(double ***d, int m, int n, int o)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < o; k++)
            {
                cout << "d[" << i << "][" << j << "][" << k << "]= " << d[i][j][k] << "  ";
            }
            cout << endl;
        }
        cout << endl;
    }
}