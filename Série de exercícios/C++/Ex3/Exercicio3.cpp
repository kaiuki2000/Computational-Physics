#include <iostream>
using namespace std;

int main()
{
    cout << "Tamanho de 'short int':    " << sizeof(short int) << " bytes" << endl;
    cout << "Tamanho de 'int':          " << sizeof(int) << " bytes" << endl;
    cout << "Tamanho de 'long int':     " << sizeof(long int) << " bytes" << endl;
    cout << "Tamanho de 'unsigned int': " << sizeof(unsigned int) << " bytes" << endl;
    cout << "Tamanho de 'float':        " << sizeof(float) << " bytes" << endl;
    cout << "Tamanho de 'double':       " << sizeof(double) << " bytes" << endl;
    cout << "Tamanho de 'long double':  " << sizeof(long double) << " bytes" << endl;
    return 0;
}