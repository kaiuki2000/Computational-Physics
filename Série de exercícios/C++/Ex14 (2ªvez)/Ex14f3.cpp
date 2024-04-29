//Função para criar uma matriz de ints
int **f3(int m, int n)
{
    int **c = new int *[m];
    for (int i = 0; i < m; i++)
    {
        c[i] = new int[n];
    }

    //Inicialização da matriz a 3 (todos os elementos são 3)
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = 3;
        }
    }
    return c;
}