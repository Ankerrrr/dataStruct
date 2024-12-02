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
    cout << "(1)���N\n(2)���j\n�п�J:";
    cin >> mode;
    cout << "�п�J�A�n��Fi: ";
    cin >> input;

    if (input >= 0 && !(cin.fail())) {
      switch (mode) {
      case 1:
        cout << "�z�L\"���N\"�p�⪺fib> " << input << "��: " << cacuFib(input) << endl;
        break;
      case 2:
        cout << "�z�L\"���j\"�p�⪺fib> " << input << "��: " << cacuFibRecur(input) << endl;
        break;
      default:
        cout << "�п�J���T���Ҧ�!!" << endl;
      }

    } else {
      cout << "�п�J�Ʀr�Τj��0����" << endl;
      break;
    }
    cin.sync();
  }
}