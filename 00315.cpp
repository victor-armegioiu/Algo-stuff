/*
	Author : Victor Armegioiu
	UVa 315 : Network

	Counting articulation points off a connected undirected graph.
	Used Tarjan's algorithm.
*/

#include <bits/stdc++.h>
using namespace std;

int n;
int root_children;
int dfs_root;

vector< vector<int> > g;
vector<int> visited;
vector<int> dfs_low;
vector<int> dfs_num;
vector<int> parents;

set<int> articulation_points;

void dfs(int u)
{
	static int time(0);
	dfs_num[u] = dfs_low[u] = ++time;
	visited[u] = true;

	for (int &v : g[u])
	{
		if (!visited[v])
		{
			parents[v] = u;
			if (u == dfs_root)
				root_children++;

			dfs(v);

			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
			if (u != dfs_root && dfs_low[v] >= dfs_num[u])
				articulation_points.insert(u);

			else if (u == dfs_root && root_children > 1)
				articulation_points.insert(u);
		}

		// If v != parent[u] there is a back edge from u to v
		else if (v != parents[u])
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	while (cin >> n, n)
	{
		cin.ignore();
		string line;

		g.assign(n, vector<int> ());
		visited.assign(n, false);
		dfs_low.assign(n, -1);
		dfs_num.assign(n, -1);
		parents.assign(n, -1);

		while (getline(cin, line), line != "0")
		{	
			if (line == "0")
				break;

			stringstream ss;
			ss.str(line);

			int u, v;
			ss >> u;
			u--;

			while (ss >> v)
			{
				v--;
				g[u].push_back(v);
				g[v].push_back(u);
			}
		}

		articulation_points = {};
		root_children = 0;
		dfs_root = 0;

		dfs(0);
		cout << articulation_points.size() << endl;
	}

	return 0;
}