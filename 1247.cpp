#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void print_path(int i, int j, const vector<vector<int>> &parents)
{
	if (i != j) print_path(i, parents[i][j], parents);
	cout << char(j + 'A') << " ";
}

int main()
{
	ios_base::sync_with_stdio(false);
	vector< vector<pii> > g;
	vector< vector<int> > parents;

	int s, p;
	cin >> s >> p;

	g.assign(26, vector<pii> (26, {1e9, 1e9}));
	parents.assign(26, vector<int> (26));

	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			 parents[i][j] = i;

	for (int i = 0; i < p; i++)
	{
		char e1, e2;
		int w;
		cin >> e1 >> e2 >> w;

		int u = int(e1 - 'A');
		int v = int(e2 - 'A');

		g[u][v].first = w;
		g[u][v].second = 1;

		g[u][u].first = g[u][u].second = 0;
		g[v][v].first = g[v][v].second = 0;
	}

	for (int k = 0; k < s; k++)
		for (int i = 0; i < s; i++)
			for (int j = 0; j < s; j++)
				if (g[i][k].first + g[k][j].first <= g[i][j].first)
				{
					if (g[i][k].first + g[k][j].first == g[i][j].first &&
						g[i][k].second + g[k][j].second < g[i][j].second)
					{
						g[i][j].second = g[i][k].second + g[k][j].second;
						parents[i][j] = parents[k][j];
					}

					else if (g[i][k].first + g[k][j].first < g[i][j].first)
					{
						g[i][j].first = g[i][k].first + g[k][j].first;
						g[i][j].second = g[i][k].second + g[k][j].second;

						parents[i][j] = parents[k][j];
					}

				}

	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		char e1, e2;
		int w;
		cin >> e1 >> e2;

		int u = int(e1 - 'A');
		int v = int(e2 - 'A');

		print_path(u, v, parents);
		cout << endl;
	}

	return 0;
}