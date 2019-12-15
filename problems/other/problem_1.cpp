#include <iostream>
#include <map>
#include <vector>
#include <set>
using namespace std;
vector<int> find_repeated(vector<int> a);

int main() {
    int n;
    vector<int> a;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int input;
        cin >> input;
        a.push_back(input);
    }
    vector<int> res = find_repeated(a);
    for (int x : res)
        cout << x << " ";

    return 0;
}

vector<int> find_repeated(vector<int> a) {
    map<int, pair<int, int>> key_order; //key, index - count
    set<pair<int, int>> key_rept; //index, element
    vector<int> result;
    int i = 0;
    for (vector<int>::iterator it = a.begin(); it != a.end(); ++it) {
        if (key_order.count(*it) == 0)
            key_order[*it] = make_pair(i, 1);
        else
            ++key_order.at(*it).second;
        ++i;
    }

    int max = -1;
    for (map<int, pair<int, int>>::iterator it = key_order.begin(); it != key_order.end(); ++it) {
        if (max < (it->second).second) {
            key_rept.clear();
            key_rept.insert(make_pair((it->second).first, it->first));
            max = (it->second).second;
        }
        else if (max == (it->second).second)
            key_rept.insert(make_pair((it->second).first, it->first));
    }

    for (set<pair<int, int>>::iterator it = key_rept.begin(); it != key_rept.end(); ++it)
        result.push_back(it->second);
        
    return result;
}