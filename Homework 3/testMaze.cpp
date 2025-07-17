#include <string>
#include <cassert>
#include <iostream>
using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    if (sr == er && sc == ec) {
        return true;
    }
    
    maze[sr][sc] = 'X';
    
    int dr[] = {1, 0, -1, 0};
    int dc[] = {0, 1, 0, -1};
    for (int i=0; i<4; i++) {
        int nr = sr + dr[i];
        int nc = sc + dc[i];
        
        if (nr < 0 || nc < 0 || nr >= nRows || nc >= nCols) {
            continue;
        }
        
        if (maze[nr][nc] == 'X') {
            continue;
        }
        
        if (pathExists(maze, nRows, nCols, nr, nc, er, ec)) {
            return true;
        }
    }
    return false;
}

int main() {
    string maze[10] = {
        "XXXXXXXXXX",
        "X........X",
        "XX.X.XXXXX",
        "X..X.X...X",
        "X..X...X.X",
        "XXXX.XXX.X",
        "X.X....XXX",
        "X..XX.XX.X",
        "X...X....X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze, 10, 10, 1, 1, 6, 1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
