#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

using namespace std;

template <typename T>
class stack {
public:
  stack();
  ~stack();
  void pop();
  void push(const T &);
  T &getTop();
  void print();
  bool empty();
  T &get(int &);
  int &size();

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
  // if (array != nullptr) {
  //   delete[] array;
  //   array = nullptr; // ¨¾¤î¤G¦¸ÄÀ©ñ
  // }
}

template <typename T>
void stack<T>::changeSize1D() {
  // cout << "expend" << top << ", " << capacity << endl;
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
  if (top >= capacity) {
    changeSize1D();
  }
  array[top++] = x;
}

template <typename T>
void stack<T>::pop() {
  if (top <= 0) {
    throw "less than 0, cant pop()";
  }
  --top;
}

template <typename T>
T &stack<T>::getTop() {
  if (top < 1) {
    throw "less than 0, cant getTop()";
  }
  return array[top - 1];
}

template <typename T>
void stack<T>::print() {
  for (int i = 0; i < top; i++) {
    cout << array[i] << ", " << endl;
  }
}

template <typename T>
bool stack<T>::empty() {
  if (top < 1) {
    return true;
  }
  return false;
}

template <typename T>
T &stack<T>::get(int &n) {
  if (n >= top || n < 0) {
    throw "cant get this index";
  } else {
    return array[n];
  }
}

template <typename T>
int &stack<T>::size() {
  return top;
}
#endif