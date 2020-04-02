#include <iostream>

using namespace std;

template <typename T>
class Container {

public:
  virtual ~Container() {}
  virtual int size() const = 0;
  virtual bool empty() const { return size() == 0; }
  virtual void clear() = 0;

};

template <typename T>
class dlist: public Container<T> {
  public:
    dlist() 
      : the_front(nullptr), the_back(nullptr), the_size(0) {}

    dlist(const dlist &l) 
      : the_front(nullptr), the_back(nullptr), the_size(0) { copy(l); }

    virtual ~dlist() override { purge(); }

    dlist & operator = (const dlist &l) {
      clear(); copy(l); 
      return *this;
    } 

    virtual int size() const override { return the_size; }

    virtual void clear() override {
      purge();
      the_front = the_back = nullptr;
      the_size = 0;
    }

    void push_back(const T &x) {
      node *p = new node(x, nullptr, the_back);
      if (the_back != nullptr) the_back->next = p;
      else the_front = p;
      the_back = p;
      the_size++;
    }

    void push_front(const T &x) {
      node *p = new node(x, the_front, nullptr);
      if (the_front != nullptr) the_front->prev = p;
      else the_back = p;
      the_front = p;
      the_size++;
    }

    void pop_back() {
      node *p = the_back;
      the_back = p->prev;
      if (the_back != nullptr) the_back->next = nullptr;
      else the_front = nullptr;
      delete p;
      the_size--;
    }

    void pop_front() {
      node *p = the_front;
      the_front = p->next;
      if (the_front != nullptr) the_front->prev = nullptr;
      else the_back = nullptr;
      delete p;
      the_size--;
    }
    T & back() { return the_back->data; }

    T & front() { return the_front->data; }

  private:
    struct node {
      T data;
      node *next, *prev;
      node(const T &x, node *n, node *p) 
        : data(x), next(n), prev(p) {}
    };

    node *the_front, *the_back;
    int the_size;
    void copy(const dlist &l) {
      for (node *p = l.the_front; p != nullptr; p = p->next)
        push_back(p->data);
    }

    void purge() {
      node *p = the_front;
      while (p != nullptr) {
        node *q = p;
        p = p->next;
        delete q;
      }
    }
};


template <typename T>
void print(dlist<T> &l) {
  while (!l.empty()) {
    cout<< l.front();
    cout << " ";
    l.pop_front();
  }
}

int main() {
  dlist<int> l;
  for (int i = 0; i < 10; i++) l.push_back(i);
  cout << "size: " << l.size() << " :";
  print (l);
  

}



