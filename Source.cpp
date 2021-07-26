#define _CRT_SECURE_NO_WARNINGS_
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <string.h>
#include <map>
#include <set>

using namespace std;

int n, m, a, b, c;


struct Edge {
	int start, finish, capacity, flow;

};

vector<Edge> edges;
vector<vector<int> > gr;
int visited[110];

void addEdgeLocal(int from, int to, int cap, int flow) {
	edges.push_back(Edge{ from, to, cap, flow });
	gr[from].push_back(edges.size() - 1);
}

void addEdge(int from, int to, int cap) {
	addEdgeLocal(from, to, cap, 0);
	addEdgeLocal(to, from, 0, 0);
}

void pushFlow(int e, int f) {
	edges[e].flow += f;
	edges[e ^ 1].flow -= f;
}

bool isSaturated(int e) {
	return edges[e].flow == edges[e].capacity;
}

int getResidualCapacity(int e) {
	return edges[e].capacity - edges[e].flow;
}

// перебор ребер

/*for (int e : gr[v]) {
	int u = edges[e].finish;
	....
	pushFlow(e, 4);
}*/

int dfs(int u, int Cmin) {        // Cmin Ч пропускна€ способность в текущем подпотоке
	if (u = n)
		return Cmin;
	visited[u] = true;
	for (auto& v : gr[u]) {
		auto uv = edges[v];
		if (!visited[v] && uv.flow < uv.capacity) {
			int delta = dfs(uv.finish, min(Cmin, uv.capacity - uv.flow));
			if (delta > 0) {
				pushFlow(v, delta);
				return delta;
			}
		}
	}
	return 0;
}

int main() {
	cin >> n;
	gr.resize(n + 2);
	cin >> m;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> c;
		addEdge(a, b, c);
	}
	dfs(0, 100000);
	int res = 0;
	for (auto& k : gr[1]) {
		res += edges[k].capacity;
	}
	cout << res;
	return 0;
}