#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
string encrypt(string text, int& G, int& C);
string decrypt(string text, int& G, int& C);

int main() {
    string str1, str2;
    getline(cin, str1);
    getline(cin, str2);
    int G = stoi(str2.substr(1, str2.find(' ') - 1));
    int C = stoi(str2.substr(str2.find('c') + 1, (int)str2.length() - (str2.find('c') + 1)));
    if (str1[0] == 'e' || str1[0] == 'E') {
        for (std::string::size_type i = 1; i < str1.length(); ++i)
            str1[i] = toupper(str1[i]);
        cout << encrypt(str1.substr(1, str1.length() - 1), G, C) << endl;
    }
    else if (str1[0] == 'd' || str1[0] == 'D')
        cout << decrypt(str1.substr(1, str1.length() - 1), G, C) << endl;

    return 0;
}

string encrypt(string text, int& G, int& C) {
    string res;
    vector<string> pack_str;
    for (int i = 0; i < text.length(); i += min((int)text.length() - i, G)) {
        pack_str.push_back(text.substr(i, min((int)text.length() - i, G)));
        reverse(pack_str.at(pack_str.size() - 1).begin(), pack_str.at(pack_str.size() - 1).end());
    }
    for (vector<string>::iterator it = pack_str.begin(); it != pack_str.end(); ++it)
        for (char s : *it) 
            res += char((int)s + C);

    return res;
}

string decrypt(string text, int& G, int& C) {
    string res;
    vector<string> pack_str;
    for (char s : text)
        res += char((int)s - C);
    for (int i = 0; i < res.length(); i += min((int)res.length() - i, G)) {
        pack_str.push_back(res.substr(i, min((int)text.length() - i, G)));
        reverse(pack_str.at(pack_str.size() - 1).begin(), pack_str.at(pack_str.size() - 1).end());
    }
    res = "";
    for (vector<string>::iterator it = pack_str.begin(); it != pack_str.end(); ++it)
        res += *it;

    return res;
}