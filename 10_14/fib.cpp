#include <cstdlib>
#include <iostream>

using namespace std;

int cacuFib(int inp) {
  int x[3] = {0, 1, 0};
  switch (inp) {
  case 0:
    return x[0];
  case 1:
    return x[1];
  default:
    for (int i = 2; i <= inp; i++) {
      x[2] = (x[0] + x[1]);
      x[0] = x[1];
      x[1] = x[2];
    }
  }
  return x[2];
}

int cacuFibRecur(int input) {
  switch (input) {
  case 0:
    return 0;
  case 1:
    return 1;
  default:
    return cacuFibRecur(input - 2) + cacuFibRecur(input - 1);
  }
}

int main() {
  int mode, input;
  while (1) {
    cout << "(1)迭代\n(2)遞迴\n請輸入:";
    cin >> mode;
    cout << "請輸入你要的Fi: ";
    cin >> input;

    if (input >= 0 && !(cin.fail())) {
      switch (mode) {
      case 1:
        cout << "透過\"迭代\"計算的fib> " << input << "為: " << cacuFib(input) << endl;
        break;
      case 2:
        cout << "透過\"遞迴\"計算的fib> " << input << "為: " << cacuFibRecur(input) << endl;
        break;
      default:
        cout << "請輸入正確的模式!!" << endl;
      }

    } else {
      cout << "請輸入數字及大於0的樹" << endl;
      break;
    }
    cin.sync();
  }
}