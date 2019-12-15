#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <list>
using namespace std;

template<typename T>
class Graph {
private:
    unordered_map<T, list<T>> m;
    unordered_set<T> vertice;
public:
    void addEdge(T v, T u) {
        m[v].push_back(u);
        m[u].push_back(v);
        vertice.insert(v);
        vertice.insert(u);
    }

    bool bipartite_graph() {
        unordered_map<T, bool> visited;
        unordered_map<T, char> color;
        for (auto v : vertice) {
            visited[v] = false;
            color[v] = 'N';
        }
            
        for (typename unordered_map<T, list<T>>::iterator it = m.begin(); it != m.end(); ++it) {
            if (!visited[it->first]) {
                visited[it->first] = true;
                color[it->first] = 'b';
                if (!BFS_util(it->first, color[it->first], visited, color))
                    return false;
                else continue;
            }
        }
        return true;
    }

    bool BFS_util(T v, char c, unordered_map<T, bool>& visited, unordered_map<T, char>& color) {
        visited[v] = true;
        color[v] = (c == 'b') ? 'r' : 'b';
        bool bi_p = true;
        for (typename list<T>::iterator it = m[v].begin(); it != m[v].end(); ++it) {
            if (color[v] == color[*it]) {
                bi_p = false;
                break;
            }
            if (!visited[*it]) 
                bi_p = BFS_util(*it, color[v], visited, color);
        }
        return bi_p;
    }
};


int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int e;
        cin >> e;
        Graph<int> graph;
        for (int j = 0; j < e; ++j) {
            int v, u;
            cin >> v >> u;
            graph.addEdge(v, u);
        }
        cout << graph.bipartite_graph() << endl;
    }
    return 0;
}