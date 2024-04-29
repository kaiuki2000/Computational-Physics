#include <iostream>
#include <cmath>
using namespace std;

double funccopy (double);
void funcreference (double&);
void funcpointer (double*);

int main() {
    double x,x1,x2,x3;
cout << "Introduza uma valor para x: ";
cin >> x;

x1= funccopy (x);
printf("funccopy: sqrt(sin(2*%f))= %f\n", x,x1);

x2=x;
funcreference(x2);
printf("funcreference: sqrt(sin(2*%f))= %f\n", x,x2);

x3=x;
funcpointer(&x3);
printf("funcponter: sqrt(sin(2*%f))= %f\n", x,x3);
return (0);
}

double funccopy (const double x)
{
double a =(sqrt(sin(2*(x*M_PI/180))));
return(a);
}

void funcreference (double& x)
{
x= sqrt(sin(2*(x*M_PI/180)));
}

void funcpointer (double* x)
{
*x= sqrt(sin(2*(*x*M_PI/180)));
}