/*
	Author : Victor Armegioiu
	UVa 11624 : Fire!

	Slightly more interesting BFS problem. Used a multi-source BFS by enqueuing
	all the fire points on the map and filled a 'burning time' map. This is useful
	since Joe can only go through a passable cell if the time he takes to reach that
	particular cell is less than the time needed for the fire to reach it.

	In other words, Joe can only move to a new position if he reaches it faster than 
	the fire does.
*/

#include <bits/stdc++.h>
using namespace std;

int r, c;

vector< vector<char> > maze;
vector< vector<int> > fire_time;
vector< vector<int> > joe_time;

const pair<int, int> deltas[]= {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

struct Point
{
	int i, j;
	Point(int _i, int _j) : i(_i), j(_j) {}
	Point() {}
};

inline bool in_bounds(int i, int j)
{
	return (i >= 0 && i < r && j >= 0 && j < c);
}

inline void bfs(queue<Point> &fire_q)
{
	while (!fire_q.empty())
	{
		Point fire = fire_q.front();
		fire_q.pop();

		for (auto &delta : deltas)
		{
			int new_i = fire.i + delta.first;
			int new_j = fire.j + delta.second;

			if (in_bounds(new_i, new_j) && maze[new_i][new_j] != '#' && fire_time[new_i][new_j] == -1)
			{
				fire_time[new_i][new_j] = fire_time[fire.i][fire.j] + 1;
				fire_q.push(Point(new_i, new_j));
			}
		}
	}
}

inline int joe_bfs(Point &joe_position)
{
	queue<Point> q;
	q.push(joe_position);
	joe_time[joe_position.i][joe_position.j] = 0;

	while (!q.empty())
	{
		Point u = q.front();
		q.pop();

		if (u.i == 0 || u.i == r - 1 || u.j == 0 || u.j == c - 1)
			return joe_time[u.i][u.j] + 1;

		for (auto &delta : deltas)
		{
			int new_i = u.i + delta.first;
			int new_j = u.j + delta.second;

			if (!in_bounds(new_i, new_j) || maze[new_i][new_j] == '#')
				continue;

			if (joe_time[new_i][new_j] == -1 && (joe_time[u.i][u.j] + 1 < fire_time[new_i][new_j] || fire_time[new_i][new_j] == -1))
			{
				joe_time[new_i][new_j] = joe_time[u.i][u.j] + 1;
				q.push(Point(new_i, new_j));
			}
		}
	}

	return -1;
}

int main()
{
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;

	while (t--)
	{
		cin >> r >> c;

		maze.assign(r, vector<char> (c));
		fire_time.assign(r, vector<int> (c, -1));
		joe_time.assign(r, vector<int> (c, -1));

		queue<Point> fire_queue;
		Point joe_position;

		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				cin >> maze[i][j];
				if (maze[i][j] == 'F')
				{
					fire_queue.push(Point(i, j));
					fire_time[i][j] = 0;
				}

				else if (maze[i][j] == 'J') joe_position = Point(i, j);
			}
		}

		bfs(fire_queue);
		int ans = joe_bfs(joe_position);

		if (ans != -1)
			cout << ans << endl;
		else
			cout << "IMPOSSIBLE\n";
	}

	return 0;
}