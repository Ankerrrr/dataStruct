#ifndef GETMAP_HPP
#define GETMAP_HPP
#include <fstream>
#include <iostream>
#include <string>

#define mazeRow 13 // ¤@
#define mazeCol 17 // 1

using namespace std;

int maze[mazeRow][mazeCol];

bool loadMap(const string &filename) {
  ifstream inputfile(filename);
  if (!inputfile.is_open()) {
    throw "cant not open File, plz check file name";
  }

  string line;
  for (int i = 0; i < mazeRow; i++) {
    if (!getline(inputfile, line) || line.size() != mazeCol) {
      throw "problem occur read file";
      inputfile.close();
      return false;
    }

    for (int j = 0; j < mazeCol; j++) {
      if (line[j] >= '0' && line[j] < '2') {
        maze[i][j] = line[j] - '0';
      } else {
        throw "problem occur read file";
        inputfile.close();
        return false;
      }
    }
  }
  inputfile.close();
  return true;
}

#endif