#include <iostream>
using namespace std;


int main() {
    int rows = 10, cols = 10;
    int** arr = new int*[rows];
    for(int i = 0; i < rows; ++i) 
        arr[i] = new int[cols];
    for(int i = 0; i < rows; ++i)  {
        for (int j = 0; j < cols; ++j) {
            arr[i][j] = 1;
        }
    }
    arr[2][3] = 3;
    for(int i = 0; i < rows; ++i)  {
        for (int j = 0; j < cols; ++j) {
            cout << arr[i][j];
        }
        cout << endl;
    }


    }
    for (short x = x_trans(limitX_1); x <= x_trans(limitX_2); ++x) {
        arr[rows/2][x] = 'k';
    }
    return 0;
}