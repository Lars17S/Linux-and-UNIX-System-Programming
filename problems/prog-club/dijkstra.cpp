#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
using namespace std;

template<typename T>
class Graph {
private:
    unordered_map<int, list<int, int>> m;
public:
    void addEdge(int v, int u, int w) {
        m[v].insert(make_pair(u, w));
        m[u].insert(make_pair(v, w));
    }

    string dijkstra(int s) {
        unordered_map<int, bool> dist;
        priority_queue<int> pq;
        for (auto j : m)
            dist[j.first] = 0;
        dist[s] = INT32_MAX;
        unordered_set
    }
};

int main() {
    Graph g;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int num_c, num_h, s, d;
        cin >> num_c >> num_h >> s >> d;
        for (int j = 0; j < num_h; ++j) {
            int v, u, w;
            cin >> v >> u >> w;
            g.addEdge(v, u, w);
        }
    }
    return 0;
}