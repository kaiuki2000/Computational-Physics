//Função para criar um tensor de dimensão 3 de doubles
double ***f4(int m, int n, int o)
{
    double ***d = new double **[m];
    for (int i = 0; i < m; i++)
    {
        d[i] = new double *[n];
        for (int j = 0; j < n; j++)
        {
            d[i][j] = new double[o];
        }
    }

    //Inicialização do tensor a 4 (todos os elementos são 4)
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < o; k++)
            {
                d[i][j][k] = 4;
            }
        }
    }

    return d;
}