#include <bits/stdc++.h>
using namespace std;

vector< vector<int> > g;
vector<int> learning_value;
vector<bool> visited;

int n, m;
pair<int, int> ans;

void dfs(int u)
{
	visited[u] = true;
	int max_value(-1), node(-1);

	for (int &v : g[u])
	{
		if (!visited[v])
		{
			if (learning_value[v] > max_value)
			{
				max_value = learning_value[v];
				node = v;
			}
		}
	}

	if (node != -1) 
	{
		ans.first += max_value;
		ans.second = node;
		dfs(node);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	int t, test(1);
	cin >> t;

	while (t--)
	{
		cin >> n >> m;

		g.assign(n, vector<int>());
		learning_value.assign(n, 0);
		visited.assign(n, false);
		ans = {0, 0};

		for (int i = 0; i < n; i++)
		{
			cin >> learning_value[i];
		}

		for (int i = 0; i < m; i++)
		{
			int u, v;
			cin >> u >> v;
			g[u].push_back(v);
		}

		dfs(0);
		cout << "Case " << test++ << ": " 
		<< ans.first << " " << ans.second << endl;
	}
	return 0;
}