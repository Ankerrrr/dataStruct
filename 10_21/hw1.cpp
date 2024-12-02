#include "./Rect.hpp"
#include <iostream>

using namespace std;

int main() {
  Rect a, b, *c;
  // c = new Rect[2];
  cin >> a;
  cin >> b;
  cout << a;
  cout << b;
  // cout << c[0];

  cout << "a" << (a > b ? ">" : "<") << "b" << endl;
}
