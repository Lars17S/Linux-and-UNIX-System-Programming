#include <iostream>
bool isVowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}
using namespace std;

int main() {
    string str1, str2;
    string str;
    cin >> str1 >> str2;
    if (str1.length() != str2.length()) {
        cout << "No" << endl;
    }
    else {
        // If not vowel, then it is consonant
        for (int i = 0; i < str1.length(); ++i) {
            bool char1 = isVowel(str1[i]);
            bool char2 = isVowel(str2[i]);
            if (char1 != char2) {
                str = "No";
                break;
            }  
        }
        if (str.compare("No")) {
            str = "Yes";
        }
            
        cout << str << endl;
    }
    return 0;
}