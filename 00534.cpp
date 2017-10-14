/*
	Author : Victor Armegioiu
	UVa 00534 : Frogger

	This problem involved finding the length of the minimax path
	between two nodes in a graph. As such, we needed to find the heaviest
	edge on the unique path from stone #1 to stone #0 through the minimum
	spanning tree.

	Found the spanning tree using Kruskal and got the answer with a dfs.
*/


#include <bits/stdc++.h>
using namespace std;

int n;
double costs[1001][1001];


struct Point
{
	int x, y;
	Point(int _x, int _y) : x(_x), y(_y) {}
};

vector<Point> points;

inline double dist(Point p1 , Point p2)
{
	double dx = p1.x - p2.x;
	double dy = p1.y - p2.y;

	return sqrt(dx * dx + dy * dy);
}

struct Edge
{
	int u, v;
	double w;

	Edge(int _u, int _v) : u(_u), v(_v) { w = dist(points[u], points[v]); }

	inline bool operator<(const Edge & other)
	{
		return w < other.w;	
	}
};


vector< vector<int> > g;
vector<Edge> edges, mst;
vector<int> ranks, parents;
vector<bool> visited;

inline void make_sets()
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

void dfs(int u, int par=-1)
{
	for (int &v : g[u])
	{
		if (v != par)
		{
			parents[v] = u;
			dfs(v, u);
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	int scenario(1);

	while (cin >> n, n)
	{
		memset(costs, 0, sizeof costs);
		make_sets();

		g.assign(n, vector<int> ());
	
		edges.clear();
		points.clear();
		mst.clear();

		for (int i = 0; i < n; i++)
		{
			int x, y;
			cin >> x >> y;

			points.push_back(Point(x, y));
		}

		for (int u = 0; u < n; u++)
		{	
			for (int v = u + 1; v < n; v++)
			{
				double w = dist(points[u], points[v]);
				edges.push_back(Edge(u, v));

				costs[u][v] = costs[v][u] = w;
			}
		}

		sort(edges.begin(), edges.end());
		for (auto &edge : edges)
		{
			int u = edge.u;
			int v = edge.v;
			int w = edge.w;

			if (unite_sets(u, v))
			{
				mst.push_back(edge);

				g[u].push_back(v);
				g[v].push_back(u);
			}

			if (mst.size() == n - 1) break;
		}

		make_sets();
		dfs(0);

		double minimax_path(0);
		int v(1);

		while (v)
		{
			minimax_path = max(minimax_path, costs[v][parents[v]]);
			v = parents[v];
		}

		cout << fixed << setprecision(3)
			 << "Scenario #" << scenario++ << "\nFrog Distance = "
			<< minimax_path << endl << endl;
	}

	return 0;
}