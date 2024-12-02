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

void swapRow(int **&matrix, int src, int dest) {
  int tempX, tempY, tempA;
  tempX = matrix[src][0];
  tempY = matrix[src][1];
  tempA = matrix[src][2];
  matrix[src][0] = matrix[dest][0];
  matrix[src][1] = matrix[dest][1];
  matrix[dest][0] = tempX;
  matrix[dest][1] = tempY;
  matrix[dest][2] = tempA;
}

void transposeMatrix(int **&matrix, int size) {
  for (int i = 0; i < size; i++) {
    int temp = matrix[i][0];
    matrix[i][0] = matrix[i][1];
    matrix[i][1] = temp;
  }
  for (int i = 0; i < size - 1; i++) {
    int compIndex = i;
    for (int j = i + 1; j < size; j++) {
      if (matrix[j][0] < matrix[compIndex][0] ||
          (matrix[j][0] == matrix[compIndex][0] && matrix[j][1] < matrix[compIndex][1])) {
        compIndex = j;
      }
    }
    if ((compIndex != i)) {
      swapRow(matrix, compIndex, i);
    }
  }
}

void deleteMatrix(int **&matrix, int count) {
  for (int i = 0; i < count; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

int main() {
  ofstream outfile("output.txt");
  if (!outfile.is_open()) {
    cerr << "無法開啟檔案" << endl;
    return 1;
  }

  int **orignal;
  int **newMatrix;
  int sizeCol = 0;
  int sizeRow = 0;
  int newMatrixIndex = 0;

  initMatrix(orignal, sizeCol, sizeRow);
  copyMatrix(orignal, SPMatrix, sizeCol, sizeRow);
  printMatrix(outfile, const_cast<int const **>(orignal), sizeRow, sizeCol, false);
  notZeroMatrixAndInit(orignal, sizeCol, sizeRow, newMatrix, newMatrixIndex);
  outfile << "模糊後:" << endl;
  printMatrix(outfile, const_cast<int const **>(newMatrix), newMatrixIndex, 3, true);

  transposeMatrix(newMatrix, newMatrixIndex);
  outfile << "轉制後:" << endl;
  printMatrix(outfile, const_cast<int const **>(newMatrix), newMatrixIndex, 3, true);
  printMatrix(outfile, const_cast<int const **>(newMatrix), newMatrixIndex, 3, true, true);
  deleteMatrix(orignal, sizeRow);
  deleteMatrix(newMatrix, 3);

  outfile.close();
  return 0;
}
