#include <iostream>
#include <list>
#include <unordered_map>
#include <iterator>
using namespace std;

class Graph {
    unordered_map<string, list<string>> m;
public:
    void addEdge(string u, string v) {
        m[u].push_back(v);
        m[v].push_back(u);
    }

    void printGraph() {
        
        for (unordered_map<string, list<string>>::iterator it_i = m.begin(); it_i != m.end(); ++it_i) {
            cout << "City: " << it_i->first << " connected to: ";
            for (list<string>::iterator it_j = it_i->second.begin(); it_j != it_i->second.end(); ++it_j) {
                cout << *it_j << " ";
            }
            cout << endl;
        }
    }

    bool isReachable(string s, string d) {
        if (s.compare(d) == 0)
            return true;

        // Mark all the vertices as not visited
        unordered_map<string, bool> visited;
        for (unordered_map<string, list<string>>::iterator it = m.begin(); it != m.end(); ++it)
            visited[it->first] = false;

        // Create a queue for BFS
        list<string> queue;

        // Mark the current node as visited and enqueue it
        visited[s] = true;
        queue.push_back(s);

        list<string>::iterator i;
        while (!queue.empty()) {
            // Dequeue a vertex from queue and print it
            s = queue.front();
            queue.pop_front();

            // Get all adjacent vertices of the dequeued vertex s 
            // If a adjacent has not been visited, then mark it visited 
            // and enqueue it 
            for (i = m[s].begin(); i != m[s].end(); ++i) {
                // IF this adjacent node is the destination node
                // return true
                if ((*i).compare(d) == 0)
                    return true;
                
                // Else continue to do BFS
                if (!visited[*i]) {
                    visited[*i] = true;
                    queue.push_back(*i);
                }
            }
        }

        return false;
    }
};

int main() {
    Graph graph;
    short N;
    cin >> N;
    cin.clear(); cin.ignore();
    for (short i = 0; i < N; ++i) {
        string str;
        getline(cin, str);
        //cout << "str: " << str << endl;
        short index = str.find(' ');
        short M = stoi(str.substr(0, index));
        //cout << "M: " << M << endl;
        string* city = new string[M];
        if (M != 1) {
            for (short j = 0; j < M; ++j) {
            city[j] = str.substr(index + 1, str.find(' ', index + 1) - (index + 1));
            //cout << "city " << city[j] << " added" << endl;
            index = str.find(' ', index + 1);
            }
        }
        
        for (short j = 0; j < M - 1; ++j) {
            graph.addEdge(city[j], city[j + 1]);
        }

        delete[] city;
    }

    string s, d;
    cin >> s >> d;
    //graph.printGraph();
    if(graph.isReachable(s, d))
        cout << "posible" << endl;
    else cout << "imposible" << endl;

    return 0;
}