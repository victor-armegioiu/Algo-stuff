/*
	Author : Victor Armegioiu
	UVa 11080 : Placing Guards

	Very similar to uva-10505. Break the graph into individual connected components,
	and test for bipartiteness; each component has to be bipartite because any two guards
	assigned to the same street will inevitably fight so the components have to be partitioned
	into disjoint and independent sets.

	Since we need the minimum number of guards for each component in the forest,
	we compute the final answer as max(1, min(white, black)) 
	[there has to be at least 1 guard per component].
*/

#include <bits/stdc++.h>
using namespace std;

vector< vector<int> > g;
vector<bool> visited;
vector<int> colours;

int n;
int white, black;

bool dfs(int u, int colour=0)
{
	visited[u] = true;
	colours[u] = colour;

	white += (colour == 0);
	black += (colour == 1);

	bool is_bipartite = true;

	for (int &v : g[u])
	{
		if (!visited[v])
			is_bipartite &= dfs(v, 1 - colour);

		else if (colours[u] == colours[v])
			is_bipartite = false;
	}

	return is_bipartite;	
}

int main()
{
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;

	while (t--)
	{
		int e;
		cin >> n >> e;

		g.assign(n, vector<int> ());
		visited.assign(n, false);
		colours.assign(n, -1);

		for (int i = 0; i < e; i++)
		{
			int u, v;
			cin >> u >> v;

			g[u].push_back(v);
			g[v].push_back(u);
		}

		bool is_bipartite(true);
		int ans(0);

		for (int i = 0; i < n && is_bipartite; i++)
		{
			if (!visited[i])
			{
				white = 0;
				black = 0;

				is_bipartite = dfs(i);
				ans += max(1, min(white, black));
			}
		}

		if (is_bipartite) cout << ans << endl;
		else cout << -1 << endl;
	}
	return 0;
}