#include <algorithm>
#include <iostream>

using namespace std;

class best {
public:
  int rowMaxStore[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
  int rowindex[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
  int bestSum = 0;
  void findMax();

private:
  int table[8][8] = {
      {522, 703, 366, 131, 167, 938, 935, 553},
      {35, 842, 39, 346, 169, 82, 37, 702},
      {139, 942, 649, 77, 835, 81, 813, 537},
      {618, 246, 208, 599, 44, 662, 655, 365},
      {703, 983, 680, 333, 462, 365, 652, 31},
      {46, 978, 832, 702, 812, 850, 641, 176},
      {848, 266, 281, 849, 715, 38, 370, 81},
      {160, 865, 262, 849, 570, 647, 553, 902}};
};

void best::findMax() {
  int columns[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  do {
    int currentSum = 0;
    int currentRowMax[8];
    for (int row = 0; row < 8; row++) {
      currentRowMax[row] = table[row][columns[row]];
      currentSum += currentRowMax[row];
    }

    if (currentSum > bestSum) {
      bestSum = currentSum;
      for (int i = 0; i < 8; i++) {
        rowMaxStore[i] = currentRowMax[i];
        rowindex[i] = columns[i];
      }
    }
  } while (next_permutation(columns, columns + 8));
}

int main() {
  best b;
  b.findMax();

  // 輸出結果
  cout << "最優解的總和為: " << b.bestSum << endl;
  for (int i = 0; i < 8; i++) {
    cout << "第" << i << "行選擇的最大值為: " << b.rowMaxStore[i] << "，對應的列索引為: " << b.rowindex[i] << endl;
  }

  return 0;
}
