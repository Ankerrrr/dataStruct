#include "stack1.hpp"
#include <iostream>

using namespace std;

class node {
public:
  int data;
  node *link;

  node(int d, node *l = 0) : data(d), link(l) {};
};

class equivalentArray {
  friend class node;

private:
  bool Check;
  node *child;

public:
  equivalentArray() {
    Check = false;
    child = nullptr;
  }
  bool getCheck() { return Check; }
  void checkTrue() { Check = true; }
  void setChild(int);
  node *getChild() { return child; }
};

void equivalentArray::setChild(int value) {
  if (child == nullptr) {
    child = new node(value);

  } else {
    child = new node(value, child);
  }
}

void inputEquivalence(int &num, equivalentArray **&arr) {
  // 輸入(創建)有幾個等價點
  cout << "輸入要幾個等價列:";
  cin >> num;

  arr = new equivalentArray *[num];

  for (int i = 0; i < num; ++i) {
    arr[i] = new equivalentArray();
  }

  // 輸入(處理)等價關係
  cout << "輸入等價關係(結束輸入:輸入錯誤等價關係)" << endl;
  while (1) {
    int Value1, Value2;
    cin >> Value1 >> Value2;
    if (Value1 >= num || Value1 < 0 || Value2 >= num || Value2 < 0) {
      cout << "輸入錯誤(輸入結束)" << endl;
      break;
    }

    arr[Value1]->setChild(Value2);
    arr[Value2]->setChild(Value1);
    cout << Value1 << " == " << Value2 << "(suss)" << endl;
  }
}

void analyzeEquivlence(int &num, equivalentArray **&arr) {
  stack<int> myStack;
  stack<int> ans;
  int nowPois = 0;

  while (nowPois < num) {
    if (arr[nowPois]->getCheck() == true) {
      nowPois++;
      continue;
    }

    // 處理直接的
    ans.push(nowPois);
    node *getNode = arr[nowPois]->getChild();
    while (getNode != nullptr) {
      if (arr[getNode->data]->getCheck() == false) {
        myStack.push(getNode->data);
      }
      getNode = getNode->link;
    }
    arr[nowPois]->checkTrue();

    ////處理堆疊裡的
    while (!myStack.empty()) {
      int getStack = myStack.getTop();
      myStack.pop();

      if (arr[getStack]->getCheck() == false) {
        // cout << "hh:" << getStack << endl;
        arr[getStack]->checkTrue();
        ans.push(getStack);

        node *getNode = arr[getStack]->getChild();
        while (getNode != nullptr) {
          myStack.push(getNode->data);
          getNode = getNode->link;
        }
      }
    }
    // cout << "//" << endl;
    ans.push(-99);
  }

  while (!ans.empty()) {
    int getAnsTop = ans.getTop();
    ans.pop();

    if (getAnsTop != -99) {
      cout << getAnsTop << ", ";
    } else {
      cout << endl;
      cout << "A new class: " << endl;
    }
  }
}

void deleteArray(int &num, equivalentArray **&arr) {
  cout << endl
       << endl;
  cout << "delete" << endl;
  for (int i = 0; i < num; i++) {
    cout << i << ": ";

    node *temp = arr[i]->getChild();
    while (temp != nullptr) {
      cout << temp->data << ", ";
      node *temptemp = temp;
      temp = temp->link;
      delete temptemp;
    }
    cout << endl;
  }
  delete[] arr;
}

int main() {
  equivalentArray **arr;
  int num;
  inputEquivalence(num, arr);
  analyzeEquivlence(num, arr);
  deleteArray(num, arr);
}