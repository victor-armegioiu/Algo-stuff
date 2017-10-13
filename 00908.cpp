/*
	Author : Victor Armegioiu
	UVa 908 : Re-connecting Computer Sites 

	Just a basic MST problem; used my favourite version of Kruskal's algorithm,
	based on the union-find algorithm with path compression and union by rank.

	Combining those two we get an amortized time per operation of O(alpha(n)) 
	[alpha(n) is the inverse Ackerman function, converges extremely fast for
	any value of n, having the limit < 5, so it's esentially a constant time operation].
*/

#include <bits/stdc++.h>
using namespace std;

int n, k, m;
vector<int> parents, ranks;

struct Edge
{
	int u, v, cost;
	Edge(int _u, int _v, int _cost) : u(_u), v(_v), cost(_cost) {}

	inline bool operator<(const Edge & other)
	{
		return cost < other.cost;
	}
};

vector<Edge> relevant_edges;

inline void make_set()
{
	parents.resize(n);
	ranks.assign(n, 0);

	for (int i = 0; i < n; i++)
	{
		parents[i] = i;
	}
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

int main()
{
	ios_base::sync_with_stdio(false);
	bool first_case(true);

	while (cin >> n)
	{

		relevant_edges.clear();
		make_set();

		int original_cost(0);
		int final_cost(0);

		for (int i = 0; i < n - 1; i++)
		{
			int u, v, c;
			cin >> u >> v >> c;
			u--, v--;

			original_cost += c;
		}

		cin >> k;
		for (int i = 0; i < k; i++)
		{
			int u, v, c;
			cin >> u >> v >> c;
			u--, v--;

			relevant_edges.push_back(Edge(u, v, c));
		}

		cin >> m;
		for (int i = 0; i < m; i++)
		{
			int u, v, c;
			cin >> u >> v >> c;
			u--, v--;

			relevant_edges.push_back(Edge(u, v, c));
		}

		sort(relevant_edges.begin(), relevant_edges.end());

		for (auto &edge : relevant_edges)
		{
			int u = edge.u;
			int v = edge.v;
			int c = edge.cost;

			if (unite_sets(u, v))
			{
				final_cost += c;
			}
		}

		if (first_case)
		{
			cout << original_cost << endl << final_cost << endl;
			first_case = false;
		}

		else
			cout << endl << original_cost << endl << final_cost << endl;
	}

	return 0;
}