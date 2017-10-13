#include <bits/stdc++.h>
#define UNVISITED 0
#define EXPLORED 1
#define VISITED 2

using namespace std;
int n, m;

vector< vector<int> > g;
vector<int> visited;
vector<int> dfs_parent;
stack<int> toposort;

bool dfs(int u)
{
	bool sortable = true;
	visited[u] = EXPLORED;

	for (int &v : g[u])
	{
		if (visited[v] == EXPLORED)
			sortable = false;

		else if (visited[v] == UNVISITED)
			sortable &= dfs(v);
	}

	visited[u] = VISITED;
	toposort.push(u);

	return sortable;
}

int main()
{
	ios_base::sync_with_stdio(false);
	while (cin >> n >> m, (n | m))
	{
		g.assign(n, vector<int> ());
		visited.assign(n, UNVISITED);

		for (int i = 0; i < m; i++)
		{
			int u, v;
			cin >> u >> v;
			u--, v--;

			g[u].push_back(v);
		}

		bool sortable(true);
		for (int i = 0; i < n; i++)
		{
			if (!visited[i])
				sortable &= dfs(i);

			if (!sortable)
				break;
		}

		if (!sortable) 
		{
			cout << "IMPOSSIBLE\n"; 
			while (!toposort.empty()) toposort.pop(); 
			continue; 
		}

		while (!toposort.empty())
		{
			cout << ++toposort.top() << endl;
			toposort.pop();
		}
	}

	return 0;
}