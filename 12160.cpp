/*
	Author : Victor Armegioiu
	UVa 12160 : Unlock the Lock

	Use BFS to explore possible valid configurations in order to reach the goal.
*/

#include <bits/stdc++.h>
using namespace std;

int l, u, r;
vector<int> buttons;
vector<int> dist;

inline int bfs()
{
	queue<int> q;
	q.push(l);
	dist[l] = 0;

	while (!q.empty())
	{
		int curr_state  = q.front();
		q.pop();

		if (curr_state == u)
			return dist[curr_state];

		for (int &button : buttons)
		{
			int new_state = curr_state + button;
			if (new_state >= 10000) new_state -= 10000;

			if (dist[new_state] == 1e9)
			{
				dist[new_state] = dist[curr_state] + 1;
				q.push(new_state);
			}
		}
	}

	return -1;
}

int main()
{
	ios_base::sync_with_stdio(false);
	int tc(1);

	while (cin >> l >> u >> r, l, u, r)
	{
		buttons.resize(r);
		dist.assign(10000, 1e9);

		for (int i = 0; i < r; i++) cin >> buttons[i];
		int ans = bfs();

		cout << "Case " << tc++ << ": ";
		if (ans != -1)
			cout << ans << endl;
		else
			cout << "Permanently Locked\n";
	}

	return 0;
}