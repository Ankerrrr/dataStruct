#include <iostream>

using namespace std;

class Triple {
public:
  int row, col, value;
};

class matrixNode {
private:
  matrixNode *down, *right;
  bool head;
  union {
    matrixNode *next;
    Triple tp;
  };
  matrixNode(bool, Triple *);
};

int main() {
}