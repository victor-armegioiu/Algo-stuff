/*
	Author : Victor Armegioiu
	UVa 10505 : Montesco vs Capuleto

	The problem actually boils down to noticing that
	the given constraints will determine a forest of bipartite
	graphs (in the favourable cases).

	By taking into consideration this aspect, we need to 
	find the maximum independent set; which in turn is reduced to
	finding the largest side in each bipartite component by using
	a 2-coloring.
*/

#include <bits/stdc++.h>
using namespace std;

vector< vector<int> > g;
vector<bool> visited;
vector<int> colours;

int white, black;
int n;

bool dfs(int u, int colour=0)
{
	visited[u] = true;
	colours[u] = colour;

	black += (colour == 1);
	white += (colour == 0);

	bool is_bipartite = true;

	for (int &v : g[u])
	{
		if  (!visited[v])
			is_bipartite &= dfs(v, 1 - colour);

		else if (colours[v] == colours[u])
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
		cin >> n;
		g.assign(n, vector<int> ());
		visited.assign(n, false);
		colours.assign(n, -1);

		for (int i = 0; i < n; i++)
		{
			int enemies;
			cin >> enemies;

			for (int j = 0; j < enemies; j++)
			{
				int enemy;
				cin >> enemy;

				--enemy;
				if (enemy >= n)
					continue;

				g[i].push_back(enemy);
				g[enemy].push_back(i);
			}
		}

		int ans(0);
		
		for (int i = 0; i < n; i++)
		{	
			bool is_bipartite(true);

			white = 0;
			black = 0;

			if (!visited[i])
				is_bipartite &= dfs(i);

			if (is_bipartite)
				ans += max(white, black);
		}

		cout << ans << endl;
	}

	return 0;
}