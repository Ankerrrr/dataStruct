#include <iostream>

using namespace std;

int Ackermann(int m, int n) {
  while (1) {
    if (m == 0) {
      return n + 1;
    } else if (n == 0) {
      m--;
      n = 1;
    } else {
      n = Ackermann(m, n - 1);
      m--;
    }
  }
}

int AckermannRecur(int m, int n) {
  if (m == 0)
    return n + 1;
  else if (m > 0 && n == 0)
    return AckermannRecur(m - 1, 1);
  else
    return AckermannRecur(m - 1, AckermannRecur(m, n - 1));
}

int main() {
  int mode, m, n;
  cout << "(1)迭代\n(2)遞迴\n請輸入:";
  cin >> mode;

  if (mode > 2 && mode < 1) {
    cout << "請輸入正確的模式" << endl;
  }

  cout << "請輸入m=";
  cin >> m;
  cout << "請輸入n=";
  cin >> n;

  if (cin.fail()) {
    cout << "輸入不合理數值";
    return -1;
  }

  switch (mode) {
  case 1:
    cout << "透過迭代的計算結果: " << Ackermann(m, n);
    break;
  case 2:
    cout << "透過遞迴的計算結果: " << AckermannRecur(m, n);
    break;
  }
}