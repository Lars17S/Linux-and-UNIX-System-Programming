#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <tuple>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef unordered_map<int, list<tuple<int, int, bool>>> dir_graph_structure;

class DirectionalGraph {
public:
    dir_graph_structure m; //nalGraph graph_sort; Vertex | List<pointer, weight>
    unordered_map<int, int> v_set; // Set V vertex: Vertex - Max weight
    list<int> topological_sort; // Topological sort
    vector<int> max_vertex;

    int root; 
    int weight = 0;

    void topologicalSort();
    void topologicalSortUtil(int v, unordered_map<int, bool>& visited);
    DirectionalGraph buildMaxGraph();
    DirectionalGraph buildMaxGraphUtil(int& v, unordered_map<int, bool>& visited);
    DirectionalGraph buildSubGraph(int& v);
    void weightGraphUtil(int v, unordered_map<int, bool>& visited);
    void addEdge(int& v, int& u, int weight);
    void setRoot(int& root);
    void mergeGraph(DirectionalGraph sub_graph);
    void mergeGraphMax(DirectionalGraph& max_graph);
    void longestPath(DirectionalGraph& original_graph);
    void longestPathUtil();
    
    void makeV_set();
    void printGraph(); 
    void clearGraph();
    void weightGraph();
};

void DirectionalGraph::setRoot(int& root) {
    this->root = root;
}

void DirectionalGraph::makeV_set() {
    for (auto m_it : m) {
        v_set[m_it.first] = 0;
        for (auto l_it : m_it.second)
            v_set[get<0>(l_it)] = 0;
    }
}

void DirectionalGraph::addEdge(int& v, int& u, int weight) {
    m[v].push_front(make_tuple(u, weight, true));
    v_set[v] = 0;
    v_set[u] = 0;
}

void DirectionalGraph::clearGraph() {
    m.clear();
}

void DirectionalGraph::mergeGraph(DirectionalGraph sub_graph) {
    // Set union of root trees
    weight = sub_graph.weight;
    addEdge(root, sub_graph.root, sub_graph.weight + 1);
    // Add each (u, v) edge from sub_graph to graph
    if (!sub_graph.m.empty())
        for (dir_graph_structure::iterator it = sub_graph.m.begin(); it != sub_graph.m.end(); ++it)
            m[it->first] = it->second;
}

void DirectionalGraph::mergeGraphMax(DirectionalGraph& max_graph) {
    weight = max_graph.weight;
    if (!max_graph.m.empty())
        for (dir_graph_structure::iterator it = max_graph.m.begin(); it != max_graph.m.end(); ++it)
            m[it->first] = it->second;
}

void DirectionalGraph::printGraph() {
    cout << "VERTEX_SET: ";
    for (auto v : v_set) 
        cout << "v: " << v.first << " weight: " << v.second << " | ";
    cout << endl;
    cout << "TOPOLOGICAL_SORT: ";
    for (int v : topological_sort) 
        cout << v << " ";
    cout << endl;
    cout << "MAX_VERTEX: "; 
    for (int v : max_vertex)
        cout << v << " ";
    cout << endl;
    for (dir_graph_structure::iterator it = m.begin(); it != m.end(); ++it)
        for (tuple<int, int, bool> u : it->second)
            cout << it->first << " -> (" << get<0>(u) << ", " << get<1>(u) << ")" << endl;
}

void DirectionalGraph::weightGraphUtil(int v, unordered_map<int, bool>& visited) {
    int weight = 0;
    for (list<tuple<int, int, bool>>::iterator it = m[v].begin(); it != m[v].end(); ++it) {
        tuple<int, int, bool> u = *it;
        if (!visited[get<0>(u)])
            weightGraphUtil(get<0>(u), visited);
        get<1>(*it) = v_set[get<0>(u)] + 1;
        if (weight < get<1>(*it))
            weight = get<1>(*it);
    }
    visited[v] = true;
    v_set[v] = weight;
}

void DirectionalGraph::weightGraph() {
    unordered_map<int, bool> visited;
    for (auto v : v_set) 
        visited[v.first] = false;
    
    for (auto it = v_set.begin(); it != v_set.end(); ++it) { 
        if (!visited[it->first])
            weightGraphUtil(it->first, visited); 
        visited[it->first] = true;
    }
}


DirectionalGraph DirectionalGraph::buildMaxGraphUtil(int& v, unordered_map<int, bool>& visited) {
    DirectionalGraph max_graph;
    max_graph.setRoot(v);
    if (!m[v].empty()) {
        for (list<tuple<int, int, bool>>::iterator it = m[v].begin(); it != m[v].end(); ++it) {
            tuple<int, int, bool> u = *it;
            DirectionalGraph sub_graph;
            // Recursive call
            if (!visited[get<0>(u)]) {
                sub_graph = buildMaxGraphUtil(get<0>(u), visited);
            }
            // Non-recursive call
            else {
                sub_graph.setRoot(get<0>(u));
                sub_graph.weight = v_set[get<0>(u)]; 
            }
            if (max_graph.weight < sub_graph.weight) { // At first moment, weight is equal to zero
                max_graph.clearGraph();
                max_graph.mergeGraph(sub_graph);
            }
            else if (max_graph.weight == sub_graph.weight) 
                max_graph.mergeGraph(sub_graph); 
        }
        max_graph.weight = max_graph.weight + 1;
    }
    visited[v] = true;
    return max_graph;
}

DirectionalGraph DirectionalGraph::buildMaxGraph() {
    unordered_map<int, bool> visited;
    int max = -1;
    for (pair<int, int> v : v_set) {
        if (max < v.second)
            max = v.second;
        visited[v.first] = false;
    }
        
    for (pair<int, int> v : v_set) 
        if (v.second == max)
            max_vertex.push_back(v.first);

    DirectionalGraph max_graph;
    for (vector<int>::reverse_iterator it = max_vertex.rbegin(); it != max_vertex.rend(); ++it) {
        DirectionalGraph max_sub_graph = buildMaxGraphUtil(*it, visited);
        max_graph.mergeGraphMax(max_sub_graph);
        visited[*it] = true;
    }
    max_graph.max_vertex = max_vertex;
    max_graph.makeV_set();
    return max_graph;
}


DirectionalGraph DirectionalGraph::buildSubGraph(int& v) {
    DirectionalGraph graph;
    graph.setRoot(v);
    if (!m[v].empty())
        for (list<tuple<int, int, bool>>::iterator it = m[v].begin(); it != m[v].end(); ++it) {
            // Recursive call
            DirectionalGraph sub_graph = buildSubGraph(get<0>(*it));
            graph.mergeGraph(sub_graph);
        }    
    return graph;
}

void DirectionalGraph::longestPath(DirectionalGraph& original_graph) {
    unordered_map<int, int> dist;
    for (int v_i : topological_sort)
        dist[v_i] = -1;
    int min_possible = INT16_MAX;
    for (dir_graph_structure::iterator it_i = m.begin(); it_i != m.end(); ++it_i) {
        for (list<tuple<int, int, bool>>::iterator it_j = it_i->second.begin(); it_j != it_i->second.end(); ++it_j) {
            int v_blocked = it_i->first;
            DirectionalGraph temp_graph = *this;
            temp_graph.mergeGraph(original_graph.buildSubGraph(v_blocked));
            for (list<tuple<int, int, bool>>::iterator it_list = temp_graph.m[v_blocked].begin(); it_list != temp_graph.m[v_blocked].end(); ++it_list)
                if (get<0>(*it_list) == get<0>(*it_j)) {
                    get<2>(*it_list) = false;
                    break;
                }
            int max_case = 0;
            for (int v : max_vertex) {
                unordered_map<int, int> dist_temp = dist;
                dist_temp[v] = 0;
                for (int u : topological_sort)
                    if (dist_temp[u] != -1)
                        for (list<tuple<int, int, bool>>::iterator it_k = temp_graph.m[u].begin(); it_k != temp_graph.m[u].end(); ++it_k)
                            if (get<2>(*it_k) && dist_temp[get<0>(*it_k)] < dist_temp[u] + 1) 
                                dist_temp[get<0>(*it_k)] = dist_temp[u] + 1;
                for (pair<int, int> dist_i : dist_temp)
                    if (max_case < dist_i.second)
                        max_case = dist_i.second;
            }
            if (max_case < min_possible) 
                min_possible = max_case;
        }
    }
    cout << min_possible << endl;
}

void DirectionalGraph::topologicalSortUtil(int v, unordered_map<int, bool>& visited) {
    visited[v] = true;
    if (m.find(v) != m.end())
        for (list<tuple<int, int, bool>>::iterator it = m[v].begin(); it != m[v].end(); ++it)
            if (!visited[get<0>(*it)])
                topologicalSortUtil(get<0>(*it), visited);
    
    topological_sort.push_front(v);
}

void DirectionalGraph::topologicalSort() {
    unordered_map<int, bool> visited;
    for (auto v : v_set)
        visited[v.first] = false;
    
    for (dir_graph_structure::iterator it = m.begin(); it != m.end(); ++it)
        if (!visited[it->first])
            topologicalSortUtil(it->first, visited);
}

int main() {
    DirectionalGraph graph;
    int m, n;
    cin >> m >> n;
    for (int i = 0; i < n; ++i) {
        int v, u;
        cin >> v >> u;
        graph.addEdge(v, u, 1);
    }
    graph.weightGraph();
    // graph.printGraph();
    DirectionalGraph max_graph = graph.buildMaxGraph();
    max_graph.topologicalSort();
    // max_graph.printGraph();
    max_graph.longestPath(graph);
    return 0;
}