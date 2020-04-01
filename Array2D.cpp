#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class Array2D{
  public:
    Array2D(int n = 0, int m = 0, int bi = 0, int bj = 0);
    Array2D(const Array2D &a);
    ~Array2D();
    Array2D & operator = (const Array2D &a){
      delete data[];
      data = new T[a.length];
      basei = a.basei;
      basej = a.basej;
      length = a.length;
      for (int i = 0, i < length; i++) data[i] = a.data[i];
    }
    T & select (int i, int j);
    const T & select (int i, int j);

  protected:
    T* data;
    int basei;
    int basej;
    unsigned length;
    unsigned loc(int i, int j) const throw (out_of_range);
};

Array2D::Array2D(int n = 0, int m = 0, int bi = 0, int bj = 0):
  data(new T[n*m]), basei(bi), basej(bj), length(n*m){}

Array2D::Array2D(const Array2D &a):
  data(new T[a.length]), basei(a.basei), basej(a.basej), length(a.length){
    for (int i = 0, i < length; i++) data[i] = a.data[i];
  }

Array2D::~Array2D(){
  delete data[];
}



