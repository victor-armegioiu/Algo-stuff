/*
	Author : Victor Armegioiu
	UVa 10600 : ACM Contest and Blackout

	O(V * E). Find the MST using Kruskal, then iterate over the set
	of edges that comprise mst and invalidate them 1 by 1 and reconstruct
	another MST that doesn't contain the respective unselected edge.

	This could be done a lot faster by using heavy light decomposition or
	LCA in order to find the heaviest edge in the cycle formed by adding a 
	new edge to the initial MST.
*/

#include <bits/stdc++.h>
using namespace std;

int n, m;

struct Edge
{
	int u, v, w;

	Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

	inline bool operator<(const Edge & other)
	{
		return w < other.w;
	}

	inline bool operator==(const Edge & other)
	{
		return u == other.u && v == other.v && w == other.w;
	}
};

vector<Edge> edges, mst;
vector<int> parents;
vector<int> ranks;

inline void make_set()
{
	ranks.assign(n, 0);
	parents.assign(n, 0);

	for (int i = 0; i < n; i++) 
		parents[i] = i;
}

int find_set(int u)
{
	if (u != parents[u])
		parents[u] = find_set(parents[u]);

	return parents[u];
}

inline bool unite_sets(int u, int v)
{
	int u_root = find_set(u);
	int v_root = find_set(v);

	if (u_root == v_root)
		return false;

	if (ranks[u_root] > ranks[v_root])
		parents[v_root] = u_root;

	else if (ranks[u_root] < ranks[v_root])
		parents[u_root] = v_root;

	else
	{
		parents[u_root] = v_root;
		ranks[v_root]++;
	}

	return true;
}

inline int second_best(int best_cost)
{
	int second_mst(1e9);

	for (auto mst_edge : mst)
	{
		make_set();
		int curr_mst = 0;
		int taken = 0;

		for (auto edge : edges)
		{
			if (edge == mst_edge) continue;

			int u = edge.u;
			int v = edge.v;
			int w = edge.w;

			if (unite_sets(u, v))
			{
				curr_mst += w;
				taken++;
			}

			if (taken == n - 1)
			{
				second_mst = min(second_mst, curr_mst);
				break;
			}
		}
	}

	return second_mst;
}

int main()
{
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;

	while (t--)
	{
		cin >> n >> m;
		make_set();
		edges.clear();
		mst.clear();

		for (int i = 0; i < m; i++)
		{
			int u, v, w;
			cin >> u >> v >> w;
			u--, v--;

			edges.push_back(Edge(u, v, w));
		}

		sort(edges.begin(), edges.end());
		int mst_cost(0);

		for (auto &edge : edges)
		{
			int u = edge.u;
			int v = edge.v;
			int w = edge.w;

			if (unite_sets(u, v))
			{
				mst_cost += w;
				mst.push_back(edge);
			}
		}

		cout << mst_cost << " " << second_best(mst_cost) << endl;
	}


	return 0;
}