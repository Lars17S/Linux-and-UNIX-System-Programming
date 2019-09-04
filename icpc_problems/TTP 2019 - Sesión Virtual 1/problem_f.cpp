#include <iostream>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <string>
#include <list>
using namespace std;

template <typename T>
class Graph {
	unordered_map<T, list<pair<T, short>>> m;
public:
	void addEdge(T u, T v, short dist) {
		m[u].push_back(make_pair(v, dist));
		m[v].push_back(make_pair(u, dist));
	}

	void clearGraph() {
		m.clear();
	}

	T DijkstraSSSD(T src, T final_dest) {
		unordered_map<T, short> dist;
		for (auto j : m)
			dist[j.first] = 0;

		dist[src] = SHRT_MAX;
		set<pair<short, T>> s;
		short min1, min2, edge;
		T dest;
		s.insert(make_pair(dist[src], src));
		while (!s.empty()) {
			auto p = *s.rbegin();
			T node = p.second;
			short distLocal = p.first;
			s.erase(--s.end());
			for (auto childPair : m[node]) {
				edge = childPair.second;
				dest = childPair.first;
				min1 = min(dist[node], edge);
				min2 = min(dist[dest], edge);
				if (min1 != min2) {
					auto f = s.find(make_pair(dist[dest], dest));
					if (f != s.end())
						s.erase(f);

					dist[dest] = max(min1, min2);
					s.insert(make_pair(dist[dest], dest));
				}
			}
		}
		return to_string(dist[final_dest]);
	}
};

int main()
{
	Graph<string> graph;
	short n, r, w_limit, j = 1;
	string name1, name2;
	string output = "";
	cin >> n >> r;
	while (n != 0 && r != 0) {
		for (short i = 0; i < r; ++i) {
			cin >> name1 >> name2 >> w_limit;
			graph.addEdge(name1, name2, w_limit);
		}
		cin >> name1 >> name2;
		graph.DijkstraSSSD(name1, name2);
		output += "Scenario #" + to_string(j) + '\n' + graph.DijkstraSSSD(name1, name2) + " tons" + '\n' + '\n';
		graph.clearGraph();
		++j;
		cin >> n >> r;
	}

	cout << output;

	return 0;
}