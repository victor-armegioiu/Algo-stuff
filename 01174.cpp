/*
	Author : Victor Armegioiu
	UVa 1174 : IP-TV

	Kruskal's MST algorithm; DSU; involved a bit of parsing
	to map the edges of the network.
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge
{
	string u, v;
	int c;

	Edge(string _u, string _v, int _c) : u(_u), v(_v), c(_c){}

	inline bool operator<(const Edge & other)
	{
		return c < other.c;
	}
};

map <string, string> parents;
map <string, int> ranks;
vector<Edge> edges;

string find_set(string u)
{
	if (u != parents[u])
		parents[u] = find_set(parents[u]);

	return parents[u];
}

inline bool unite_sets(string u, string v)
{
	string u_root = find_set(u);
	string v_root = find_set(v);

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
	int t, m, n;
	bool first_case(true);

	cin >> t;
	cin.ignore();

	while (t--)
	{
		cin >> m >> n;
		cin.ignore();

		edges.clear();
		parents.clear();
		ranks.clear();

		string line;
		for (int i = 0; i < n; i++)
		{
			getline(cin, line);
			stringstream ss(line);

			string u, v;
			int c;

			ss >> u >> v >> c;
			edges.push_back(Edge(u, v, c));

			parents[u] = u;
			parents[v] = v;

			ranks[u] = 0;
			ranks[v] = 0;
		}

		sort(edges.begin(), edges.end());
		int ans(0);

		for (auto &edge : edges)
		{
			string u = edge.u;
			string v = edge.v;
			int c = edge.c;

			if (unite_sets(u, v))
				ans += c;
		}

		if (first_case)
		{
			cout << ans << endl;
			first_case = false;
		}

		else
		{
			cout << endl << ans << endl;
		}	
	}

	return 0;
}