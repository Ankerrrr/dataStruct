#include "./poly.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
  poly a, b;
  // string inpA, inpB;
  cout << "input poly A" << endl;
  a.input();
  cout << "\ninput poly B" << endl;
  b.input();

  cout << "\nthis is A:" << endl;
  a.print();
  cout << "\nthis is B:" << endl;
  b.print();

  a.add(b);
  cout << "\nthis is A + B:" << endl;
  a.print();

  return 0;
}