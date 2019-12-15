#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
vector<string> quadrant_algorithm(vector<pair<int, int>>& quadrant, short& N, char num);

int main() {
    vector<pair<int, int>> I_quadrant;
    vector<pair<int, int>> II_quadrant;
    vector<pair<int, int>> III_quadrant;
    vector<pair<int, int>> IV_quadrant;
    short N, A;
    cin >> N;
    cin >> A;
    for (short i = 0; i < A; ++i) {
        short x, y;
        cin >> x >> y;
        cout << "x: " << x << " y: " << y << endl;
        if (x > 0 && y >= 0) {
            I_quadrant.push_back(make_pair(x, y));
            cout << "I_quadrant" << endl;
        }
            
        else if (x <= 0 && y > 0) {
            II_quadrant.push_back(make_pair(x, y));
            cout << "II_quadrant" << endl;
        }
            
        else if (x < 0 && y <= 0) {
            III_quadrant.push_back(make_pair(x, y));
            cout << "III_quadrant" << endl;
        }
            
        else if (x >= 0 && y < 0) {
            IV_quadrant.push_back(make_pair(x, y));
            cout << "IV_quadrant" << endl;
        }
    }
    vector<string> I = quadrant_algorithm(I_quadrant, N, '1');
    vector<string> II = quadrant_algorithm(II_quadrant, N, '2');
    vector<string> III = quadrant_algorithm(III_quadrant, N, '3');
    vector<string> IV = quadrant_algorithm(IV_quadrant, N, '4');
    int diff_I_II = (I.size() - 1) - II.size();
    if (diff_I_II > 0) {
        for (short i = 0; i < diff_I_II; ++i) {
            II.insert(II.begin(), string(II[II.size() - 1].size(), ' '));
        }
    }
    if (diff_I_II < 0) {
        for (short i = 0; i < diff_I_II; ++i) {
            I.insert(I.begin(), string(I[I.size() - 1].size(), ' '));
        }
    }
    vector<string> res;
    for (vector<string>::iterator it = I.begin(), jt= II.begin(); it != I.end(); ++it, ++jt) {
        res.push_back(*jt + *it);
    }

    for (vector<string>::iterator it = res.begin(); it != res.end(); ++it) {
        cout << *it << endl;
    }

    return 0;
}

vector<string> quadrant_algorithm(vector<pair<int, int>>& quadrant, short& N, char num) {
    short max_x = 0, dist_x = 0, max_y = 0, dist_y = 0;
    vector<string> quadrant_str;
    for (vector<pair<int, int>>::iterator it = quadrant.begin(); it != quadrant.end(); ++it) {
        if (abs(max_x) < abs((*it).first))
            max_x = (*it).first;
        if (abs(max_y) < abs((*it).second))
            max_y = (*it).second;
    }
    cout << "max_x: " << max_x << " | max_y: " << max_y << endl;
    if (num == '1') { // a todas las coordenadas x se le resta 1
        short x_size = abs(max_x);
        short y_size = abs(max_y) + 1;
        cout << "x_size: " << x_size << " y_size" << y_size << endl;
        for (short i = 0; i < y_size; ++i) {
            quadrant_str.push_back("");
            for (short j = 0; j < x_size; ++j) {
                quadrant_str[i] += 'o';
            }
        }
        for (vector<pair<int, int>>::iterator it = quadrant.begin(); it != quadrant.end(); ++it) {
            if (sqrt(((*it).first * (*it).first) + ((*it).second * (*it).second)) <= N) { // y = (y_size - 1) - y', x = x' - 1
                quadrant_str[(y_size - 1) - (*it).second][(*it).first - 1] = '+';
            }
            else {
                quadrant_str[(y_size  - 1) - (*it).second][(*it).first - 1] = 'x';
            }    
        }
        for (short i = 0; i < y_size; ++i) {
            for (short j = 0; j < x_size; ++j) {
                cout << quadrant_str[i][j];
            }
            cout << endl;
        }
    }
    else if (num == '2') { // a todas las coordenadas x se le resta 1
        short x_size = abs(max_x) + 1;
        short y_size = abs(max_y);
        cout << "x_size: " << x_size << " y_size" << y_size << endl;
        for (short i = 0; i < y_size; ++i) {
            quadrant_str.push_back("");
            for (short j = 0; j < x_size; ++j) {
                quadrant_str[i] += 'o';
            }
        }
        for (vector<pair<int, int>>::iterator it = quadrant.begin(); it != quadrant.end(); ++it) {
            if (sqrt(((*it).first * (*it).first) + ((*it).second * (*it).second)) <= N) {
                quadrant_str[y_size - (*it).second][x_size + (*it).first - 1] = '+';
            }
            else {
                quadrant_str[y_size - (*it).second][x_size + (*it).first - 1] = 'x';
            }    
        }
        for (short i = 0; i < y_size; ++i) {
            for (short j = 0; j < x_size; ++j) {
                cout << quadrant_str[i][j];
            }
            cout << endl;
        }
    }   
    else if (num == '3') { // a todas las coordenadas x se le resta 1
        short x_size = abs(max_x);
        short y_size = abs(max_y) + 1;
        cout << "x_size: " << x_size << " y_size" << y_size << endl;
        for (short i = 0; i < y_size; ++i) {
            quadrant_str.push_back("");
            for (short j = 0; j < x_size; ++j) {
                quadrant_str[i] += 'o';
            }
        }
        for (vector<pair<int, int>>::iterator it = quadrant.begin(); it != quadrant.end(); ++it) {
            if (sqrt(((*it).first * (*it).first) + ((*it).second * (*it).second)) <= N) {
                quadrant_str[-(*it).second][x_size + (*it).first] = '+';
            }
            else {
                quadrant_str[-(*it).second][x_size + (*it).first] = 'x';
            }    
        }
        for (short i = 0; i < y_size; ++i) {
            for (short j = 0; j < x_size; ++j) {
                cout << quadrant_str[i][j];
            }
            cout << endl;
        }
    }  
    else if (num == '4') { // a todas las coordenadas x se le resta 1
        short x_size = abs(max_x) + 1;
        short y_size = abs(max_y);
        cout << "x_size: " << x_size << " y_size" << y_size << endl;
        for (short i = 0; i < y_size; ++i) {
            quadrant_str.push_back("");
            for (short j = 0; j < x_size; ++j) {
                quadrant_str[i] += 'o';
            }
        }
        for (vector<pair<int, int>>::iterator it = quadrant.begin(); it != quadrant.end(); ++it) {
            if (sqrt(((*it).first * (*it).first) + ((*it).second * (*it).second)) <= N) {
                quadrant_str[-(*it).second - 1][(*it).first] = '+';
            }
            else {
                quadrant_str[-(*it).second - 1][(*it).first] = 'x';
            }    
        }
        for (short i = 0; i < y_size; ++i) {
            for (short j = 0; j < x_size; ++j) {
                cout << quadrant_str[i][j];
            }
            cout << endl;
        }
    }  
    return quadrant_str;
}