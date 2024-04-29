//Função para criar um array de doubles
double *f2(int n)
{
    double *b = new double[n];
    for (int i = 0; i < n; i++)
        b[i] = 2;
    return b;
}