#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <stack>
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

    int root; //QUE PASA SI EL ROOT SON DOS NODOS?
    int weight = 0;

    DirectionalGraph topologicalSort();
    void topologicalSortUtil(int v, unordered_map<int, bool>& visited, DirectionalGraph& graph_sort);
    DirectionalGraph BuildMaxGraph();
    DirectionalGraph BuildMaxGraphUtil(int v, unordered_map<int, bool>& visited);
    DirectionalGraph buildSubGraph(int v);
    int weightGraphUtil(int v, unordered_map<int, bool>& visited);
    void addEdge(int v, int u, int weight);
    void setRoot(int root);
    void mergeGraph(DirectionalGraph sub_graph);
    void mergeGraphMax(DirectionalGraph max_graph);
    void longestPath(DirectionalGraph& original_graph);
    void longestPathUtil();
    
    void makeV_set();
    void printGraph(); 
    void clearGraph();
    void weightGraph();
};

void DirectionalGraph::setRoot(int root) {
    this->root = root;
}

void DirectionalGraph::makeV_set() {
    for (auto m_it : m) {
        v_set[m_it.first] = 0;
        for (auto l_it : m_it.second)
            v_set[get<0>(l_it)] = 0;
    }
}

void DirectionalGraph::addEdge(int v, int u, int weight) {
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

void DirectionalGraph::mergeGraphMax(DirectionalGraph max_graph) {
    weight = max_graph.weight;
    // Add each (u, v) edge from sub_graph to graph
    if (!max_graph.m.empty())
        for (dir_graph_structure::iterator it = max_graph.m.begin(); it != max_graph.m.end(); ++it)
            m[it->first] = it->second;
    else cout << "MAX_SUB_GRAPH EMPTY" << endl;
}

void DirectionalGraph::printGraph() {
    cout << "VERTEX_SET: ";
    for (auto v : v_set) 
        cout << "v: " << v.first << " max weight: " << v.second << " | ";
    cout << endl;
    cout << "TOPOLOGICAL_SORT: ";
    if (topological_sort.empty())
        cout << "EMPTY" << endl; 
    for (int v : topological_sort) 
        cout << v << " ";
    cout << endl;
    for (dir_graph_structure::iterator it = m.begin(); it != m.end(); ++it)
        for (tuple<int, int, bool> u : it->second)
            cout << it->first << " -> (" << get<0>(u) << ", " << get<1>(u) << ")" << endl;
}

int DirectionalGraph::weightGraphUtil(int v, unordered_map<int, bool>& visited) {
    int weight = 0;
    if (m.find(v) != m.end()) {
        for (list<tuple<int, int, bool>>::iterator it = m[v].begin(); it != m[v].end(); ++it) {
            tuple<int, int, bool> u = *it;
            get<1>(*it) = (!visited[get<0>(u)]) ? weightGraphUtil(get<0>(u), visited) + 1 : v_set[get<0>(u)] + 1;
            if (weight < get<1>(*it))
                weight = get<1>(*it);
        }
    }
    visited[v] = true;
    v_set[v] = weight;
    return weight;
}

void DirectionalGraph::weightGraph() {
    unordered_map<int, bool> visited;
    for (auto v : topological_sort) 
        visited[v] = false;
    
    for (list<int>::iterator it = topological_sort.begin(); it != topological_sort.end(); ++it) { //PUEDE TIRAR ERROR
        if (!visited[*it])
            int k = weightGraphUtil(*it, visited); // CAMBIAR
        visited[*it] = true;
    }
    printGraph();
}


DirectionalGraph DirectionalGraph::BuildMaxGraphUtil(int v, unordered_map<int, bool>& visited) {
    DirectionalGraph max_graph;
    max_graph.setRoot(v);
    if (!m[v].empty()) {
        for (list<tuple<int, int, bool>>::iterator it = m[v].begin(); it != m[v].end(); ++it) {
            tuple<int, int, bool> u = *it;
            DirectionalGraph sub_graph;
            // Recursive call
            if (!visited[get<0>(u)]) {
                sub_graph = BuildMaxGraphUtil(get<0>(u), visited);
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
            else if (max_graph.weight == sub_graph.weight) {
                max_graph.mergeGraph(sub_graph);                }
            cout << "PRINT MAX_GRAPH: " << endl;
            max_graph.printGraph();
        }
        max_graph.weight = max_graph.weight + 1;
    }
    else cout << "Subgraph is a trivial 1-node graph: " << max_graph.root << endl;  
    visited[v] = true;
    return max_graph;
}

DirectionalGraph DirectionalGraph::BuildMaxGraph() {
    unordered_map<int, bool> visited;
    vector<int> max_vertex;
    for (int v : topological_sort) 
        visited[v] = false;
    
    int max = -1;
    for (int v : topological_sort) {
        if (max < v_set[v]) {
            max_vertex.clear();
            max_vertex.push_back(v);
            max = v_set[v];
        } 
        else if (max == v_set[v]) {
            max_vertex.push_back(v);
        }
    }

    DirectionalGraph max_graph;
    DirectionalGraph original_graph = *this;
    for (vector<int>::reverse_iterator it = max_vertex.rbegin(); it != max_vertex.rend(); ++it) {
        DirectionalGraph max_sub_graph = original_graph.BuildMaxGraphUtil(*it, visited);
        cout << "MAX_SUB_GRAPH PRINTED: " << endl;
        max_sub_graph.printGraph();
        max_graph.mergeGraphMax(max_sub_graph);
        visited[*it] = true;
    }
    max_graph.makeV_set();
    cout << "END" << endl;
    max_graph.printGraph();

    //DirectionalGraph max_graph = BuildMaxGraphUtil(s);
    //max_graph.printGraph();
    return max_graph;
}

// Es invocado por el graph original
DirectionalGraph DirectionalGraph::buildSubGraph(int v) {
    DirectionalGraph graph;
    graph.setRoot(v);
    if (!m[v].empty()) {
        for (list<tuple<int, int, bool>>::iterator it = m[v].begin(); it != m[v].end(); ++it) {
            // Recursive call
            DirectionalGraph sub_graph = buildSubGraph(get<0>(*it));
            graph.mergeGraph(sub_graph);
        }    
    }
    else cout << "Subgraph is a trivial 1-node graph: " << graph.root << endl;  
    return graph;
}

void DirectionalGraph::longestPath(DirectionalGraph& original_graph) {
    vector<int> max_vertex;
    // Process all vertices in topological order
    int max = -1;
    for (int v : topological_sort) {
        if (max < v_set[v]) {
            max_vertex.clear();
            max_vertex.push_back(v);
            max = v_set[v];
        } 
        else if (max == v_set[v]) {
            max_vertex.push_back(v);
        }
    }

    // for (auto m_it : m)
    //     for (auto l_it : m_it.second) 
    //         l_it.second = 1;
    // // DEBO LIMPIAR EL PESO DE TODOS
    for (dir_graph_structure::iterator it_i = m.begin(); it_i != m.end(); ++it_i) {
        for (list<tuple<int, int, bool>>::iterator it_j = it_i->second.begin(); it_j != it_i->second.end(); ++it_j)
            get<1>(*it_j) = 1;
    }
    int min_possible = INT16_MAX;
    for (dir_graph_structure::iterator it_i = m.begin(); it_i != m.end(); ++it_i) {
        for (list<tuple<int, int, bool>>::iterator it_j = it_i->second.begin(); it_j != it_i->second.end(); ++it_j) {
            int v_blocked = it_i->first;
            cout << "EDGE BLOCKED: " << it_i->first << ", " << get<0>(*it_j) << endl;
            DirectionalGraph temp_graph = *this;
            temp_graph.mergeGraph(original_graph.buildSubGraph(v_blocked));
            // I NEED TO MERGE AND CONNECT THE NODE WITH THE BLOCKED ONE
            for (list<tuple<int, int, bool>>::iterator it_list = temp_graph.m[v_blocked].begin(); it_list != temp_graph.m[v_blocked].end(); ++it_list) {
                if (get<0>(*it_list) == get<0>(*it_j)) {
                    get<1>(*it_list) = -1;
                    get<2>(*it_list) = false;
                    cout << "U FOUND: " << get<0>(*it_list) << endl;
                    break;
                }
            }
            int max_case = 0;
            for (int v : max_vertex) {
                cout << "MAX_VERTEX: " << v << endl;
                unordered_map<int, int> dist;
                for (int v_i : topological_sort)
                    dist[v_i] = -1;
                dist[v] = 0;
                for (int u : topological_sort) {
                    if (dist[u] != -1) {
                        for (list<tuple<int, int, bool>>::iterator it_k = temp_graph.m[u].begin(); it_k != temp_graph.m[u].end(); ++it_k) {
                            cout << "Edge compared: " << u << " -> " << get<0>(*it_k) << ", status: " << get<2>(*it_k) << endl;
                            if (get<2>(*it_k)) {
                                if (dist[get<0>(*it_k)] < dist[u] + get<1>(*it_k)) {
                                    dist[get<0>(*it_k)] = dist[u] + get<1>(*it_k);
                                    //cout << "dist[u]: " << dist[u] << " | get<1> = " << get<1>(*it_k) << endl;
                                }
                            }
                        }
                    }
                }
                cout << "DISTANCES PRINTED: " << endl;
                for (pair<int, int> dist_i : dist) {
                    if (max_case < dist_i.second)
                        max_case = dist_i.second;
                    cout << dist_i.second << " ";
                }
                cout << endl;
            }
            if (max_case < min_possible) 
                min_possible = max_case;
        }
    }
    cout << "RESULT: " << min_possible << endl;
}

void DirectionalGraph::topologicalSortUtil(int v, unordered_map<int, bool>& visited, DirectionalGraph& graph_sort) {
    visited[v] = true;
    if (m.find(v) != m.end()) {
        for (list<tuple<int, int, bool>>::iterator it = m[v].begin(); it != m[v].end(); ++it) {
            //cout << v << " -> " << (*it).first << endl;
            graph_sort.addEdge(v, get<0>(*it), 0);
            if (!visited[get<0>(*it)]) {
                topologicalSortUtil(get<0>(*it), visited, graph_sort);
            }
        }   
    } 
    
    topological_sort.push_front(v);
}

DirectionalGraph DirectionalGraph::topologicalSort() {
    int n = m.size();
    unordered_map<int, bool> visited;
    DirectionalGraph graph_sort;
    for (auto v : v_set)
        visited[v.first] = false;
    
    for (dir_graph_structure::iterator it = m.begin(); it != m.end(); ++it) {
        if (!visited[it->first])
            topologicalSortUtil(it->first, visited, graph_sort);
    }

    v_set.clear();
    for (int v : topological_sort) {
        v_set[v] = 0;
    }
    cout << endl;

    return graph_sort;
}

int main() {
    DirectionalGraph graph;
    DirectionalGraph graph_sort;
    int m, n;
    cin >> m >> n;
    for (int i = 0; i < n; ++i) {
        int v, u;
        cin >> v >> u;
        graph.addEdge(v, u, 1);
    }
    graph_sort = graph.topologicalSort();
    graph_sort.topological_sort = graph.topological_sort;
    //graph_sort.printGraph();
    graph_sort.weightGraph();
    DirectionalGraph max_graph = graph_sort.BuildMaxGraph();
    DirectionalGraph max_graph_sort = max_graph.topologicalSort();
    max_graph_sort.topological_sort = max_graph.topological_sort;
    max_graph_sort.weightGraph();
    cout << "MAX_GRAPH_SORT: " << endl;
    max_graph_sort.printGraph();
    max_graph_sort.longestPath(graph_sort);
    //DirectionalGraph sub_graph = graph_sort.buildSubGraph(3);
    //sub_graph.printGraph();
    return 0;
}