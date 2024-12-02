#ifndef POLY_hpp
#define POLY_hpp

#include "./term.hpp"
#include <iostream>
#include <string>

using namespace std;

class poly {
private:
  int capacity = 10;
  int nowTermCount = 0;
  term *terms;

  void expend();
  void sortTerms();

public:
  poly() {
    terms = new term[capacity];
  }
  ~poly() {
    delete[] terms;
  }
  void input();
  void add(poly const &);
  void print();
  void printDonut();
};

void poly::expend() {
  capacity += 1;
  term *newTerm = new term[capacity];
  for (int i = 0; i < nowTermCount; i++) {
    newTerm[i] = terms[i];
  }
  delete[] terms;
  terms = newTerm;
}

void poly::input() {
  bool isFirst = true;
  while (1) {
    int cof, exp;
    cout << "input coff:";
    cin >> cof;
    cout << "input exp:";
    cin >> exp;
    if (cin.fail()) {
      cin.clear();
      cin.sync();
      break;
    }
    if (nowTermCount >= capacity) {
      expend();
    }
    terms[nowTermCount++] = term(cof, exp, isFirst);
    isFirst = false;
  }
}

void poly::sortTerms() {
  for (int i = 0; i < nowTermCount - 1; i++) {
    for (int j = 0; j < nowTermCount - i - 1; j++) {
      if (terms[j].getExponent() < terms[j + 1].getExponent()) {
        // 交換項目
        term temp = terms[j];
        terms[j] = terms[j + 1];
        terms[j + 1] = temp;
      }
    }
  }
}

void poly::add(const poly &s) {
  for (int i = 0; i < s.nowTermCount; i++) {
    bool found = false;
    for (int j = 0; j < nowTermCount; j++) {
      if (terms[j].getExponent() == s.terms[i].getExponent()) {
        terms[j].setCoefficient(terms[j].getCoefficient() + s.terms[i].getCoefficient());

        // 若係數為 0，則刪除該項
        if (terms[j].getCoefficient() == 0) {
          for (int k = j; k < nowTermCount - 1; k++) {
            terms[k] = terms[k + 1];
          }
          nowTermCount--;
        }
        found = true;
        break;
      }
    }
    if (!found) {
      if (nowTermCount >= capacity) {
        expend();
      }
      terms[nowTermCount++] = s.terms[i];
    }
  }
  sortTerms();
}

void poly::print() {
  for (int i = 0; i < nowTermCount; i++) {
    terms[i].print();
    if (i < nowTermCount - 1 && terms[i + 1].getCoefficient() >= 0) {
      cout << "+";
    }
  }
  cout << endl;
}

#endif