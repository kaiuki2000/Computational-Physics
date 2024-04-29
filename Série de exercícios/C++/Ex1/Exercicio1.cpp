#include <iostream>
int main() {
    int a,b,c=0;
    std::cout << "Introduza um primeiro número: ";
    std::cin >> a;
    std::cout << "Introduza um segundo número: ";
    std::cin >> b;
    std::cout << "1º número: " << a << " | 2º número: " << b<< std::endl;
    if(a<=b)
    {
    for(int i = a; i <=b;i++)
    c+=i;
    std::cout << "A soma dos números entre " << a << " e " << b << " é " << c << std::endl;
    }
    else
    {
    for(int i = b; i <=a;i++)
    c+=i;   
    std::cout << "A soma dos números entre " << b << " e " << a << " é " << c << std::endl;
    }
    return 0;
}