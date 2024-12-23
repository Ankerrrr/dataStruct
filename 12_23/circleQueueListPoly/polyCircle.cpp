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
  queue();
  //   ~queue() {
  //     while (!isEmpty()) {
  //       pop();
  //     }
  //   }
  bool isEmpty();
  node<T> *getFront();
  void push(const term<T> &);
  void pop();
  void print();

  void input();
};

template <typename T>
queue<T>::queue() {
  front = nullptr;
  rear = nullptr;
}

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
    rear->link = front;

  } else {
    rear = rear->link = new node<T>(t);
    rear->link = front;
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
    } else {
      rear->link = front; // 保證循環鏈表
    }
    delete temp;
  }
}

template <typename T>
void queue<T>::print() {
  bool first = true;
  for (node<T> *i = front; 1; i = i->link) {
    if (i == front && !first) {
      break;
    }
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
    queue::push(term(c, e));
  }
}

template <typename T>
queue<T> addPoly(queue<T> &a, queue<T> &b) {
  node<T> *p1 = a.getFront();
  node<T> *p2 = b.getFront();

  a.push(term(-1, -1));
  b.push(term(-1, -1));

  queue<T> ansPoly;
  while (p1 != nullptr && p2 != nullptr) {
    if (p1->data.exp == p2->data.exp) {
      if (p1->data.exp == -1) {
        break;
      }
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

  return ansPoly;
}

int main() {
  queue<int> poly1;
  queue<int> poly2;

  cout << "輸入第一個多項式" << endl;
  poly1.input();
  cout << "輸入第二個多項式" << endl;
  poly2.input();

  queue<int> addAns = addPoly(poly1, poly2);

  cout << "加法結果" << endl;
  addAns.print();
}
