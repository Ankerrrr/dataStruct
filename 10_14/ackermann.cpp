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
  cout << "(1)���N\n(2)���j\n�п�J:";
  cin >> mode;

  if (mode > 2 && mode < 1) {
    cout << "�п�J���T���Ҧ�" << endl;
  }

  cout << "�п�Jm=";
  cin >> m;
  cout << "�п�Jn=";
  cin >> n;

  if (cin.fail()) {
    cout << "��J���X�z�ƭ�";
    return -1;
  }

  switch (mode) {
  case 1:
    cout << "�z�L���N���p�⵲�G: " << Ackermann(m, n);
    break;
  case 2:
    cout << "�z�L���j���p�⵲�G: " << AckermannRecur(m, n);
    break;
  }
}