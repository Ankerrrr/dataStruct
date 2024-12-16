#include <iostream>

using namespace std;

template <typename T>
class queue;

template <typename T>
class chainNode {
  friend class queue<T>;

private:
  T data;
  chainNode *link;

public:
  chainNode(T &D, chainNode *L = 0) : data(D), link(L) {};
};

template <typename T>
class queue {
private:
  chainNode<T> *front, *rear;

public:
  queue() : front(nullptr), rear(nullptr) {};
  ~queue() {
    while (!isEmpty()) {
      pop();
    }
  }
  bool isEmpty();
  void push(T &);
  void pop();
  void print();
};

template <typename T>
bool queue<T>::isEmpty() {
  return front == NULL;
}

template <typename T>
void queue<T>::push(T &D) {
  if (isEmpty()) {
    front = rear = new chainNode<T>(D, 0);
  } else {
    rear = rear->link = new chainNode<T>(D, 0);
  }
}

template <typename T>
void queue<T>::pop() {
  if (isEmpty()) {
    throw "queue is Empty, cant pop()";
  } else {
    chainNode<T> *temp = front;
    front = front->link;
    if (front == nullptr) {
      rear = nullptr;
    }
    delete temp;
  }
}

template <typename T>
void queue<T>::print() {
  int count = 0;
  for (chainNode<T> *i = front; i != NULL; i = i->link) {
    cout << "N." << ++count << ": " << i->data << ", ";
  }
}

int main() {
  queue<int> myIntQueue;
  for (int i = 0; i < 10; i++) {
    myIntQueue.push(i);
  }
  myIntQueue.print();
}