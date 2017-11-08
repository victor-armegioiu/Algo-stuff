#include <bits/stdc++.h>	
using namespace std;

vector< vector<int> > g;
vector< vector<int> > M; //sparse table
vector<int> L, E, H;

int n(10);
int idx;

void dfs(int curr, int depth, int par=-1)
{
	H[curr] = idx;
	E[idx] = curr;
	L[idx++] = depth;

	for (int &v : g[curr])
	{
		if (v == par) continue;

		dfs(v, depth + 1, curr);

		E[idx] = curr;
		L[idx++] = depth;
	}
}

inline void preprocess()
{
	int max_log = ceil(log2(L.size()));
	int N = L.size();

	M.assign(L.size() + 1, vector<int> (max_log, 0));

	for (int i = 0; i < N; i++) 
		M[i][0] = i;

	for (int j = 1; (1 << j) <= N; j++)
	{
		for (int i = 0; i + (1 << j) - 1 < N; i++)
			if (L[M[i][j - 1]] <= L[M[i + (1 << (j - 1))][j - 1]])
				M[i][j] = M[i][j - 1];
			else
				M[i][j] = M[i + (1 << (j - 1))][j - 1];
	}
}

inline int rmq_lca(int u, int v)
{
	int i = H[u];
	int j = H[v];

	if (i > j) swap(i, j);

	int k = floor(log2(j - i + 1));
	int rmq_index;

	if (L[M[i][k]] <= L[M[j - (1 << k) + 1][k]])
		rmq_index = M[i][k];
	else
		rmq_index = M[j - (1 << k) + 1][k];

	return E[rmq_index];
}

inline void add_edge(int u, int v)
{
	g[u].push_back(v);
	g[v].push_back(u);
}

inline void stupid_lca(int u, int v)
{
	int i, j;
	i = H[u];
	j = H[v];

	if (i > j) swap(i, j);

	int lca(1e9), pos(-1);
	for (int k = i; k <= j; k++)
	{
		if (lca > L[k])
		{
			lca = L[k];
			pos = k;
		}
	}	

	cout << E[pos] << endl;
}

int main()
{
	ios_base::sync_with_stdio(false);
	g.assign(n, vector<int> ());
	E.resize(2 * n - 1);
	L.resize(2 * n - 1);
	H.resize(n);

	add_edge(0, 1);
	add_edge(0, 7);

	add_edge(1, 2);
	add_edge(1, 3);
	add_edge(1, 6);

	add_edge(3, 4);
	add_edge(3, 5);

	add_edge(7, 8);
	add_edge(7, 9);

	dfs(0, 0);

	preprocess();

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			cout << "LCA of " << "(" << i << ", " << j << ")" << " is : " << rmq_lca(i, j) << endl; 
	return 0;
}