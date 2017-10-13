/*
	Author : Victor Armegioiu
	UVa 318 : Domino Effect

	Used Dijkstra's algorithm to get the actual falling times for each
	of the key dominoes. The sole trick to this problem relies on noticing
	that in order for the last domino to fall in the middle of some arbitrary
	edge (u, v) the following have to hold:

	- without loss of generality let d[u] > d[v]
	- if d[u] + w(u, v) > d[v] then the stream coming towards 'v' would flow
	  through (u, v) simultaneously with the stream coming towards 'u'
	- since uniformity is implied from the text of the problem, the 
	  last domino on this edge would fall in d[u] + ((d[v] - d[u] + w(u, v)) / 2.0) second
*/

#include <bits/stdc++.h>
using namespace std;
using cell = pair<int, int>;

vector< vector< cell > > g;
vector<bool> visisted;
vector<int> dist;

int n, m;
const int INF = 1e9;

inline void dijkstra()
{
	priority_queue<cell, vector<cell>, greater<cell>> pq;
	dist[0] = 0;
	pq.push(cell(0, 0));

	while (!pq.empty())
	{
		cell node = pq.top();
		int u = node.second;
		int d = node.first;

		pq.pop();

		if (d > dist[u])
			continue;

		for (auto &v : g[u])
		{
			if (dist[u] + v.second < dist[v.first])
			{
				dist[v.first] = dist[u] + v.second;
				pq.push(cell(dist[v.first], v.first));
			}
		}	
	}
}

void last_domino(double &ans, int &l, int &r)
{
	for (int i = 0; i < n; i++)
		if (dist[i] > ans && dist[i] != INF)
		{
			ans = (double)dist[i];
			l = i;
			r = -1;
		}

	for (int u = 0; u < n; u++)
	{	for (int j = 0; j < (int) g[u].size(); j++)
		{
			int v = g[u][j].first;
			int w = g[u][j].second;

			int x = dist[u]; 
			int y = dist[v]; 

			if (x == INF || y == INF) continue;
			if (x > y) swap(x, y);

			if (x + w > y)
			{
				double end_time = x + ((y - x + w) / 2.0);
				if (end_time > ans)
				{
					ans = end_time;
					l = min(u, v);
					r = max(u, v);
				}
			}

		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	int system_no(1);

	cout << fixed << setprecision(1);

	while (cin >> n >> m && (n || m))
	{
		g.assign(n, vector<cell> ());
		visisted.assign(n, false);
		dist.assign(n, INF);

		for (int i = 0; i < m; i++)
		{
			int u, v, w;
			cin >> u >> v >> w;

			u--, v--;
			g[u].push_back(make_pair(v, w));
			g[v].push_back(make_pair(u, w));
		}

		dijkstra();

		double ans(0.0);
		int l(0), r(-1);

		last_domino(ans, l, r);

		cout << "System #" << system_no++ << endl;
		cout << "The last domino falls after ";
		if (r == -1)
			cout << ans << " seconds, " 
			<< "at key domino " << ++l << ".\n\n";

		else
			cout << ans << " seconds, " 
			<< "between key dominoes " << ++l << " and " << ++r << ".\n\n";
	}		

	return 0;
}