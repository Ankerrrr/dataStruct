#include "./stack1.hpp"
#include "getMap.hpp"
#include <iostream>

#define EntraceX 1
#define EntraceY 1
#define outX 11
#define outY 15

using namespace std;

int findMaze[mazeRow][mazeCol] = {0};

struct direction {
  int a, b;
} movePos[8] = {
    {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}};

struct node {
  int x, y, dir;
};

string poistionName[8] = {
    "W", "NW", "N", "NE", "E", "SE", "S", "SW"};

ostream &
operator<<(ostream &s, node n) {
  s << "(" << n.x << ", " << n.y << ", " << poistionName[n.dir] << ")" << endl;
  return s;
}

void showRoute(stack<node> myStack) {
  cout << "Start" << endl;
  int tempIndex = 0;
  node temp = {
      EntraceX,
      EntraceY,
      myStack.get(tempIndex).dir};

  cout << temp;

  int height = myStack.size();
  for (int i = 0; i < height; i++) {
    int ind = i + 1;
    cout << "(" << myStack.get(i).x << ", " << myStack.get(i).y << ", " << poistionName[ind < myStack.size() ? myStack.get(ind).dir : -1] << ")" << endl;
  }
  cout << "Fnish" << endl;

  // graphic
  for (int i = 0; i < mazeRow; i++) {
    for (int j = 0; j < mazeCol; j++) {
      bool isRoute = false;
      for (int k = 0; k < myStack.size(); k++) {
        if (myStack.get(k).x == i && myStack.get(k).y == j) {
          isRoute = true;
        }
      }
      if (isRoute || i == EntraceX && j == EntraceY) {
        cout << '*' << ' ';
      } else {
        cout << '1' << ' ';
      }
    }
    cout << endl;
  }
}

void solve(int statrX, int startY, int endX, int endY) {
  stack<node> mystack;
  node temp;
  mystack.push({statrX, startY, -1});
  findMaze[statrX][startY] = 1;

  while (!mystack.empty()) {
    temp = mystack.getTop();
    mystack.pop();

    int x = temp.x;
    int y = temp.y;
    int d = temp.dir + 1;

    for (; d < 8; d++) {
      int g = x + movePos[d].a;
      int h = y + movePos[d].b;

      if (g == endX && h == endY) {
        mystack.push({g, h, d});
        showRoute(mystack);
        return;
      }

      if ((findMaze[g][h]) != 1 && (maze[g][h] == 0)) {
        temp.x = g;
        temp.y = h;
        temp.dir = d;
        mystack.push(temp);
        findMaze[g][h] = 1;

        x = g;
        y = h;
        d = 0;
      }
    }
  }
  throw "cant Find any Route";
}

int main() {
  try {
    loadMap("map.txt");
    solve(EntraceX, EntraceY, outX, outY);
  } catch (char const *msg) {
    cout << msg;
  }
  return 0;
}