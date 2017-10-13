/*
	Author : Victor Armegioiu
	UVa 11228 : Transportation System

	Basic MST problem. The set of edges is comprised of all pairs 
	of points; sort them by euclidean distance and run Kruskal's algorithm.
	Upon joining two disjoint sets, if the distance between the current nodes
	is greater than the threshold we need to build a rail road otherwise a road is
	sufficient.
*/

#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

int n;
double r;

struct Point
{
	int x, y;
	Point (int _x, int _y) : x(_x), y(_y) {}
};

inline double dist(const Point &p1, const Point &p2)
{
	double dx = p1.x - p2.x;
	double dy = p1.y - p2.y;

	return sqrt(dx * dx + dy * dy);
}

vector<Point> points;
vector<int> parents, ranks;

struct Edge
{
	int u, v;
	double distance;

	Edge(int _u, int _v) : u(_u), v(_v) {distance = dist(points[u], points[v]);}

	bool operator<(const Edge & other)
	{
		return distance < other.distance;
	}
};

vector<Edge> edges;

inline void make_set()
{
	ranks.assign(n, 0);
	parents.assign(n, 0);

	for (int i = 0; i < n; i++)
		parents[i] = i;
}

inline int closest_int(double x)
{
	return floor(x + 0.5);
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

	if (ranks[u_root] < ranks[v_root])
		parents[u_root] = v_root;

	else if (ranks[u_root] > ranks[v_root])
		parents[v_root] = u_root;

	else
	{
		parents[v_root] = u_root;
		ranks[u_root]++;
	}

	return true;
}

int main()
{
	ios_base::sync_with_stdio(false);
	int t;
	int test_no(1);

	cin >> t;

	while (t--)
	{
		points.clear();
		edges.clear();

		cin >> n >> r;
		for (int i = 0; i < n; i++)
		{
			int x, y;
			cin >> x >> y;
			points.push_back(Point(x, y));
		}

		double roads(0), rail_roads(0);
		int states(1);
		make_set();

		for (int u = 0; u < n - 1; u++)
			for (int v = u + 1; v < n; v++)
				edges.push_back(Edge(u, v));

		sort(edges.begin(), edges.end());
		int selected(0);

		for (auto &edge : edges)
		{
			int u = edge.u;
			int v = edge.v;
			double w = edge.distance;

			if (unite_sets(u, v))
			{
				selected++;
				if (w > r)
				{
					states++;
					rail_roads += w;
				}

				else
					roads += w;
			}

			if (selected == n - 1)
				break;
		}

		cout << "Case #" << test_no++ << ": " << 
		states << " " << closest_int(roads) << " " << closest_int(rail_roads) << endl;

	}

	return 0;
}