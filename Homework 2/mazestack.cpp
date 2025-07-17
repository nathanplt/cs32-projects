#include <stack>
#include <iostream>

using namespace std;

class Coord
{
  public:
    Coord(int r, int c) : m_row(r), m_col(c) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
  private:
    int m_row;
    int m_col;
};


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    // Return true if there is a path from (sr,sc) to (er,ec)
    // through the maze; return false otherwise
    stack<Coord> st;
    st.push(Coord(sr, sc));
    maze[sr][sc] = 'X';
    
    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, 1, 0, -1};
    
    while (!st.empty()) {
        Coord curr = st.top();
        st.pop();
        
        if (curr.r() == er && curr.c() == ec) {
            return true;
        }
        
        for (int i=0; i<4; i++) {
            int nr = curr.r() + dr[i];
            int nc = curr.c() + dc[i];
            
            if (nr < 0 || nc < 0 || nr >= nRows || nc >= nCols) {
                continue;
            }
            
            if (maze[nr][nc] == 'X') {
                continue;
            }
            
            maze[nr][nc] = 'X';
            st.push(Coord(nr, nc));
        }
    }
    return false;
}

int main(int argc, const char * argv[]) {
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

    if (pathExists(maze, 10,10, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
    return 0;
}
