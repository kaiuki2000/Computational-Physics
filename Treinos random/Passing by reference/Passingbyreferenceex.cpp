#include <iostream>
using namespace std;

void factorial (int, double&);

int main () {
    int n = 4;
    double d = 1;
    factorial (n, d);
    cout << n << "!= " << d << endl;
    return (0);
}

void factorial (int n, double& fact){
    for (int count = n; count > 0; count--) {
        fact *= (double)count;
    }
}