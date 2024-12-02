#include <iostream>

using namespace std;

// push, pop, print
// changeSize1D

template <typename T>
class stack {
public:
  stack();
  ~stack();
  void pop();
  void push(const T &);
  void print();
  void printParticularP(T *);
  void printParticularRF(T *&);
  void printParticularDP(T **);

private:
  T *array;
  int capacity;
  int top;
  void changeSize1D();
};

template <typename T>
stack<T>::stack() {
  capacity = 10;
  top = 0;
  array = new T[capacity];
}

template <typename T>
stack<T>::~stack() {
  delete[] array;
}

template <typename T>
void stack<T>::changeSize1D() {
  cout << "expend" << top << ", " << capacity << endl;
  int newCapacity = capacity * 2;
  T *newArray = new T[newCapacity];
  for (int i = 0; i < top; i++) {
    newArray[i] = array[i];
  }
  delete[] array;
  array = newArray;
  capacity = newCapacity;
}

template <typename T>
void stack<T>::push(const T &x) { // call by reference
  if (top == capacity) {
    changeSize1D();
  }
  array[top++] = x;
}

template <typename T>
void stack<T>::pop() {
  if (top - 1 < 0) {
    throw "less than 0, cant pop()";
  }
  --top;
}

template <typename T>
void stack<T>::print() {
  for (int i = 0; i < top; i++) {
    cout << array[i] << ", " << endl;
  }
}

template <typename T>
void stack<T>::printParticularP(T *x) { // call by pointer
  cout << *x << ": " << array[*x] << endl;
}

template <typename T>
void stack<T>::printParticularRF(T *&x) { // call by reference pointer
  cout << *x << ": " << array[*x] << endl;
}

template <typename T>
void stack<T>::printParticularDP(T **x) { // call by Double pointer
  cout << **x << ": " << array[**x] << endl;
}

int main() {
  try {
    stack<int> myStack;
    for (int i = 0; i < 99; i += 2) {
      myStack.push(i);
    }
    myStack.push(20);
    myStack.print();
    myStack.pop();

    // call by
    int a = 5;
    int *b = new int(6);
    int *c = new int(8);
    myStack.printParticularP(&a);
    myStack.printParticularRF(b);
    myStack.printParticularDP(&c);

  } catch (const char *msg) {
    cout << "error: " << msg << endl;
  }
}