#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <list>
#include <string>
#include <sstream>
using namespace std;

class Graph {
	map<string, list<pair<string, short>>> m;
public:
	void addEdge(string u, string v, short dist) {
		m[u].push_back(make_pair(v, dist));
		m[v].push_back(make_pair(u, dist));
	}

	void clearGraph() {
		m.clear();
	}

	string DijkstraSSSD(string src, string final_dest) {
		map<string, short> dist;
		map<string, list<pair<string, short>>>::iterator it = m.begin();
		while (it != m.end())
		{
			dist[it->first] = 0;
			it++;
		}

		dist[src] = SHRT_MAX;
		set<pair<short, string>> s;
		short min1, min2, edge;
		string dest;
		s.insert(make_pair(dist[src], src));
		while (!s.empty()) {
			set<pair<short, string>>::reverse_iterator p = s.rbegin();
			string node = p->second;
			short distLocal = p->first;
			s.erase(--s.end());
			list<pair<string, short>>::iterator childPair = m[node].begin();
			while (childPair != m[node].end()) {
				edge = childPair->second;
				dest = childPair->first;
				min1 = min(dist[node], edge);
				min2 = min(dist[dest], edge);
				if (min1 != min2) {
					set<pair<short, string>>::iterator f = s.find(make_pair(dist[dest], dest));
					if (f != s.end())
						s.erase(f);

					dist[dest] = max(min1, min2);
					s.insert(make_pair(dist[dest], dest));
				}
				++childPair;
			}
		}
		ostringstream str1;
		str1 << dist[final_dest];
		return str1.str();
	}
};

int main()
{
	Graph graph;
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
		ostringstream jstr;
		jstr << j;
		output += "Scenario #" + jstr.str() + '\n' + graph.DijkstraSSSD(name1, name2) + " tons" + '\n' + '\n';
		graph.clearGraph();
		++j;
		cin >> n >> r;
	}

	cout << output;

	return 0;
}