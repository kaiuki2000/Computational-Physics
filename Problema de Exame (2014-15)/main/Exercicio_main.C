#include <iostream>

using namespace std;

class vector
{
public:
    vector()
    {
        size = 5;
        vec = new double[size];
    }
    ~vector() { ; }
    double *GetVector()
    {
        return vec;
    }

    int GetSize() { return size; };

private:
    double *vec;
    int size;
};

int main()
{
    vector V;
    //print vector
    for (int i = 0; i < V.GetSize(); i++)
    {
        cout << V.GetVector()[i] << endl;
    }
    //get array defined inside vector and delete it
    double *f = V.GetVector();
    delete f;
}