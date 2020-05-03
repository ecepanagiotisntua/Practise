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

    class iterator {
      public:
        iterator(const iterator &i)
          : ptr(i.ptr){}
        //++i 
        iterator & operator++() {
          ptr = ptr->next;
          return *this;
        }
        //i++
        iterator operator++(int){
          iterator result(*this);
          ptr = ptr-> next;
          return result;
        }

       T & operator*() { return ptr->data; }

       bool operator!=(const iterator &i) const { return ptr != i.ptr; }
       bool operator==(const iterator &i) const { return ptr == i.ptr; }

      private: 
        node *ptr;

        iterator(node *p)
          : ptr(p) {}

        friend class dlist;
      
    };

    iterator begin() { return iterator(the_front); }
    iterator end() { return iterator(nullptr); }

  
};

template <typename T>
class bstree: public Container<T> {
  private:
    struct node {
      T data;
      node *left, *right, *parent;
      node(const T &x, node *l, node *r, node *p) 
        : data(x), left(l), right(r), parent(p) {}
    };

    node *root;

    int the_size;

    void copy(node *t) {
      if(t != nullptr){
        insert(t->data);
        copy(t->left);
        copy(t->right);
      }
    }

    static void purge(node *t) {
      if(t != nullptr){
        purge(t->left);
        purge(t->right);
        delete t;
      }
    }

    static bool insert(node *t, const T &x){
      if (x < t->data){
        if (t->left == nullptr){
          t->left = new node(x, nullptr, nullptr, t);
          return true;
        } else
          return insert(t->left, x);
      } else if (x > t->data){
        if (t->right == nullptr){
          t->right = new node(x, nullptr, nullptr, t);
          return true;
        } else
          return insert(t->right, x);

      }
      return false;

    }

    static void print(node *t){
      if (t != nullptr){
        print(t->left);
        cout<< " " << t->data;
        print(t->right);
      }
    }

  public:
    bstree() 
      : root(nullptr), the_size(0) {}

    bstree(const bstree &t) 
      : root(nullptr), the_size(0) { copy(t.root); }

    virtual ~bstree() override { purge(root); }

    bstree & operator = (const bstree &t) {
      clear(root); copy(t.root); 
      return *this;
    } 

    virtual int size() const override { return the_size; }

    virtual void clear() override {
      purge();
      root = nullptr;
      the_size = 0;
    }

    void insert(const T &x) {
      if(root == nullptr) {
        root = new node(x, nullptr, nullptr, nullptr);
        ++the_size;
      }
      else if(insert(root, x)) the_size++;
    }

    void print() {
      print(root);
    }

    

    class iterator {
      public:
        iterator(const iterator &i)
          : ptr(i.ptr){}
        //++i 
        iterator & operator++() {
          ptr = ptr->next;
          return *this;
        }
        //i++
        iterator operator++(int){
          iterator result(*this);
          ptr = ptr-> next;
          return result;
        }

       T & operator*() { return ptr->data; }

       bool operator!=(const iterator &i) const { return ptr != i.ptr; }
       bool operator==(const iterator &i) const { return ptr == i.ptr; }

      private: 
        node *ptr;

        iterator(node *p)
          : ptr(p) {}

        friend class dlist;
      
    };

    iterator begin() { return iterator(the_front); }
    iterator end() { return iterator(nullptr); }

  
};


template <typename T>
void print(dlist<T> &l) {
 
  for (auto i = l.begin(); i != l.end(); ++i){
    cout << " " << *i;
  }
}

int main() {
  dlist<int> l;
  for (int i = 0; i < 10; i++) l.push_back(i);
  cout << "size: " << l.size() << " :";
  print (l);
  cout << endl;
  print (l);
  for (int &x : l) x*=2;
  print(l);

}



