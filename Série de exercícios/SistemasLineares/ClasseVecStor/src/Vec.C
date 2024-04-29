#include "Vec.h"
#include <cstdio>
#include <algorithm>
#include <stdexcept>
#include <iomanip>

#include "TROOT.h"

#define DEBUG

///////////////////// constructors

Vec::Vec(int i, double x) : N(i) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (N<0) throw std::invalid_argument(Form("[%s] received negative number of elements...!\n", __PRETTY_FUNCTION__));
  entries = new double[N];
  std::fill_n(entries, N, x);
}

Vec::Vec(int i, const double* x) : Vec(i) { //c++11 on...
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (x)
    std::copy(x, x+i, entries);
  else  
    throw std::invalid_argument(Form("[%s] null pointer to array...!\n", __PRETTY_FUNCTION__));
}

Vec::Vec(const Vec& v) : Vec(v.N, v.entries) { //c++11 on...
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
}

////////////////////// destructor
Vec::~Vec() {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  delete [] entries;
}

///////////////////// operators
double Vec::operator[](int i) const {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (i>=N) 
    throw std::invalid_argument(Form("[%s] index out of bounds...(i=%d N=%d)!\n", __PRETTY_FUNCTION__, i, N));  
  return entries[i];
}

///////////////////// operators
double& Vec::operator[](int i) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (i>=N) 
    throw std::invalid_argument(Form("[%s] index out of bounds...(i=%d N=%d)!\n", __PRETTY_FUNCTION__, i, N));  
  return entries[i];
}

void Vec::operator=(const Vec& v) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (this != &v) {
    if (v.N != N) {
      N = v.N;
      delete [] entries;
      entries = new double[N];
    }
    std::copy(v.entries, v.entries+N, entries);    
  }
}

const Vec& Vec::operator+= (const Vec& v) { 
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__ );
#endif
  if (v.N != N) {
    throw std::invalid_argument(Form("[%s] objects with different size...(N=%d v.N=%d)!\n", __PRETTY_FUNCTION__, N, v.N));        
  }
  for (int i=0; i<N; ++i) {
    entries[i] += v[i];
  }
  return *this;
}

Vec Vec::operator*(double x) const {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__ );
#endif
  if (abs(x-1.)<1E-9)
    return *this;
  double a[N];
  for (int i=0; i<N; ++i) {
    a[i] = entries[i] * x;
  }
  return Vec(N, a);
} 


///////////////////// friend methods

std::ostream& operator<<(std::ostream& s, const Vec& v) {
  s << "[";
  for (int i=0; i<v.N; ++i) {
    s << std::fixed << std::setprecision(6) << v.entries[i];
    if (i<v.N-1) s << ", ";
  }
  s << "]";
  return s;
}