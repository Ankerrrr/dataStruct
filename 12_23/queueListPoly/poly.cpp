#include <iostream>

using namespace std;

template <typename T>
class queue;

template <typename T>
queue<T> addPoly(queue<T> &, queue<T> &);

// defin for node
template <typename T>
class term {
public:
  T cof;
  int exp;
  term(const T &c, const int &e) : cof(c), exp(e) {};
};

// defin for single node
template <typename T>
class node {
  friend class queue<T>;
  friend queue<T> addPoly<T>(queue<T> &, queue<T> &);

private:
  term<T> data;
  node *link;

public:
  node(const term<T> &d) : data(d), link(nullptr) {};
};

// defin for every node
template <typename T>
class queue {
private:
  node<T> *front, *rear;

public:
  queue() : front(nullptr), rear(nullptr) {};
  ~queue() {
    while (!isEmpty()) {
      pop();
    }
  }
  bool isEmpty();
  node<T> *getFront();
  void push(const term<T> &);
  void pop();
  void print();

  void input();
};

template <typename T>
bool queue<T>::isEmpty() {
  return front == NULL;
}

template <typename T>
node<T> *queue<T>::getFront() {
  return front;
}

template <typename T>
void queue<T>::push(const term<T> &t) {
  if (isEmpty()) {
    front = rear = new node<T>(t);
  } else {
    rear = rear->link = new node<T>(t);
  }
}

template <typename T>
void queue<T>::pop() {
  if (isEmpty()) {
    throw "queue is Empty, cant pop()";
  } else {
    node<T> *temp = front;
    front = front->link;
    if (front == nullptr) {
      rear = nullptr;
    }
    delete temp;
  }
}

template <typename T>
void queue<T>::print() {
  bool first = true;
  for (node<T> *i = front; i != NULL; i = i->link) {
    if (i->data.cof == 0) {
      continue;
    }
    if (!first) {
      cout << " + ";
    } else {
      first = false;
    }
    if (i->data.exp == 0) {
      cout << i->data.cof;
      continue;
    }
    cout << i->data.cof << "^" << i->data.exp;
  }
}

template <typename T>
void queue<T>::input() {
  cout << "輸入多項式(次方由大到小)" << endl;
  cout << "輸入999中止" << endl;

  int min = INT_MIN;

  T c;
  int e;

  while (1) {
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "輸入係數: ";
    cin >> c;
    if (c == 999) {
      cout << "程式中止" << endl;
      break;
    }
    cout << "輸入次方: ";
    cin >> e;
    if (e == 999) {
      cout << "程式中止" << endl;
      break;
    }

    if (e < min || min == INT_MIN) {
      min = e;
    } else if (e >= min) {
      cout << "請將次方由大到小依序輸入!!";
      throw "錯誤";
    }
    this->push(term<T>(c, e));
  }
}

template <typename T>
queue<T> addPoly(queue<T> &a, queue<T> &b) {
  node<T> *p1 = a.getFront();
  node<T> *p2 = b.getFront();

  queue<T> ansPoly;

  while (p1 != nullptr && p2 != nullptr) {
    if (p1->data.exp == p2->data.exp) {
      ansPoly.push(term<T>((p1->data.cof + p2->data.cof), p1->data.exp));
      p1 = p1->link;
      p2 = p2->link;

    } else if (p1->data.exp > p2->data.exp) {
      ansPoly.push(term<T>(p1->data.cof, p1->data.exp));
      p1 = p1->link;

    } else {
      ansPoly.push(term<T>(p2->data.cof, p2->data.exp));
      p2 = p2->link;
    }
  }

  while (p1 != nullptr) {
    ansPoly.push(term<T>(p1->data.cof, p1->data.exp));
    p1 = p1->link;
  }
  while (p2 != nullptr) {
    ansPoly.push(term<T>(p2->data.cof, p2->data.exp));
    p2 = p2->link;
  }

  return ansPoly;
}

int main() {
  queue<int> poly1;
  queue<int> poly2;
  cout << "一般" << endl;

  try {
    cout << "輸入第一個多項式" << endl;
    poly1.input();
    cout << "輸入第二個多項式" << endl;
    poly2.input();

    queue<int> addAns = addPoly(poly1, poly2);

    cout << "加法結果" << endl;
    addAns.print();
  } catch (const char *msg) {
    cout << msg;
  }
}