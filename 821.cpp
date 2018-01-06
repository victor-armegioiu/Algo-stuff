/*
	Author : Victor Armegioiu
	UVa 821 : Page Hopping

	Just plain old Floyd-Warshall.
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	int test(1);
	string line;

	while (getline(cin, line) && line[0] != '0')
	{
		int u, v, n(0);
		
		vector< vector<int> > g;
		g.assign(100, vector<int> (100, 1e9));
		
		unordered_set<int> unqiue;
		stringstream ss(line);
		while (ss >> u >> v && (u | v))
		{
			n = max(n, max(u, v));
			unqiue.insert(u);
			unqiue.insert(v);

			u--, v--;
			g[u][v] = 1;
			g[u][u] = g[v][v] = 0;
		}

		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					g[i][j] = min(g[i][j], g[i][k] + g[k][j]);

		double sum(0.0);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (g[i][j] != 1e9)
					sum += g[i][j];

		int count = unqiue.size();

		cout << "Case " << test++ << ": average length between pages = " <<
		fixed << setprecision(3) << sum / (count * (count - 1)) << " clicks\n";
		
	}		

	return 0;
}