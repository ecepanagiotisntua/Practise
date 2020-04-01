#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class Array2D{
  public:
    Array2D(int n = 0, int m = 0, int bi = 0, int bj = 0);
    Array2D(const Array2D &a);
    ~Array2D();
    Array2D & operator = (const Array2D &a);
    T & select (int i, int j);
    const T & select (int i, int j);

  protected:
    T* data;
    int bi;
    int bj;
    unsigned lenght;
    unsigned loc(int i, int j) const throw (out_of_range);
};

Array2D::Array2D()

