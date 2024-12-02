#ifndef term_hpp
#define term_hpp
#include <iostream>

using namespace std;

class term {
  friend class poly;

private:
  int coefficient, exponent;
  bool isFirst;

public:
  term(int coef = 0, int exp = 0, bool b = false)
      : coefficient(coef), exponent(exp), isFirst(b) {}

  int getExponent() const { return exponent; }
  int getCoefficient() const { return coefficient; }
  void setCoefficient(int coef) { coefficient = coef; }

  void print() {
    cout << (coefficient > 0 ? (isFirst ? "" : "") : "");
    if (coefficient != 1) {
      cout << coefficient;
    }
    if (exponent) {
      cout << "X^" << exponent;
    }
  }
};
#endif
