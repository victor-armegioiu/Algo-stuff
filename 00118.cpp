#include <bits/stdc++.h>
using namespace std;

unordered_map <char, pair<char, char> > turns;
unordered_map<char, int> dir_pos;

bool scent[51][51];
int n, m;

inline bool in_bounds(int x, int y)
{
	if (x > m || y > n)
		return false;

	if (x < 0 || y < 0)
		return false;

	return true;
}

int main()
{
	ios_base::sync_with_stdio(false);
	char direction;
				   //n, s, w, e	
	int dir_x[] = {0, 0, -1, 1};
	int dir_y[] = {1, -1, 0, 0};

	dir_pos['N'] = 0;
	dir_pos['S'] = 1;
	dir_pos['W'] = 2;
	dir_pos['E'] = 3;

	turns['N'] = {'W', 'E'};
	turns['W'] = {'S', 'N'};
	turns['S'] = {'E', 'W'};
	turns['E'] = {'N', 'S'};

	cin >> m >> n;

	int x, y;
	char dir;
	string instruction;

	while (cin >> x >> y >> dir >> instruction)
	{
		bool break_loop = false;
		for (char action : instruction)
		{
			if (break_loop)
				break;

			switch (action)
			{
				case 'R':
					dir = turns[dir].second;
				break;

				case 'L':
					dir = turns[dir].first;
				break;

				case 'F':
					if (scent[x][y] && !in_bounds(x + dir_x[dir_pos[dir]], y + dir_y[dir_pos[dir]]))
						continue;

					x += dir_x[dir_pos[dir]];
					y += dir_y[dir_pos[dir]];

					if (!in_bounds(x, y))
					{
						x -= dir_x[dir_pos[dir]];
						y -= dir_y[dir_pos[dir]];

						break_loop = true;
						scent[x][y] = true;
					} 

				break;
			}

		}

		if (break_loop)
		{
			cout << x << " " << y << " " << dir << " LOST" << endl;
		}	

		else cout << x << " " << y << " " << dir << endl;
	}

	return 0;
}