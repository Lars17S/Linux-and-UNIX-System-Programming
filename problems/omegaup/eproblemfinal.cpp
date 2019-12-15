#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
// Input caso 1 probablemente hay que ajustarlo, ya que esta mal

int main() {
    short D, A;
    unordered_map<string, string> map; // key: reference - value: instance
    vector<string> instance; // instances
    cin >> D >> A;
    cin.clear(); cin.ignore();
    for (short i = 0; i < D; ++i) {
        string str;
        getline(cin, str);
        short left = str.find(' ');
        short right = str.find(' ', left + 1);
        str = str.substr(left + 1, right - (left + 1));
        map[str] = str;
        instance.push_back(str);
    }

    for (short i = 0; i < A; ++i) {
        string str;
        getline(cin, str);
        string p_1 = str.substr(0, str.find(' '));
        string p_2 = str.substr(str.find('=') + 2, str.length() - (str.find('=') + 3));
        map[p_1] = map[p_2];
    }
    
    short count = 0;
    for (vector<string>::iterator it_j = instance.begin(); it_j != instance.end(); ++it_j) {
        for (unordered_map<string, string>::iterator it_i = map.begin(); it_i != map.end(); ++it_i)
            if (it_i->second.compare(*it_j) == 0) {
                ++count;
                break;
            }
    }
    
    cout << count << endl;
    return 0;
}