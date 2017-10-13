/*
	Author : Victor Armegioiu
	UVa 610 : Street Directions

	Tarjan's algorithm for finding bridges.
*/

#include <bits/stdc++.h>
using namespace std;

vector< vector<int> > g;
vector< vector<bool> > roads;
vector<bool> visited;
vector<int> parents, dfs_low, dfs_num;

int n, m;

void dfs(int u)
{
	static int time(0);
	visited[u] = true;
	dfs_low[u] = dfs_num[u] = ++time;

	for (int &v : g[u])
	{
		if (!visited[v])
		{
			parents[v] = u;
			dfs(v);

			if (dfs_low[v] > dfs_num[u])
				roads[u][v] = roads[v][u] = true;

			else if (!roads[v][u]) roads[u][v] = true;
	
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}

		else if (v != parents[u])
		{
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
			if (!roads[v][u]) roads[u][v] = true;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	int t(1);

	while (cin >> n >> m, (n | m))
	{
		g.assign(n, vector<int> ());
		roads.assign(n, vector<bool> (n, false));
		visited.assign(n, false);
		dfs_low.assign(n, -1);
		dfs_num.assign(n, -1);
		parents.assign(n, -1);

		for (int i = 0; i < m; i++)
		{
			int u, v;
			cin >> u >> v;
			u--, v--;
			g[u].push_back(v);
			g[v].push_back(u);

		}

		dfs(0);
		cout << t++ << "\n\n";

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (roads[i][j])
					cout << i + 1 << " " << j + 1 << endl;

		cout << "#\n";
	}

	return 0;
}