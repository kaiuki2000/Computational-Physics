#include <iostream>
using namespace std;

int fact (int);

int main() {
    int n,nfact;
    cout << "Introduza um número natural, n, para o cálculo de n!: ";
    cin >> n;
    nfact= fact (n);
    cout << n << "!= " << nfact << endl;
    return (0);
}