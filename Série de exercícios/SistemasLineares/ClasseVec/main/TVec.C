#include "Vec.h"

int main()
{
    //Constructor tests
    //***
    double *vals = new double[5]{1, 2, 3, 4, 5};
    double *nul = nullptr;

    std::cout << std::endl;

    Vec v1;
    std::cout << "Accessing v1 elements: " << v1 << std::endl;
    //v1[0] = 4; Testes...
    Vec v2(5, 3);
    std::cout << "Accessing element v2[0]: v2[0]= " << v2[0] << std::endl;
    std::cout << "Accessing v2 elements: " << v2 << std::endl;
    std::cout << "Altering v2[0] from " << v2[0] << " to 4..." << std::endl;
    v2[0] = 4;
    std::cout << "Accessing element v2[0]: v2[0]= " << v2[0] << std::endl;
    std::cout << "Accessing v2 elements: " << v2 << std::endl;
    Vec v3(5, vals);
    Vec v4(v2);
    Vec v5(3, 12);
    v5 = v3;
    //v4 = v1; Testes...
    //Vec v6(0, nul); Testes...

    delete[] vals;
    //***

    //SetEntries && size methods
    //***
    std::cout << "v4.size()= " << v4.size() << std::endl;
    v4.SetEntries(5, nul);
    std::cout << "v4.size()= " << v4.size() << std::endl;
    //***

    //operator+= tests && operator-= tests
    std::cout << "Accessing v3 elements: " << v3 << std::endl;
    std::cout << "Accessing v5 elements: " << v5 << std::endl;
    v3 += v5; //Equivalent to v3.operator+=(v5);
    std::cout << "Accessing v3 elements: " << v3 << std::endl;
    std::cout << "Accessing v5 elements: " << v5 << std::endl;
    v5 -= v3; //Equivalent to v5.operator-=(v3);
    std::cout << "Accessing v3 elements: " << v3 << std::endl;
    std::cout << "Accessing v5 elements: " << v5 << std::endl;
    /*Vec v6(7);
    std::cout << "Accessing v6 elements: " << v6 << std::endl;
    v3 += v6; Testes...*/
    //v3 += v1; Testes...

    //operator* tests
    v3 = v3 * 0.725;
    std::cout << "Accessing v3 elements: " << v3 << std::endl;
    //v1 = v1 * 3; Testes...

    //operator*= tests && operator/= tests
    //std::cout << "Accessing v3 elements: " << v3 << std::endl;
    v3 *= 24; //Equivalent to v3.operator*=(24);
    std::cout << "Accessing v3 elements: " << v3 << std::endl;
    std::cout << "Accessing v5 elements: " << v5 << std::endl;
    v5 /= 3; //Equivalent to v5.operator-=(v3);
    std::cout << "Accessing v5 elements: " << v5 << std::endl;
    //v1 /= 5; Testes...

    //Testing Vec.maxAbs...
    Vec a;
    double *a1 = new double[5]{-9, 3, 6, 0, -2};
    a.SetEntries(5, a1);
    std::cout << a << std::endl;
    std::cout << "a's biggest value: " << a.maxAbs() << std::endl;
    std::cout << "|a's biggest value|= " << fabs(a.maxAbs()) << std::endl;

    //Testing swap method...
    std::cout << "vector a: " << std::endl;
    std::cout << a << std::endl;
    std::cout << "Swapping 1st and 4th elements of a... " << std::endl;
    a.swap(0, 3);
    std::cout << a << std::endl;

    //Testing push_back method...
    a.push_back(4);
    std::cout << a << std::endl;
    a.push_back(-3.57);
    std::cout << a << std::endl;
    a.push_back(20.5789);
    std::cout << a << std::endl;
    a.push_back(0);
    std::cout << a << std::endl;
    a.swap(5, 7); //Random swap to check for errors...
    std::cout << a << std::endl;

    //Testing Vec.clear() method...
    Vec empty;
    std::cout << empty << std::endl;
    empty.push_back(2);
    std::cout << empty << std::endl;
    empty.push_back(3);
    empty.push_back(5);
    std::cout << empty << std::endl;
    empty.clear();

    std::cout << empty << std::endl;
    empty.push_back(2);
    std::cout << empty << std::endl;
    empty.push_back(3);
    empty.push_back(5);
    std::cout << empty << std::endl;

    return (0);
}