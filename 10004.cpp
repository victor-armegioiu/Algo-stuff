#include <bits/stdc++.h>
using namespace std;

int n, l;
vector< vector<int> > g;
vector<bool> visited;
vector<int> colours;

bool dfs(int u, int colour=0)
{
	visited[u] = true;
	colours[u] = colour;

	bool bicolourable = true;

	for (int &v : g[u])
	{
		if (!visited[v])
			bicolourable &= dfs(v, 1 - colour);

		else if (colours[v] == colours[u]) bicolourable = false;
	}

	return bicolourable;
}

int main()
{
	ios_base::sync_with_stdio(false);
	while (cin >> n, n)
	{
		cin >> l;
		g.assign(n, vector<int> ());
		visited.assign(n, false);
		colours.assign(n, -1);

		for (int i = 0; i < l; i++)
		{
			int u, v;
			cin >> u >> v;

			g[u].push_back(v);
			g[v].push_back(u);
		}

		cout << (dfs(0) ? "BICOLORABLE.\n" : "NOT BICOLORABLE.\n");
	}
	return 0;
}