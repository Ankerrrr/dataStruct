#include <iostream>

using namespace std;

template <typename T>
class stack;

template <typename T>
class chainNode {
  friend class stack<T>;

private:
  T data;
  chainNode *link;

public:
  chainNode(T D, chainNode *L = nullptr) : data(D), link(L) {}
};

template <typename T>
class stack {
private:
  chainNode<T> *top;

public:
  stack() : top(nullptr) {}
  bool isEmpty();
  void push(T D);
  void pop();
  void print();
};

template <typename T>
bool stack<T>::isEmpty() {
  return top == nullptr;
}

template <typename T>
void stack<T>::push(T D) {
  top = new chainNode<T>(D, top);
}

template <typename T>
void stack<T>::pop() {
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
    }
  }
  cout << endl;
}

int main() {
  stack<int> myIntTop;
  for (int i = 0; i < 10; i++) {
    myIntTop.push(i);
  }
  myIntTop.print();
  return 0;
}
