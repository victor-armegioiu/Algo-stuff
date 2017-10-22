/*
	Author : Victor Armegioiu
	UVa 10977 : Enchanted Forest

	BFS with a small twist, intersections containted within the circle centered 
	at the positions of each pokemon with the given radius are restricted.
*/

#include <bits/stdc++.h>
using namespace std;

vector< vector<bool> > passable;
vector< vector<int> > dist;

const pair<int, int> deltas[]= {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

int r, c;

struct Point
{
	int row, col;
	Point(int _row, int _col) : row(_row), col(_col) {}
};

inline bool in_bounds(int row, int col)
{
	return row >= 0 && row < r && col >= 0 && col < c;
}

inline bool in_circle(int x, int y, int radius)
{
	return x * x + y * y <= radius * radius;
}

inline int bfs()
{
	queue<Point> q;
	q.push(Point(0, 0));
	dist[0][0] = 0;

	while (!q.empty())
	{
		Point u = q.front();
		q.pop();

		if (u.row == r - 1 && u.col == c - 1)
			return dist[u.row][u.col];

		for (auto &delta : deltas)
		{
			int new_row = u.row + delta.first;
			int new_col = u.col + delta.second;

			if (in_bounds(new_row, new_col) && passable[new_row][new_col] && dist[new_row][new_col] == -1)
			{
				dist[new_row][new_col] = dist[u.row][u.col] + 1;
				q.push(Point(new_row, new_col));
			}
		}
	}

	return -1;
}

int main()
{
	ios_base::sync_with_stdio(false);
	while (cin >> r >> c, r)
	{
		passable.assign(r, vector<bool> (c, true));
		dist.assign(r, vector<int> (c, -1));

		int n;
		cin >> n;

		for (int i = 0; i < n; i++)
		{
			int x, y;
			cin >> x >> y;
			x--, y--;

			passable[x][y] = false;
		}

		int m;
		cin >> m;

		for (int i = 0; i < m; i++)
		{
			int x, y, l;
			cin >> x >> y >> l;
			x--, y--;

			passable[x][y] = false;
			for (int row = x - l; row <= x + l; row++)
				for (int col = y - l; col <= y + l; col++)
					if (in_bounds(row, col) && in_circle(x - row, y - col, l)) passable[row][col] = false;
		}

		int cost = bfs();
		if (cost == -1)
			cout << "Impossible.\n";

		else
			cout << cost << endl;
	}

	return 0;
}