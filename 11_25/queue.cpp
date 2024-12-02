#include <iostream>

using namespace std;

template <typename t>
class queue {
private:
  int size, front, rear, capacity;
  t *array;
  void changeSizeOneD();

public:
  queue();
  ~queue();
  void push(const t &);
  void pop();
  void print();
};

template <typename t>
queue<t>::queue() {
  size = 0;
  front = 0;
  rear = 0;
  capacity = 10;

  array = new t[capacity];
}

template <typename t>
queue<t>::~queue() {
  delete[] array;
}

template <typename t>
void queue<t>::push(const t &x) {
  if (size >= capacity) {
    changeSizeOneD();
  }
  array[rear++] = x;
  size++;
}

template <typename t>
void queue<t>::pop() {
  if (rear - front <= 0) {
    throw "data less than 1,Cant pop()";
  }
  front++;
  size--;
}

template <typename t>
void queue<t>::print() {
  if (size < 1) {
    throw "no DATA nothing to print()";
  }
  for (int i = front; i < rear; i++) {
    cout << array[i] << ", ";
  }
  cout << endl;
}

template <typename t>
void queue<t>::changeSizeOneD() {
  capacity *= 2;
  t *tempArray = new t[capacity];
  int j = 0;
  for (int i = front; i < rear; i++) {
    tempArray[j++] = array[i];
  }
  front = 0;
  rear = j;

  delete[] array;
  array = tempArray;
}

int main() {
  queue<int> IntengerQueqe;
  IntengerQueqe.push(1);
  IntengerQueqe.push(2222);
  for (int i = 0; i < 99; i++) {
    IntengerQueqe.push(i);
  }
  IntengerQueqe.pop();
  IntengerQueqe.print();
  return 0;
}