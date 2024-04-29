#include <iostream>
using namespace std;

void sum (const double* const , int);

int main(){
double v[10]= {1,2,3,4,5,6,7,8,9,10};   
sum (v,10);
}

void sum (const double* const v, int n)
 {
     double sum = 0;
     for (int i = 0; i < n; i++)
     sum+= v[i];
     cout << "A soma dos elementos do array dá: " << sum << endl;
 }