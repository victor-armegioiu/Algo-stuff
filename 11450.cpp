#include <bits/stdc++.h>
using namespace std;

const int C = 30;
const int K = 30;

int m, c;
int no_models[C];
int prices[C][K];

int dp[210][30];

inline int go(int money, int g)
{
	if (money < 0)
		return -1e9;

	if (g == c)
		return m - money;

	int &ans = dp[money][g];
	if (ans != -1)
		return ans;

	for (int i = 0; i < no_models[g]; i++)
		ans = max(ans, go(money - prices[g][i], g + 1));

	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;

	while (t--)
	{
		cin >> m >> c;
		int k;

		memset(no_models, 0, sizeof no_models);
		memset(prices, 0, sizeof prices);
		memset(dp, -1, sizeof dp);

		for (int i = 0; i < c; i++)
		{
			cin >> no_models[i];
			for (int j = 0; j < no_models[i]; j++)
				cin >> prices[i][j];
		}

		int ans = go(m, 0);
		if (ans == -1)
			cout << "no solution\n";

		else
			cout << ans << "\n";
	}
	return 0;
}