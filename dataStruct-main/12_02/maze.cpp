#include "./stack1.hpp"
#include "getMap.hpp"
#include <iostream>

#define EntraceX 1
#define EntraceY 1
//#define outX 11
//#define outY 15

#define outX 15
#define outY 15

using namespace std;

int findMaze[mazeRow][mazeCol] = { 0 };

struct direction {
    int a, b;
} movePos[8] = {
    {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1} };

struct node {
    int x, y, dir;
};

string poistionName[8] = {
    "W", "NW", "N", "NE", "E", "SE", "S", "SW" };

ostream&
operator<<(ostream& s, node n) {
    s << "(" << n.x << ", " << n.y << ", " << (n.dir >= 0 ? poistionName[n.dir] : "") << ")" << endl;
    return s;
}

void showRoute(stack<node> myStack) {
    cout << "Start" << endl;

    int height = myStack.size();
    for (int i = 0; i < height; i++) {
        int ind = i;
        cout << "(" << myStack.get(i).x << ", " << myStack.get(i).y << ", "
            << (ind < myStack.size() ? poistionName[myStack.get(ind).dir] : "") << ")" << endl;
    }
    cout << "Finish" << endl;

    // graphic
    for (int i = 0; i < mazeRow; i++) {
        for (int j = 0; j < mazeCol; j++) {
            bool isRoute = false;
            for (int k = 0; k < myStack.size(); k++) {
                if (myStack.get(k).x == i && myStack.get(k).y == j) {
                    isRoute = true;
                    break; // 提高效率
                }
            }
            if (isRoute || (i == EntraceX && j == EntraceY)) {
                cout << '*' << ' ';
            }
            else if (!isRoute && (maze[i][j] == 0)) {
                cout << '0' << ' ';
            }else{
                cout << 'x' << ' ';
            }
        }
        cout << endl;
    }
}

void solve(int startX, int startY, int endX, int endY) {
    stack<node> mystack;
    node temp;
    mystack.push({ startX, startY, -1 });
    findMaze[startX][startY] = 1;

    while (!mystack.empty()) {
        temp = mystack.getTop();
        mystack.pop();

        int x = temp.x;
        int y = temp.y;
        int d = temp.dir + 1;

        while (d < 8) {
            int g = x + movePos[d].a;
            int h = y + movePos[d].b;

            if (g == endX && h == endY) {
                mystack.push({ x, y, d }); // 先將目前節點推回堆疊
                mystack.push({ g, h, d }); // 再將終點推入堆疊
                showRoute(mystack);
                return;
            }


            if (g >= 0 && g < mazeRow && h >= 0 && h < mazeCol && findMaze[g][h] != 1 && maze[g][h] == 0) {
                mystack.push({ x, y, d });
                findMaze[g][h] = 1; // 標記新節點
                x = g;
                y = h;
                d = -1; // 重置方向
            }
            else {
                d++;
            }
        }
        findMaze[temp.x][temp.y] = 0; // 回溯時清除標記
    }
    throw "Can't Find Any Route";
}

int main() {
    try {
        /*loadMap("map.txt");*/
        loadMap("map2.txt");
        for (int i = 0; i < mazeRow; i++) {
            for (int j = 0; j < mazeCol; j++) {
                cout << maze[i][j] << ", ";
            }
            cout << endl;
        }
        solve(EntraceX, EntraceY, outX, outY);
    }
    catch (const char* msg) {
        cout << msg;
    }
    return 0;
}
