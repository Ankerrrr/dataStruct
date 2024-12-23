#include <iostream>

using namespace std;

template <typename T>
class stack;

template <typename T>
class chainNode {
<<<<<<< HEAD
  friend class stack<T>;
=======
    friend class stack<T>;
>>>>>>> a4c7624e2151d634514cccc598c612c1f203fa7d

private:
    T data;
    chainNode* link;

public:
    chainNode(T D, chainNode* L = nullptr) : data(D), link(L) {}
};

template <typename T>
class stack {
private:
    chainNode<T>* top;

public:
<<<<<<< HEAD
  stack() : top(nullptr) {}
  bool isEmpty();
  void push(T D);
  void pop();
  void print();
=======
    stack() : top(nullptr) {}
    bool isEmpty();
    void push(T D);
    void pop();
    void print();
    void printHelper(chainNode<T>* node);  // 輔助函式
>>>>>>> a4c7624e2151d634514cccc598c612c1f203fa7d
};

template <typename T>
bool stack<T>::isEmpty() {
<<<<<<< HEAD
  return top == nullptr;
=======
    return top == nullptr;
>>>>>>> a4c7624e2151d634514cccc598c612c1f203fa7d
}

template <typename T>
void stack<T>::push(T D) {
<<<<<<< HEAD
  top = new chainNode<T>(D, top);
=======
    top = new chainNode<T>(D, top);
>>>>>>> a4c7624e2151d634514cccc598c612c1f203fa7d
}

template <typename T>
void stack<T>::pop() {
<<<<<<< HEAD
  if (isEmpty()) {
    throw "stack is Empty, cant pop()";
  } else {
    chainNode<T> *temp = top;
    top = top->link;
    delete temp;
  }
}

template <typename T>
void stack<T>::print() {
  int count = 0;
  for (chainNode<T> *i = top; i != NULL; i = i->link) {
    cout << "N." << ++count << ": " << i->data;
    if (i->link) {
      cout << ", ";
=======
    if (isEmpty()) {
        throw "stack is Empty, cant pop()";
>>>>>>> a4c7624e2151d634514cccc598c612c1f203fa7d
    }
    else {
        chainNode<T>* temp = top;
        top = top->link;
        delete temp;
    }
}

template <typename T>
void stack<T>::print() {
    printHelper(top); 
    cout << endl;
}

template <typename T>
void stack<T>::printHelper(chainNode<T>* node) {
    if (node == nullptr) return;  
    printHelper(node->link);  
    cout << node->data << ", ";
}

int main() {
<<<<<<< HEAD
  stack<int> myIntTop;
  for (int i = 0; i < 10; i++) {
    myIntTop.push(i);
  }
  myIntTop.print();
  return 0;
=======
    stack<float> myIntTop;

    myIntTop.push(3.45);
    myIntTop.push(7);
    myIntTop.push(0);
    myIntTop.push(2.6);
    myIntTop.pop();

    myIntTop.print();  
    return 0;
>>>>>>> a4c7624e2151d634514cccc598c612c1f203fa7d
}
