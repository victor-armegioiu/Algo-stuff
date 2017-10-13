#include <bits/stdc++.h>
using namespace std;

struct Point
{
	int x, y;
	Point (int _x, int _y) : x(_x), y(_y) {}

	bool operator<(const Point &other)
	{
		if (x != other.x)
			return x < other.x;

		return y < other.y;
	}

	bool operator==(const Point &other)
	{
		return x == other.x && y == other.y;
	}
};

vector<Point> points;
vector< vector<int> > g;
vector<bool> visited;

int n;

inline int sq_diff(int x, int y)
{
	return (x - y) * (x - y);
}

inline void construct_graph()
{
	for (int i = 0; i < n; i++)
	{
		int &p1 = g[i][0];
		int &p2 = g[i][1];

		p1 = p2 = -1;
		int dist1(0), dist2(0);

		for (int j = 0; j < n; j++)
		{
			if (i != j)
			{
				int sq_distance = sq_diff(points[i].x, points[j].x) + sq_diff(points[i].y, points[j].y);
				if (p1 == -1 || sq_distance > dist1)
				{
					p2 = p1;
					dist2 = dist1;

					p1 = j;
					dist1 = sq_distance;
				}

				else if (p2 == -1 || sq_distance > dist2)
				{
					p2 = j;
					dist2 = sq_distance;
				}
			}
		}
	}
}

int dfs(int u)
{
	if (u == -1 || visited[u])
		return 0;

	visited[u] = true;
	return 1 + dfs(g[u][0]) + dfs(g[u][1]);
}

int main()
{
	ios_base::sync_with_stdio(false);
	int t(1);

	while (cin >> n, n)
	{
		g.assign(n, vector<int> (2, 0));
		points.assign(n, Point(-1, -1));
		visited.assign(n, false);
		bool all_reachable(false);

		for (int i = 0; i < n; i++)
			cin >> points[i].x >> points[i].y;

		Point station = points[0];
		sort(points.begin(), points.end());

		construct_graph();

		for (int i = 0; i < n; i++)
		{
			if (station == points[i])
			{
				all_reachable = (dfs(i) == n);
				break;
			}
		}

		cout << (all_reachable ? "All stations are reachable.\n" : "There are stations that are unreachable.\n");
	}

	return 0;
}