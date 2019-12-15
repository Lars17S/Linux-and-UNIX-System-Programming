#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
short y_trans(short& y);
short x_trans(short& x);

int rows = 1000;
int cols = 1000;

int main() {
    char** arr = new char*[rows];
    for(int i = 0; i < rows; ++i) 
        arr[i] = new char[cols];
    vector<pair<short, short>> I_quadrant;
    vector<pair<short, short>> II_quadrant;
    vector<pair<short, short>> III_quadrant;
    vector<pair<short, short>> IV_quadrant;
    short A, N;
    cin >> A >> N;
    short limitX_1 = 1000;
    short limitY_1 = -1000;
    short limitX_2 = -1000;
    short limitY_2 = 1000;
    for (short i = 0; i < N; ++i) {
        short x, y;
        cin >> x >> y;
        if (limitX_1 > x)
            limitX_1 = x;
        if (limitY_1 < y)
            limitY_1 = y;
        if (limitX_2 < x)
            limitX_2 = x;
        if (limitY_2 > y)
            limitY_2 = y;
        if (x > 0 && y >= 0) {
            I_quadrant.push_back(make_pair(x, y));
            cout << "P = x: " << x << ", y: " << y << " I quadrant" << endl;
        }
            
        else if (x <= 0 && y > 0) {
            II_quadrant.push_back(make_pair(x, y));
            cout << "P = x: " << x << ", y: " << y << " II quadrant" << endl;
        }
            
        else if (x < 0 && y <= 0) {
            III_quadrant.push_back(make_pair(x, y));
            cout << "P = x: " << x << ", y: " << y << " III quadrant" << endl;
        }
            
        else if (x >= 0 && y < 0) {
            IV_quadrant.push_back(make_pair(x, y));
            cout << "P = x: " << x << ", y: " << y << " IV quadrant" << endl;
        }
    }

    if (limitX_1 > 0)
        limitX_1 = 0;
    if (limitY_1 < 0)
        limitY_1 = 0;
    if (limitX_2 < 0)
        limitX_2 = 0;
    if (limitY_2 > 0)
        limitY_2 = 0;

    cout << "limitX_1: " << limitX_1 << " TRANSFORM: " << x_trans(limitX_1) << endl;
    cout << "limitY_1: " << limitY_1 << " TRANSFORM: " << y_trans(limitY_1) << endl;
    cout << "limitX_2: " << limitX_2 << " TRANSFORM: " << x_trans(limitX_2) << endl;
    cout << "limitY_2: " << limitY_2 << " TRANSFORM: " << y_trans(limitY_2) << endl;

    for (short y = y_trans(limitY_1); y <= y_trans(limitY_2); ++y) {
        for (short x = x_trans(limitX_1); x <= x_trans(limitX_2); ++x) {
            arr[y][x] = ' ';
        }
    }

    arr[rows/2][cols/2] = '#';
    
    

    if (!I_quadrant.empty()) {
        short I_limitx = 0, I_limity = 0;
        for(vector<pair<short, short>>::iterator it = I_quadrant.begin(); it != I_quadrant.end(); ++it) {
            if (sqrt(((*it).first * (*it).first) + ((*it).second * (*it).second)) <= A) {
                arr[y_trans((*it).second)][x_trans((*it).first)] = '+';
            }
            else {
                arr[y_trans((*it).second)][x_trans((*it).first)] = 'x';
            }
            if (I_limitx < (*it).first) {
                I_limitx = (*it).first;
            }
            if (I_limity < (*it).second) {
                I_limity = (*it).second;
            }
        }
        cout << "I_limitx: " << I_limitx << " I_limity: " << I_limity << endl;
        // Draw I quadrant
        // arr[Y][X]
        for (short y = rows/2; y >= y_trans(I_limity); --y) {
            for (short x = cols/2 + 1; x <= x_trans(I_limitx); ++x) {
                if (arr[y][x] != 'x' && arr[y][x] != '+') 
                    arr[y][x] = 'o';
            }
        }
    }

    if (!II_quadrant.empty()) {
        short I_limitx = 0, I_limity = 0;
        for(vector<pair<short, short>>::iterator it = II_quadrant.begin(); it != II_quadrant.end(); ++it) {
            if (sqrt(((*it).first * (*it).first) + ((*it).second * (*it).second)) <= A) {
                arr[y_trans((*it).second)][x_trans((*it).first)] = '+';
            }
            else {
                arr[y_trans((*it).second)][x_trans((*it).first)] = 'x';
            }
            if (I_limitx > (*it).first) {
                I_limitx = (*it).first;
            }
            if (I_limity < (*it).second) {
                I_limity = (*it).second;
            }
        }
        cout << "I_limitx: " << I_limitx << " I_limity: " << I_limity << endl;
        for (short y = rows/2 - 1; y >= y_trans(I_limity); --y) {
            for (short x = cols/2; x >= x_trans(I_limitx); --x) {
                if (arr[y][x] != 'x' && arr[y][x] != '+') 
                    arr[y][x] = 'o';
            }
        }
    }

    if (!III_quadrant.empty()) {
        short I_limitx = 0, I_limity = 0;
        for(vector<pair<short, short>>::iterator it = III_quadrant.begin(); it != III_quadrant.end(); ++it) {
            if (sqrt(((*it).first * (*it).first) + ((*it).second * (*it).second)) <= A) {
                arr[y_trans((*it).second)][x_trans((*it).first)] = '+';
            }
            else {
                arr[y_trans((*it).second)][x_trans((*it).first)] = 'x';
            }
            if (I_limitx > (*it).first) {
                I_limitx = (*it).first;
            }
            if (I_limity > (*it).second) {
                I_limity = (*it).second;
            }
        }
        cout << "I_limitx: " << I_limitx << " I_limity: " << I_limity << endl;
        for (short y = rows/2; y <= y_trans(I_limity); ++y) {
            for (short x = cols/2 - 1; x >= x_trans(I_limitx); --x) {
                if (arr[y][x] != 'x' && arr[y][x] != '+') 
                    arr[y][x] = 'o';
            }
        }
    }

    if (!IV_quadrant.empty()) {
        short I_limitx = 0, I_limity = 0;
        for(vector<pair<short, short>>::iterator it = IV_quadrant.begin(); it != IV_quadrant.end(); ++it) {
            if (sqrt(((*it).first * (*it).first) + ((*it).second * (*it).second)) <= A) {
                arr[y_trans((*it).second)][x_trans((*it).first)] = '+';
            }
            else {
                arr[y_trans((*it).second)][x_trans((*it).first)] = 'x';
            }
            if (I_limitx < (*it).first) {
                I_limitx = (*it).first;
            }
            if (I_limity > (*it).second) {
                I_limity = (*it).second;
            }
        }
        cout << "I_limitx: " << I_limitx << " I_limity: " << I_limity << endl;
        for (short y = rows/2 + 1; y <= y_trans(I_limity); ++y) {
            for (short x = cols/2; x <= x_trans(I_limitx); ++x) {
                if (arr[y][x] != 'x' && arr[y][x] != '+') 
                    arr[y][x] = 'o';
            }
        }
    }
    
    for (short y = y_trans(limitY_1); y <= y_trans(limitY_2); ++y) {
        for (short x = x_trans(limitX_1); x <= x_trans(limitX_2); ++x) {
            cout << arr[y][x];
        }
        cout << endl;
    }

    return 0;
}

short y_trans(short& y) {
    return -y + rows/2;
}

short x_trans(short& x) {
    return x + cols/2;
}