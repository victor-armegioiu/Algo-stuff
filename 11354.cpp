#include <bits/stdc++.h>
using namespace std;

int n, m, l;
vector<vector<int>> up, mx;
vector<int> parent, depth;

struct edge
{
	int u, v, w;

	edge () {}
	edge (int u, int v, int w) : u(u), v(v), w(w) {}

	bool operator<(const edge &other) const
	{
		return w < other.w;
	}
};

vector<edge> edges;
vector<vector<edge>> g;

inline void kruskal_mst()
{
	function<int(int)> find = [&](int x)
	{
		if (x != parent[x])
			parent[x] = find(parent[x]);
		return parent[x];
	};

	auto unite = [&](int u, int v)
	{
		if (find(u) == find(v))
			return false;

		parent[find(u)] = find(v);
		return true;
	};

	sort(edges.begin(), edges.end());
	for (const auto &e : edges)
	{
		int u = e.u;
		int v = e.v;
		int w = e.w;

		if (unite(u, v))
		{
			g[u].push_back(edge(u, v, w));
			g[v].push_back(edge(v, u, w));
		}
	}
}

void dfs(int u, int par, int d=0, int w=0)
{
	up[u][0] = par;
	mx[u][0] = w;
	depth[u] = d;

	for (int i = 1; i <= l; i++)
	{
		up[u][i] = up[up[u][i - 1]][i - 1];
		mx[u][i] = max(mx[u][i - 1], mx[up[u][i - 1]][i - 1]);
	}

	for (auto &e : g[u])
		if (e.v != par)
			dfs(e.v, u, d + 1, e.w);
}

inline int query(int u, int v)
{
	if (depth[u] < depth[v])
		swap(u, v);

	int diff = depth[u] - depth[v];
	int ans(0);

	for (int i = l; i >= 0; i--)
	{
		if (diff & (1 << i))
		{
			ans = max(ans, mx[u][i]);
			u = up[u][i];
		}
	}

	if (u == v)
		return ans;

	for (int i = l; i >= 0; i--)
	{
		if (up[u][i] != up[v][i])
		{
			ans = max(ans, mx[u][i]);
			ans = max(ans, mx[v][i]);

			u = up[u][i];
			v = up[v][i];
		}
	}

	return max({ans, mx[u][0], mx[v][0]});
}

int main()
{
	ios_base::sync_with_stdio(false);
	int case_count(0);
	while (cin >> n >> m)
	{
		edges.clear();
		g.assign(n, vector<edge> ());
		parent.assign(n, 0);
		for (int i = 0; i < n; i++)
			parent[i] = i;

		l = ceil(log2(n));
		up.assign(n, vector<int> (l + 1, 0));
		mx.assign(n, vector<int> (l + 1, 0));
		depth.assign(n, 0);

		if (case_count >= 1)
			cout << endl;

		++case_count;
		for (int i = 0; i < m; i++)
		{
			int u, v, w;
			cin >> u >> v >> w;

			--u, --v;
			edges.push_back(edge(u, v, w));
		}

		kruskal_mst();
		dfs(0, 0);

		int q;
		cin >> q;

		for (int i = 0; i < q; i++)
		{
			int u, v;
			cin >> u >> v;
			u--, v--;

			cout << query(u, v) << endl;
		}

	}

	return 0;
}