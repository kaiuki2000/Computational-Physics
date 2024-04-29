#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int v[] = {1, 2, 3, 4, 5};
    vector<int> vec(v, v + 5);
    for (auto i = vec.begin(); i != vec.end(); i++) //'auto' neste caso é algo do genéro: std::vector<int>::interator
        cout << "v[" << i - vec.begin() << "]= " << *i << endl;

    for (auto &i : vec)
        i *= 2;
    cout << endl;
    for (auto i = vec.begin(); i != vec.end(); i++)
        cout << "v[" << i - vec.begin() << "]= " << *i << endl;

    return (0);
}