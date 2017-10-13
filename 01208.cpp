/*
	Author : Armegioiu Victor
	UVa 1208 : Oreon

	Basic MST problem.
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge
{
	int u, v, c;
	Edge(int _u, int _v, int _c) : u(_u), v(_v), c(_c) {if (u > v) swap(u, v);}

	inline bool operator<(const Edge & other) const
	{
		return c < other.c;
	}

	inline bool operator==(const Edge & other) const
	{
		return u == other.u && v == other.v && c == other.c;
	}

};

int n;
set<Edge> edges;
vector<int> parents;
vector<int> ranks;

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
	int t, tc(1);
	cin >> t;

	auto make_set = []() -> void
	{
		ranks.assign(n, 0);
		parents.resize(n);

		for (int i = 0; i < n; i++)
			parents[i] = i;
	};

	while (t--)
	{
		cin >> n;
		cin.ignore();	
		make_set();
		edges.clear();

		string line;
		stringstream ss;

		for (int u = 0; u < n; u++)
		{
			getline(cin, line);

			ss.clear();
			ss.str(line);

			int c;
			int v(0);

			while (ss >> c)
			{
				edges.insert(Edge(u, v++, c));
				if (ss.peek() == ',' || ss.peek() == ' ')
					ss.ignore();
			}
		}

		cout << "Case " << tc++ << ":\n";
		for (auto &edge : edges)
		{
			int u = edge.u;
			int v = edge.v;
			int c = edge.c;

			if (c && unite_sets(u, v))
				cout << char(u + 65) << "-" << char(v + 65) << " " << c << endl;
		}
	}

	return 0;
}