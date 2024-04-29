#include "Vec.h"

//#define DEBUGBUILD

//Constructor 1
Vec::Vec(int n, int val) : N(n)
{
#ifdef DEBUGBUILD
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (N < 0)
        throw std::invalid_argument(Form("[%s] Received negative number of elements...!\n", __PRETTY_FUNCTION__));
    if (N == 0)
        entries = nullptr;
    else
    {
        entries = new double[N];
        std::fill_n(entries, N, val);
    }
}

//Constructor 2
Vec::Vec(int n, double *vals) : N(n)
{
#ifdef DEBUGBUILD
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (!vals)
        throw std::invalid_argument(Form("[%s] Recieved null pointer to array...!\n", __PRETTY_FUNCTION__));
    else
    {
        if (N < 0)
            throw std::invalid_argument(Form("[%s] Received negative number of elements...!\n", __PRETTY_FUNCTION__));
        if (N == 0)
            throw std::invalid_argument(Form("[%s] Number of elements provided doesn't match the given array's size...!\n", __PRETTY_FUNCTION__));
        else
        {
            entries = new double[N];
            std::copy(vals, vals + N, entries);
        }
    }
}

//Copy constructor
Vec::Vec(const Vec &v) : Vec(v.N, v.entries)
{
#ifdef DEBUGBUILD
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
}

//Copy assignment
Vec &Vec::operator=(const Vec &v)
{
#ifdef DEBUGBUILD
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (this != &v)
    {
        if (!v.entries)
        {
            N = 0;
            if (entries)
            {
                delete[] entries;
                entries = nullptr;
            }
        }

        else
        {
            if (N != v.N)
            {
                N = v.N;
                delete[] entries;
                entries = new double[N];
            }
            std::copy(v.entries, v.entries + N, entries);
        }
    }
    return (*this);
}

//Destructor
Vec::~Vec()
{
#ifdef DEBUGBUILD
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (entries)
        delete[] entries;
}

//SetEntries method
void Vec::SetEntries(int n, double *v)
{
#ifdef DEBUGBUILD
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (!v)
    {
        N = 0;
        if (entries)
        {
            delete[] entries;
            entries = nullptr;
        }
    }

    else
    {
        if (N != n)
        {
            N = n;
            delete[] entries;
            entries = new double[N];
        }
        std::copy(v, v + N, entries);
    }
}

//size method
int Vec::size() const
{
#ifdef DEBUGBUILD
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    return N;
}

//Accessing vector elements
double Vec::operator[](int i) const
{
#ifdef DEBUGBUILD
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (i >= 0 && i < N)
    {
        return entries[i];
    }
    else
    {
        if (N == 0)
            throw std::invalid_argument(Form("[%s] <Null pointer> Array doesn't contain any values...!\n", __PRETTY_FUNCTION__));
        else
        {
            throw std::invalid_argument(Form("[%s] Invalid argument...! Argument must be in the interval [0,%d]\n", __PRETTY_FUNCTION__, N - 1));
        }
    }
}

//Accessing vector elements + returning by reference (allows changes in the vector elements)
double &Vec::operator[](int i)
{
#ifdef DEBUGBUILD
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (i >= 0 && i < N)
    {
        return entries[i];
    }
    else
    {
        if (N == 0)
            throw std::invalid_argument(Form("[%s] [nullptr] Array doesn't contain any values...!\n", __PRETTY_FUNCTION__));
        else
        {
            throw std::invalid_argument(Form("[%s] Invalid argument...! Argument must be in the interval [0,%d]\n", __PRETTY_FUNCTION__, N - 1));
        }
    }
}

//Friend method: operator<<
std::ostream &operator<<(std::ostream &s, const Vec &v)
{
#ifdef DEBUGBUILD
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    s << "[";
    for (int i = 0; i < v.N; i++)
    {
        s << std::fixed << std::setprecision(6) << std::setw(16) << v.entries[i];
        if (i < v.N - 1)
            s << ", ";
    }
    s << "]";
    return s;
}

//operator += (equivalent to Vec.operator+=(Vec2))
const Vec &Vec::operator+=(const Vec &v)
{
#ifdef DEBUGBUILD
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (!entries)
        throw std::invalid_argument(Form("[%s] [nullptr] One or both vectors don't contain any values...!\n", __PRETTY_FUNCTION__));
    if (!v.entries)
        throw std::invalid_argument(Form("[%s] [nullptr] One or both vectors don't contain any values...!\n", __PRETTY_FUNCTION__));

    if (v.N != N)
    {
        throw std::invalid_argument(Form("[%s] Diferent sized vectors...!\n", __PRETTY_FUNCTION__));
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            entries[i] += v.entries[i];
        }
        return *this;
    }
}

//operator -= (equivalent to Vec.operator-=(Vec2))
const Vec &Vec::operator-=(const Vec &v)
{
#ifdef DEBUGBUILD
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (!entries)
        throw std::invalid_argument(Form("[%s] [nullptr] One or both vectors don't contain any values...!\n", __PRETTY_FUNCTION__));
    if (!v.entries)
        throw std::invalid_argument(Form("[%s] [nullptr] One or both vectors don't contain any values...!\n", __PRETTY_FUNCTION__));

    if (v.N != N)
    {
        throw std::invalid_argument(Form("[%s] Diferent sized vectors...!\n", __PRETTY_FUNCTION__));
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            entries[i] -= v.entries[i];
        }
        return *this;
    }
}

//operator*=
const Vec &Vec::operator*=(double x)
{
#ifdef DEBUGBUILD
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (!entries)
        throw std::invalid_argument(Form("[%s] [nullptr] Array doesn't contain any values...!\n", __PRETTY_FUNCTION__));
    else
    {
        for (int i = 0; i < N; i++)
        {
            entries[i] *= x;
        }
        return *this;
    }
}

//operator/=
const Vec &Vec::operator/=(double x)
{
#ifdef DEBUGBUILD
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (!entries)
        throw std::invalid_argument(Form("[%s] [nullptr] Array doesn't contain any values...!\n", __PRETTY_FUNCTION__));
    if (x == 0)
        throw std::invalid_argument(Form("[%s] Cannot divide by 0...!\n", __PRETTY_FUNCTION__));
    else
    {
        for (int i = 0; i < N; i++)
        {
            entries[i] /= x;
        }
        return *this;
    }
}

//operator*
Vec Vec::operator*(double x) const
{
#ifdef DEBUGBUILD
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (!entries)
    {
        throw std::invalid_argument(Form("[%s] [nullptr] Array doesn't contain any values...!\n", __PRETTY_FUNCTION__));
    }
    if (std::abs(x - 1.) < 1e-9)
        return *this;
    double a[N];
    for (int i = 0; i < N; i++)
    {
        a[i] = entries[i] * x;
    }
    return Vec(N, a);
}

//swap method
void Vec::swap(int i, int j)
{
#ifdef DEBUGBUILD
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    std::swap(entries[i], entries[j]);
}

//push_back method-> assumes the Vec exists...
void Vec::push_back(double x)
{
#ifdef DEBUGBUILD
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (N != 0 && entries)
    {
        double *temp_entries = new double[N];
        std::copy(entries, entries + N, temp_entries);

        N += 1;
        delete[] entries;
        entries = new double[N];
        std::copy(temp_entries, temp_entries + N - 1, entries);
        std::copy(&x, &x + 1, entries + N - 1);

        delete[] temp_entries;
    }
    else //if (N=0 || !entries)
    {
        N += 1;
        entries = new double[N]{x};
    }
}

//clear method
void Vec::clear()
{
#ifdef DEBUGBUILD
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    if (entries)
        delete[] entries;
    entries = nullptr;
    N = 0;
}

//dot product method
double Vec::dot(const Vec &v)
{
#ifdef DEBUGBUILD
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    double dot = 0.;
    if (N == v.size())
    {
        for (int i = 0; i < N; i++)
        {
            dot += entries[i] * v[i];
        }
        return dot;
    }
    else
    {
        throw std::invalid_argument(Form("[%s] Cannot calculate dot product (Different sized vectors)...!\n", __PRETTY_FUNCTION__));
    }
}

//maxAbs method
double Vec::maxAbs()
{
    double b = fabs(entries[0]);
    for (int i = 1; i < N; i++)
    {
        if (b < fabs(entries[i]))
            b = fabs(entries[i]);
    }
    return b;
}
