#include <bits/stdc++.h>
using namespace std;
vector< vector<int> > g;
stack<int> toposort;
vector<bool> visited;
int n, m;

void dfs(int u)
{
	visited[u] = true;
	for (int &v : g[u])
		if (!visited[v])
			dfs(v);

	toposort.push(u);
}

int main()
{
	ios_base::sync_with_stdio(false);
	while (cin >> n >> m, (n | m))
	{
		g.assign(n, vector<int> ());
		visited.assign(n, false);

		for (int i = 0; i < m; i++)
		{
			int u, v;
			cin >> u >> v;
			u--, v--;

			g[u].push_back(v);
		}

		for (int i = 0; i < n; i++)
		{
			if (!visited[i])
				dfs(i);
		}

		while (!toposort.empty())
		{
			cout << ++toposort.top() << " ";
			toposort.pop();
		}

		cout << endl;
	}

	return 0;
}