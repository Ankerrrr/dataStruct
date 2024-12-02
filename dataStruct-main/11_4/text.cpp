#include <algorithm>
#include <codecvt> // 用於設定 UTF-8 編碼
#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>
#include <vector>

using namespace std;

struct MatrixTerm {
  int row;
  int col;
  int value;
};

class SparseMatrix {
private:
  vector<MatrixTerm> smArray;
  int rows;
  int cols;
  int terms;

public:
  SparseMatrix(int r, int c) : rows(r), cols(c), terms(0) {}

  void addSmTerm(int r, int c, int v) {
    if (v != 0) {
      MatrixTerm term = {r, c, v};
      smArray.push_back(term);
      terms++;
    }
  }

  SparseMatrix FastTranspose() {
    SparseMatrix b(cols, rows);
    if (terms > 0) {
      vector<int> rowSize(cols, 0);
      vector<int> rowStart(cols, 0);

      for (const auto &term : smArray) {
        rowSize[term.col]++;
      }

      rowStart[0] = 0;
      for (int i = 1; i < cols; i++) {
        rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
      }

      for (const auto &term : smArray) {
        int j = rowStart[term.col]++;
        b.smArray.push_back({term.col, term.row, term.value});
      }
    }
    b.terms = this->terms;
    return b;
  }

  SparseMatrix Transpose() {
    SparseMatrix b(cols, rows);
    for (const auto &term : smArray) {
      b.addSmTerm(term.col, term.row, term.value);
    }
    return b;
  }

  void print(wofstream &out) const {
    out << L"smallSPMatrix\n有" << rows << L"列" << cols << L"行" << terms << L"個非零項\n";
    out << L"轉置前的三元組表示法:" << endl;
    out << L"列\t行\t值" << endl;

    for (const auto &term : smArray) {
      out << term.row << L"\t" << term.col << L"\t" << term.value << endl;
    }
  }

  void printTranspose(wofstream &out) const {
    out << L"\nsmallSPMatrix\n有" << cols << L"列" << rows << L"行" << terms << L"個非零項\n";
    out << L"轉置後的三元組表示法:" << endl;
    out << L"列\t行\t值" << endl;

    vector<MatrixTerm> sortedArray = smArray;
    sort(sortedArray.begin(), sortedArray.end(), [](const MatrixTerm &a, const MatrixTerm &b) {
      return (a.row == b.row) ? (a.col < b.col) : (a.row < b.row);
    });

    for (const auto &term : sortedArray) {
      out << term.row << L"\t" << term.col << L"\t" << term.value << endl;
    }
  }

  void printFastTranspose(wofstream &out) const {
    out << L"\nsmallSPMatrix" << endl;
    out << L"快速轉置矩陣:" << endl;

    vector<int> rowSize(cols, 0);
    for (const auto &term : smArray) {
      rowSize[term.col]++;
    }

    out << L"rowSize\t\t";
    for (int i = 0; i < cols; i++) {
      out << rowSize[i] << L"\t";
    }
    out << endl;

    out << L"rowStart\t";
    vector<int> rowStart(cols, 0);
    rowStart[0] = 0;
    for (int i = 1; i < cols; i++) {
      rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
    }
    for (int i = 0; i < cols; i++) {
      out << rowStart[i] << L"\t";
    }
    out << endl;
  }
};

int main() {
  ifstream inputFile("smallSPMatrix.txt");
  if (!inputFile) {
    cerr << "無法打開檔案!" << endl;
    return 1;
  }

  wofstream outputFile("condensed_representation.txt");
  outputFile.imbue(locale(outputFile.getloc(), new codecvt_utf8<wchar_t>));
  if (!outputFile) {
    cerr << "無法創建檔案!" << endl;
    return 1;
  }

  vector<vector<int>> matrix;
  string line;
  while (getline(inputFile, line)) {
    stringstream ss(line);
    vector<int> row;
    int value;
    while (ss >> value) {
      row.push_back(value);
    }
    matrix.push_back(row);
  }

  inputFile.close();

  int rows = matrix.size();
  int cols = matrix[0].size();

  SparseMatrix sparseMatrix(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      sparseMatrix.addSmTerm(i, j, matrix[i][j]);
    }
  }

  sparseMatrix.print(outputFile);

  SparseMatrix transposedMatrix = sparseMatrix.Transpose();
  transposedMatrix.printTranspose(outputFile);

  sparseMatrix.printFastTranspose(outputFile);
  SparseMatrix fastTransposedMatrix = sparseMatrix.FastTranspose();
  fastTransposedMatrix.printTranspose(outputFile);

  outputFile.close();
  return 0;
}