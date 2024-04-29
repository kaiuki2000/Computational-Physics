#include <iostream>
using namespace std;
int addnumbers(int a, int b)
{
    int sum = 0;

    for (int i = a; i <= b; i++)
        sum += i;

    return sum;
}

int main()
{
    int n1, n2, sum;
    cout << "Introduza um primeiro número: ";
    cin >> n1;
    cout << "Introduza um segundo número: ";
    cin >> n2;

    if (n2 > n1)
    {
        sum = addnumbers(n1, n2);
        cout << "O resultado da soma dos números entre " << n1 << " e " << n2 << " é: " << sum << endl;
    }
    else
    {
        sum = addnumbers(n2, n1);
        cout << "O resultado da soma dos números entre " << n2 << " e " << n1 << " é: " << sum << endl;
    }
    return 0;
}
