#include "point2D.h"

#include <vector>
//#include <algorithm>

int main()
{
    vector<point *> v;

    v.push_back(new point1D(10.));
    v.push_back(new point2D(4., 4.));
    v.push_back(new point1D(1.));
    v.push_back(new point2D(3., 3.));
    v.push_back(new point2D(2., 3.));
    v.push_back(new point2D(5., 3.));
    v.push_back(new point2D(1., 3.));
    v.push_back(new point1D(5.));
    v.push_back(new point1D(4.));
    v.push_back(new point2D(10., 5.));

    //imprimir a lista de pontos tal como foi introduzida
    for (int i = 0; i < v.size(); i++)
    {
        v[i]->Print();
    }
    cout << endl;

    //calcular a norma de cada ponto, seriar e imprimir os pontos no sentido crescente da norma
    vector<double> normas;

    for (int i = 0; i < v.size(); i++)
    {
        normas.push_back(v[i]->Norma());
    }

    cout << "\n\nPrint das normas obtidas: " << endl;
    for (int i = 0; i < normas.size(); i++)
    {
        cout << "normas[" << i << "]= " << normas[i] << endl;
    }

    /*double a = 0.;
    for (int i = 0; i < normas.size(); i++)
    {
        if (i == 0)
            a = normas[i];
        else
        {
            if (a < normas[i])
            {
                a = normas[i];
            }
        }
    }

    cout << "\nmaior norma= " << a << endl;*/

    int c = 1;
    while (c)
    {
        c = 0;
        for (int i = 0; i < normas.size() - 1; i++)
        {
            if (normas[i] > normas[i + 1])
            {
                swap(normas[i], normas[i + 1]);
                c = 1;
            }
        }
    }

    //sort(normas.begin(), normas.end());

    cout << "\nPrint das normas ordenadas: " << endl;
    for (int i = 0; i < normas.size(); i++)
    {
        cout << "normas[" << i << "]= " << normas[i] << endl;
    }

    return 0;
}