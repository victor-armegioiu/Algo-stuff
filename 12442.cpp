#include <bits/stdc++.h>
using namespace std;

vector<int> g;
vector<int> visited;
vector<int> path_len;
int n;

int dfs(int u)
{
	visited[u] = true;
	int v = g[u];
	int length(0);

	if (!visited[v])
		length = 1 + dfs(v);

	visited[u] = false;
	return path_len[u] = length;
}

int main()
{
	ios_base::sync_with_stdio(false);
	int t, test(1);
	cin >> t;

	while (t--)
	{
		cin >> n;
		g.assign(n, 0);
		visited.assign(n, false);
		path_len.assign(n, -1);

		for (int i = 0; i < n; i++)
		{
			int u, v;
			cin >> u >> v;
			g[u - 1] = v - 1;
		}

		int max_len = -1;
		int pos = 0;

		for (int i = 0; i < n; i++)
		{
			if (path_len[i] == -1)
			{
				dfs(i);
				if (path_len[i] > max_len)
				{
					max_len = path_len[i];
					pos = i;
				}
			}
		}

		cout << "Case " << test++ << ": " << ++pos << endl;	
	}

	return 0;
}