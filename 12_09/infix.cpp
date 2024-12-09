#include "stack1.hpp"
#include <iostream>
#include <string>

using namespace std;

struct post {
  char symbol;
  int rate;
};

post operators[6] = {
    {'(', 0},
    {')', 0},
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2}};

int getRate(char infix) {
  int nowRate;

  for (int g = 0; g < 6; g++) {
    if (infix == operators[g].symbol) {
      nowRate = operators[g].rate;
      break;
    }
  }
  return nowRate;
}

int getSymb(char postfix) {
  int n;
  for (int g = 2; g <= 5; g++) {
    if (operators[g].symbol == postfix) {
      n = g;
    }
  }
  return n;
}

void input(string &infix) {
  while (1) {
    cout << "請輸入中置運算式(不須空格)" << endl;
    getline(cin, infix);

    for (int i = 0; i < infix.length(); i++) {
      if (infix[i] < '0' || infix[i] > '9') {
        bool op = false;
        for (int j = 0; j < 6; j++) {
          if (infix[i] == operators[j].symbol) {
            op = true;
          }
        }
        if (op == false) {
          cout << "請輸入正確中置運算式!!" << endl;
          break;
        }
      }
    }
    break;
  }
}

string transferToPostfix(string infix) {
  stack<char> myStack;
  string postfix;

  for (int i = 0; i < infix.length();) {
    // cout << postfix;
    if (infix[i] <= '9' && infix[i] >= '0') {
      postfix.push_back(infix[i]);
      i++;
      continue;

    } else {
      if (infix[i] == '(') {
        myStack.push(infix[i]);
        i++;
        continue;

      } else if (infix[i] == ')') {
        while (1) {
          char ch = myStack.getTop();
          if (ch == '(') {
            myStack.pop();
            break;
          }
          postfix.push_back(ch);
          myStack.pop();
        }
        i++;
        continue;

      } else { // + - * /
        if (myStack.empty()) {
          myStack.push(infix[i]);
          i++;
          continue;
        }

        int nowInfixRate = getRate(infix[i]);
        int nowStackRate = getRate(myStack.getTop());

        if (nowInfixRate > nowStackRate) {
          myStack.push(infix[i]);
          i++;
          continue;
        } else {
          char ch = myStack.getTop();
          myStack.pop();
          postfix.push_back(ch);
        }
      }
    }
  }
  while (!myStack.empty()) {
    postfix.push_back(myStack.getTop());
    myStack.pop();
  }
  return postfix;
}

double caculatorPostfix(string postfix) {
  stack<double> myStack;

  for (int i = 0; i < postfix.length();) {
    if (postfix[i] <= '9' && postfix[i] >= '0') {
      myStack.push(postfix[i] - '0');
      i++;
      continue;

    } else { // + - * /
      double rear = myStack.getTop();
      myStack.pop();
      double front = myStack.getTop();
      myStack.pop();

      int operatorSN = getSymb(postfix[i]);

      switch (operatorSN) {
      case 2:
        myStack.push(front + rear);
        break;
      case 3:
        myStack.push(front - rear);
        break;
      case 4:
        myStack.push(front * rear);
        break;
      case 5:
        myStack.push(front / rear);
        break;
      default:
        throw "Err";
      }

      i++;
      continue;
    }
  }
  return myStack.getTop();
}

int main() {
  // 輸入
  string infix;
  input(infix);
  cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;

  // 轉換為後置運算元
  cout << "轉換為後置運算元: " << endl;
  string postfix = transferToPostfix(infix);
  cout << postfix << endl;

  // 計算後置運算元
  cout << "結果: " << endl;
  cout << caculatorPostfix(postfix) << endl;

  return 0;
}