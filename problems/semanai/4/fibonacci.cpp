#include <iostream>
using namespace std;

int sudoku[9][9];
bool rows[9][10], cols[9][10], sq[9][10];
int getSqrd(int r, int c) {
    return r / 3 * 3 + c / 3;
}
bool solveSudoku(int r, int c) {
    if (r >= 9) return true;
    if (c >= 9) return solveSudoku(r + 1, 0);
    if (sudoku[r][c] != 0) return solveSudoku(r, c + 1);
    for (int i = 1; i <= 9; ++i) {
        if (!rows[r][i] && !cols[r][i] && !sq[getSqrd(r, c)][i]) {
            sudoku[r][c] = i;
            rows[r][i] = true;
            cols[c][i] = true;
            sq[getSqrd(r, c)][i] = true;
            if (solveSudoku(r, c + 1)) return true;
            sudoku[r][c] = 0;
            rows[r][i] = false;
            cols[c][i] = false;
            sq[getSqrd(r, c)][i] = false;
        }
        
    }
    return false;
}

int fib[45];
int fib(int n) {

}

int main() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cin >> sudoku[i][j];
            
        }
    }
    solveSudoku(0, 0);
    // Genrar subsets todos
    cout < cnt << endl;
    int N = 5;
    int arr[5] = {30, 7, 20, 9, 13};
    // Recorre hasta 2^N
    for (int i = 0; i < 1 << N; ++i) {
        set<int> s;
        for (int j = 0; j < N; ++j) {
            if (i & 1 << j) {
                s.insert(arr[j]);
            }
        }
        auto it = s.begin();
        while (it != s.end()) {
            cout << *it << " ";
            it++;
        }
        cout << endl;
    }
    return 0;
}