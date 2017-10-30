/*
	Author : Victor Armegioiu
	UVa 10938 : Flea circus

	LCA wasn't actually needed, test cases are too weak. Use dfs to find the path
	between any two nodes given in the queries in linear time per query.
*/

#include <bits/stdc++.h>
using namespace std;

int n;
vector< vector<int> > g;
int path[5005], path_len;

bool dfs(int u, int target, int par=-1)
{
	path[path_len++] = u;
	if (u == target) return true;

	for (int v : g[u])
	{
		if (v == par) continue;
		if (dfs(v, target, u)) return true;
	}

	path_len--;
	return false;
}

int main()
{
	ios_base::sync_with_stdio(false);
	while (cin >> n, n)
	{
		g.assign(n, vector<int> ());
		memset(path, 0, sizeof path);

		for (int i = 0; i < n - 1; i++)
		{
			int u, v;
			cin >> u >> v;
			u--, v--;

			g[u].push_back(v);
			g[v].push_back(u);
		}

		int l;
		cin >> l;

		for (int i = 0; i < l; i++)
		{
			int s, e;
			cin >> s >> e;

			s--, e--;
			path_len = 0;

			dfs(s, e);

			if (path_len & 1) cout << "The fleas meet at " << path[path_len / 2]  + 1 << ".\n";
			else 
			{
				int a = path[path_len / 2 - 1] + 1;
				int b = path[path_len / 2] + 1;

				if (a > b) swap(a, b);

				cout << "The fleas jump forever between " << a << " and " << b << ".\n";
			}
		}

	}

	return 0;
}