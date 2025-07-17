#include "History.h"
#include "globals.h"
#include <iostream>

using namespace std;

History::History(int nRows, int nCols) {
    m_rows = nRows;
    m_cols = nCols;
    
    for (int i=0; i<m_rows; i++) {
        for (int j=0; j<m_cols; j++) {
            m_grid[i][j] = 0;
        }
    }
}

bool History::record(int r, int c) {
    if (r <= 0 || c <= 0 || r > m_rows || c > m_cols) {
        return false;
    }
    
    m_grid[r-1][c-1]++;
    return true;
}

void History::display() const {
    clearScreen();
    
    for (int i=0; i<m_rows; i++) {
        for (int j=0; j<m_cols; j++) {
            int num = m_grid[i][j];
            
            if (num == 0) {
                cout << '.';
            } else if (num < 26) {
                cout << (char) ('A' + num - 1);
            } else {
                cout << 'Z';
            }
        }
        cout << endl;
    }
    cout << endl;
}
