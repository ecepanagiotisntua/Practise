#include <iostream>
#include <stdexcept>

using namespace std;

class Row;

template<typename T>
class Array2D{
  public:
    Array2D(int n = 0, int m = 0, int bi = 0, int bj = 0);
    Array2D(const Array2D &a);
    ~Array2D();
    Array2D & operator = (const Array2D &a){
      delete data[];
      data = new T[a.numC*numR];
      basei = a.basei;
      basej = a.basej;
      numC = a.numC;
      numR = a.numR;
      for (int i = 0;i < numC*numR; i++) data[i] = a.data[i];
      return *this;
    }
    T & select (int i, int j){
      return data[loc(i, j)];

    }
    
    const T & select (int i, int j){
      return data[loc(i, j)];
    }

    Row operator [] (int i){
      return (*this, i);
    }

  protected:
    T* data;
    int basei;
    int basej;
    unsigned numC;
    unsigned numR;
    unsigned loc(int i, int j) const throw (out_of_range);
};

class Row{
  public:
    Row(Array2D &a, int i):
      array2D(a), row(i){};
    T &operator [](int i) const{
      return array2D.select(row, i);
    }

  private:
    Array2D &array2D;
    int row;

};

Array2D::Array2D(int n = 0, int m = 0, int bi = 0, int bj = 0):
  data(new T[n*m]), basei(bi), basej(bj), numC(m), numR(i){}

Array2D::Array2D(const Array2D &a):
  data(new T[a.length]), basei(a.basei), basej(a.basej), numC(a.numC), numR(a.numR){
    for (int i = 0, i < numC*numR; i++) data[i] = a.data[i];
  }

Array2D::~Array2D(){
  delete data[];
}


unsigned Array2D::loc(int i, int j) const throw (out_of_range){
  int di = i-basei;
  int dj = j-basej;
  if (di < 0 || dj < 0 || di > numR || dj > numC) throw out_of_range("invalid range");
  return numR*di + dj;
}



