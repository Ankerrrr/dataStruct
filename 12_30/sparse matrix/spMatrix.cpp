// 沒做完

#include <iostream>

using namespace std;

class Triple {
public:
  int row, col, value;
  Triple(int r, int c, int v) : row(r), col(c), value(v) {}
};

class matrixNode {
  friend void initNodeList(matrixNode *&head, int row, int col, int numData);
  friend void addingNode(matrixNode *head, int row, int col, int value);
  friend void printMatrix(matrixNode *head);
  friend void printMatrixLinks(matrixNode *head);

private:
  matrixNode *down, *right;
  bool head;
  union {
    matrixNode *next;
    Triple tp;
  };

  matrixNode(bool hd) {
    head = hd;
    next = nullptr;
    down = nullptr;
    right = nullptr;
  }

  matrixNode(bool hd, Triple t) : head(hd), tp(t) {
    down = nullptr;
    right = nullptr;
  }
};

void initNodeList(matrixNode *&head, int row, int col, int numData) {
  head = new matrixNode(false, Triple(row, col, numData));
  matrixNode *current = head;

  int biggest = max(row, col);

  for (int i = 0; i < biggest; i++) {
    current->next = new matrixNode(true);
    current->next->right = current->next;
    current->next->down = current->next;
    current = current->next;
  }
  current->next = head; // 關閉循環鏈表
}

void addingNode(matrixNode *head, int row, int col, int value) {
  matrixNode *rowHead = head;
  matrixNode *colHead = head;

  for (int i = 0; i <= row; i++) {
    rowHead = rowHead->next;
  }
  for (int j = 0; j <= col; j++) {
    colHead = colHead->next;
  }

  matrixNode *newNode = new matrixNode(false, Triple(row, col, value));

  // 插入到行鏈結
  matrixNode *current = rowHead;
  while (current->right != rowHead && current->right->tp.col < col) {
    current = current->right;
  }
  newNode->right = current->right;
  current->right = newNode;

  // 插入到列鏈結
  current = colHead;
  while (current->down != colHead && current->down->tp.row < row) {
    current = current->down;
  }
  newNode->down = current->down;
  current->down = newNode;
}

void inputMatrix(matrixNode *&head) {
  int row, col, numData;
  cin >> row >> col >> numData;
  initNodeList(head, row, col, numData);

  for (int i = 0; i < numData; i++) {
    int r, c, v;
    cin >> r >> c >> v;
    addingNode(head, r, c, v);
  }
}

void printMatrix(matrixNode *head) {
  matrixNode *rowHead = head->next;
  for (int i = 0; i < head->tp.row; i++) {
    matrixNode *current = rowHead->right;
    for (int j = 0; j < head->tp.col; j++) {
      if (current != rowHead && current->tp.col == j) {
        cout << current->tp.value << " ";
        current = current->right;
      } else {
        cout << "0 ";
      }
    }
    cout << endl;
    rowHead = rowHead->next;
  }
}

void printMatrixLinks(matrixNode *head) {
  cout << "Row:\n";
  matrixNode *rowHead = head->next;
  for (int i = 0; i < head->tp.row; i++) {
    cout << "h[" << i << "]: ";
    matrixNode *current = rowHead->right;
    if (current == rowHead) {
      cout << "No data in this row." << endl;
    } else {
      while (current != rowHead) {
        cout << "row: " << current->tp.row << " , col: " << current->tp.col
             << " , value: " << current->tp.value << endl;
        current = current->right;
      }
    }
    rowHead = rowHead->next;
  }

  cout << "Col:\n";
  matrixNode *colHead = head->next;
  for (int j = 0; j < head->tp.col; j++) {
    cout << "h[" << j << "]: ";
    matrixNode *current = colHead->down;
    if (current == colHead) {
      cout << "No data in this column." << endl;
    } else {
      while (current != colHead) {
        cout << "row: " << current->tp.row << " , col: " << current->tp.col
             << " , value: " << current->tp.value << endl;
        current = current->down;
      }
    }
    colHead = colHead->next;
  }
}

int main() {
  matrixNode *head = nullptr;
  inputMatrix(head);
  printMatrix(head);
  printMatrixLinks(head);
  return 0;
}
