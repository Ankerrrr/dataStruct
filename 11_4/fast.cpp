#include "./data.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void printMatrix(ofstream &outfile, int const **matrix, int row, int col, bool Mumble = false, bool tableShow = false) {
  if (tableShow) {
    for (int i = 0; i < row; i++) {
      outfile << matrix[i][0] << ", " << matrix[i][1] << ", " << matrix[i][2] << endl;
    }
    return;
  }
  if (!Mumble) {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        outfile << "第" << i << "行第" << j << "列:" << matrix[i][j] << endl;
      }
      outfile << "-------------------" << endl;
    }
  } else {
    for (int i = 0; i < row; i++) {
      outfile << "第" << matrix[i][0] << "行第" << matrix[i][1] << "列:" << matrix[i][2] << endl;
    }
    outfile << "-------------------" << endl;
  }
}

void inputMatrix(ofstream &outfile, int **orignal, int sizeCol, int &sizeRow) {
  outfile << "請輸入矩陣的內容" << endl;
  for (int i = 0; i < sizeRow; i++) {
    for (int j = 0; j < sizeCol; j++) {
      outfile << "第" << i << "行第" << j << "列:";
      cin >> orignal[i][j];
      if (cin.fail()) {
        outfile << "不要亂打!" << endl;
        cin.clear();
        j--;
      }
    }
    outfile << "-------------------" << endl;
  }
}

void initMatrix(int **&matrix, int &sizeCol, int &sizeRow) {
  cout << "請輸入矩陣大小:\n列";
  cin >> sizeCol;
  cout << "行";
  cin >> sizeRow;

  matrix = new int *[sizeRow];
  for (int i = 0; i < sizeRow; i++) {
    matrix[i] = new int[sizeCol];
  }
}

void copyMatrix(int **&dest, int src[25][12], int col, int row) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      dest[i][j] = src[i][j];
    }
  }
}

void notZeroMatrixAndInit(int **&matrix, int sizeCol, int sizeRow, int **&newMatrix, int &newMatrixIndex) {
  int *x, *y;
  x = new int[sizeCol * sizeRow + 1];
  y = new int[sizeCol * sizeRow + 1];
  newMatrixIndex = 0;

  for (int i = 0; i < sizeRow; i++) {
    for (int j = 0; j < sizeCol; j++) {
      if (matrix[i][j] != 0) {
        x[newMatrixIndex] = i;
        y[newMatrixIndex] = j;
        newMatrixIndex++;
      }
    }
  }
  newMatrix = new int *[newMatrixIndex];
  for (int i = 0; i < newMatrixIndex; i++) {
    newMatrix[i] = new int[3];
    newMatrix[i][0] = x[i];
    newMatrix[i][1] = y[i];
    newMatrix[i][2] = matrix[x[i]][y[i]];
  }

  delete[] x;
  delete[] y;
}

void fastTransposeMatrix(int **matrix, int newMatrixIndex, int sizeCol, int sizeRow, int **&resultMatrix) {
  // Step 1: 計算每列的非零元素數量
  int *colCount = new int[sizeCol]{0};
  for (int i = 0; i < newMatrixIndex; i++) {
    colCount[matrix[i][1]]++;
  }

  // Step 2: 計算每列的起始位置
  int *startPosition = new int[sizeCol]{0};
  for (int i = 1; i < sizeCol; i++) {
    startPosition[i] = startPosition[i - 1] + colCount[i - 1];
  }

  // Step 3: 填入轉置後的位置
  resultMatrix = new int *[newMatrixIndex];
  for (int i = 0; i < newMatrixIndex; i++) {
    resultMatrix[i] = new int[3];
  }
  for (int i = 0; i < newMatrixIndex; i++) {
    int col = matrix[i][1];       // 原列（轉置後成為行）
    int pos = startPosition[col]; // 取得該行的當前插入位置

    resultMatrix[pos][0] = matrix[i][1]; // 新行
    resultMatrix[pos][1] = matrix[i][0]; // 新列
    resultMatrix[pos][2] = matrix[i][2]; // 值
    startPosition[col]++;                // 更新起始位置以避免重疊
  }

  delete[] colCount;
  delete[] startPosition;
}

void deleteMatrix(int **&matrix, int count) {
  for (int i = 0; i < count; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

int main() {
  ofstream outfile("FastOutput.txt");
  if (!outfile.is_open()) {
    cerr << "無法開啟檔案" << endl;
    return 1;
  }

  int **orignal;
  int **newMatrix;
  int **transposedMatrix;
  int sizeCol = 0;
  int sizeRow = 0;
  int newMatrixIndex = 0;

  initMatrix(orignal, sizeCol, sizeRow);
  copyMatrix(orignal, SPMatrix, sizeCol, sizeRow);
  printMatrix(outfile, const_cast<int const **>(orignal), sizeRow, sizeCol, false);
  notZeroMatrixAndInit(orignal, sizeCol, sizeRow, newMatrix, newMatrixIndex);
  outfile << "模糊後:" << endl;
  printMatrix(outfile, const_cast<int const **>(newMatrix), newMatrixIndex, 3, true);

  fastTransposeMatrix(newMatrix, newMatrixIndex, sizeCol, sizeRow, transposedMatrix);
  outfile << "轉制後:" << endl;
  printMatrix(outfile, const_cast<int const **>(transposedMatrix), newMatrixIndex, 3, true);
  printMatrix(outfile, const_cast<int const **>(transposedMatrix), newMatrixIndex, 3, true, true);
  deleteMatrix(orignal, sizeRow);
  deleteMatrix(newMatrix, 3);

  outfile.close();
  return 0;
}
