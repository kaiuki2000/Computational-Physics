#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int* randomint ();
int& randomint2 ();

int main() {
srand(time(NULL));
int *randomn = randomint ();
cout << "1º número aleatório gerado: " << *randomn <<endl;
cout << "Endereço: " << randomn << endl;
delete randomn;

int& randomn2 = randomint2 ();
cout << "2º número aleatório gerado: " << randomn2 <<endl;
cout << "Endereço: " << &randomn2 << endl;
delete &randomn2;

return(0);
}

int* randomint () {
    int *r = new int(rand());
    return (r);
}

int& randomint2 () {
    int *r = new int(rand());
    return (*r);
}