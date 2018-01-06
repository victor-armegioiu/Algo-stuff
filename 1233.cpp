/*
	Author : Victor Armegioiu
	UVa 1233 : USHER

	Floyd-Warshall fits like a glove when looking for the minimum cost cycle.
*/


#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	vector< vector<int> > g;

	int c;
	cin >> c;

	while (c--)
	{
		int b, p;
		cin >> b >> p;
		g.assign(p + 1, vector<int> (p + 1, 1e9));

		int q;
		cin >> q;
		for (int i = 0; i < q; i++)
		{
			int parishioner;
			cin >> parishioner;

			g[0][parishioner] = 0;
		}

		g[0][0] = 0;
		for (int parishioner = 1; parishioner <= p; parishioner++)
		{
			int rules;
			cin >> rules;

			g[parishioner][parishioner] = 0;
			for (int i = 0; i < rules; i++)
			{
				int coins, target;
				cin >> coins >> target;										  // fkin retarded possibility				
				g[parishioner][target] = min(g[parishioner][target], coins); // "There may be multiple rules with the same parishioner to receive the box.""
			}
		}

		for (int k = 0; k <= p; k++)
			for (int i = 0; i <= p; i++)
				for (int j = 0; j <= p; j++)
					g[i][j] = min(g[i][j], g[i][k] + g[k][j]);

		int cheapest_cycle(1e9 + 1);
		for (int i = 1; i <= p; i++)
			if (!g[0][i]) cheapest_cycle = min(cheapest_cycle, g[i][0]);

		int ans(0);
		int curr_sum(0);

		while (true)
		{
			if ((curr_sum += cheapest_cycle) >= b) break;
			++ans, --curr_sum;
		}

        cout << ans << endl;
	}

	return 0;
}