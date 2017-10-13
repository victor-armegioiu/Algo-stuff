#include <bits/stdc++.h>
using namespace std;

int piles[45][4];
int dp[45][45][45][45];
int n;

int go(int i1, int i2, int i3, int i4, int basket)
{
	if (__builtin_popcount(basket) == 5)
		return 0;

	int &ans = dp[i1][i2][i3][i4];
	if (ans != 0)
		return ans;

	if (i1 < n)
	{
		int color = piles[i1][0];
		int pair = (basket >> color) & 1;

		ans = max(ans, pair + go(i1 + 1, i2, i3, i4, basket ^ (1 << color)));
	}

	if (i2 < n)
	{
		int color = piles[i2][1];
		int pair = (basket >> color) & 1;

		ans = max(ans, pair + go(i1, i2 + 1, i3, i4, basket ^ (1 << color)));
	}

	if (i3 < n)
	{
		int color = piles[i3][2];
		int pair = (basket >> color) & 1;

		ans = max(ans, pair + go(i1, i2, i3 + 1, i4, basket ^ (1 << color)));
	}

	if (i4 < n)
	{
		int color = piles[i4][3];
		int pair = (basket >> color) & 1;

		ans = max(ans, pair + go(i1, i2, i3, i4 + 1, basket ^ (1 << color)));
	}

	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	while (cin >> n && n)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < 4; j++)
				cin >> piles[i][j];

		memset(dp, 0, sizeof dp);
		cout << go(0, 0, 0, 0, 0) << endl;
	}

	return 0;
}