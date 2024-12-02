#ifndef RECT_HPP
#define RECT_HPP
#include <iostream>
#endif

using namespace std;

class Rect {
private:
  int x, y, w, h;

public:
  Rect(int xi = 0, int yi = 0, int wi = 0, int hi = 0) : x(xi), y(yi), w(wi), h(hi) {};
  void set(int xi = 0, int yi = 0, int wi = 0, int hi = 0) {
    x = xi;
    y = yi;
    w = wi;
    h = hi;
  }
  bool operator==(const Rect &s) {
    if (this == &s) {
      return true;
    } else if ((this->h == s.h) && (this->w == s.w) && (this->x == s.x) && (this->y == s.y)) {
      return true;
    } else {
      return false;
    }
  }

  bool operator>(const Rect &s) {
    if (this == &s) {
      return false;
    } else if (((this->h * this->w) > (s.h * s.w))) {
      return true;
    } else {
      return false;
    }
  }

  bool operator<(const Rect &s) {
    if (this == &s) {
      return false;
    } else if ((this->h < s.h) && (this->w < s.w) && (this->x < s.x) && (this->y < s.y)) {
      return true;
    } else {
      return false;
    }
  }

  friend ostream &operator<<(ostream &os, const Rect &s) {
    os << "座標:(" << s.x << ", " << s.y << "), 長度:" << s.w << ", 寬度:" << s.h << endl;
    return os;
  }

  friend istream &operator>>(istream &is, Rect &s) {
    int in[4];
    cout << "X: ";
    cin >> in[0];
    cout << "Y: ";
    cin >> in[1];
    cout << "長度: ";
    cin >> in[2];
    cout << "寬度: ";
    cin >> in[3];
    s.set(in[0], in[1], in[2], in[3]);
    if (cin.fail()) {
      cout << "不要亂打" << endl;
    }
    return is;
  }
};