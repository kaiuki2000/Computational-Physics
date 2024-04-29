//Função para criar um array de ints
int *f1(int n)
{
    int *a = new int[n];
    for (int i = 0; i < n; i++)
        a[i] = 1;
    return a;
}