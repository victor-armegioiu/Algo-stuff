/*
	Author : Armegioiu Victor
	UVa 796 : Critical Links

	Finding critical links (bridges) within a network; 
	used a set to mantain proper ordering, as required in the given constraint.
*/

#include <bits/stdc++.h>
using namespace std;

int n, m;
vector< vector<int> > g;
vector<bool> visited;
vector<int> parents, dfs_low, dfs_num;
set< pair<int, int> > bridges;

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
			{
				auto bridge = make_pair(min(u, v), max(u, v));
				bridges.insert(bridge);
			}

			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}

		else if (parents[u] != v)
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	while (cin >> n)
	{
		g.assign(n, vector<int> ());
		visited.assign(n, false);
		parents.resize(n);
		dfs_low.resize(n);
		dfs_num.resize(n);
		bridges.clear();

		string line;
		cin.ignore();

		for (int i = 0; i < n; i++)
		{
			getline(cin, line);
			stringstream ss(line);

			int u, v, neighbour_count;
			char parenthesis;

			ss >> u >> parenthesis >> neighbour_count >> parenthesis;
			for (int j = 0; j < neighbour_count; j++)
			{
				ss >> v;
				g[u].push_back(v);
			}
		}

		for (int i = 0; i < n; i++)
			if (!visited[i])
				dfs(i);

		cout << bridges.size() << " critical links\n";
		for (auto &bridge : bridges)
			cout << bridge.first << " - " << bridge.second << endl;
		cout << endl;
	}

	return 0;
}