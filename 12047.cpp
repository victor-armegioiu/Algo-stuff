/*
	Author : Victor Armegioiu
	UVa 12047 : Highest Paid Toll
	
	Extracting the heaviest edge from each directed path between s - t
	requires 2 preprocessing stages. 

	Namely, first run Dijkstra on the
	directed graph in the input and construct the distances from 's' to
	every other node in the graph. The second stage involves running Dijkstra
	on the transposed graph from 't' and storing the distances.

	The information we acquired is used when we're looking for the heaviest edge
	that satisfies the expression : distance_from_(s)_to(v) + weight(u, v) +
									distance_from(v)_to_(t) <= p [maximum cost path].

*/

#include <bits/stdc++.h>
#define SOURCE 0
#define DEST 1

using namespace std;
using pii = pair<int, int>;

vector< vector<pii> > gr, rev_gr;
vector< vector<int> > dist;

int n, m, s, t, p;
int start;

inline void dijkstra(int src, vector< vector<pii> > &g)
{
	priority_queue<pii, vector<pii>, greater<pii> > pq;

	pq.push(pii(0, src));
	dist[start][src] = 0;

	while (!pq.empty())
	{
		pii curr = pq.top();
		pq.pop();

		int u = curr.second;
		int d = curr.first;

		if (d > dist[start][u]) continue;

		for (auto &edge : g[u])
		{
			int v = edge.second;
			int c = edge.first;

			if (dist[start][u] + c < dist[start][v])
			{
				dist[start][v] = dist[start][u] + c;
				pq.push(pii(dist[start][v], v));
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	int tc;
	cin >> tc;

	while (tc--)
	{
		cin >> n >> m >> s >> t >> p;
		s--, t--;

		gr.assign(n, vector<pii> ());
		rev_gr.assign(n, vector<pii> ());
		dist.assign(2, vector<int> (n, 1e9));

		for (int i = 0; i < m; i++)
		{
			int u, v, c;
			cin >> u >> v >> c;
			u--, v--;

			gr[u].push_back(pii(c, v));
			rev_gr[v].push_back(pii(c, u));
		}

		int ans(-1);

		start = 0;
		dijkstra(s, gr);

		start = 1;
		dijkstra(t, rev_gr);

		for (int u = 0; u < n; u++)
		{
			for (auto &edge : gr[u])
			{
				int v = edge.second;
				int toll = edge.first;

				if (dist[SOURCE][u] + toll + dist[DEST][v] <= p) ans = max(ans, toll);
			}
		}

		cout << ans << endl;
	}

	return 0;
}