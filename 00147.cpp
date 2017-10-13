#include <bits/stdc++.h>
using namespace std;
string amount;

int coins[] = {10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5};
long long dp[(int)3e5 + 10][15];

inline long long go(int curr_val, int pos)
{
	if (curr_val == 0)
		return 1;

	if (curr_val < 0)
		return 0;

	if (pos > 10)
		return 0;

	long long &ans = dp[curr_val][pos];
	if (ans != -1)
		return ans;

	return ans = go(curr_val - coins[pos], pos) + go(curr_val, pos + 1);
}

int main()
{
	memset(dp, -1, sizeof dp);
	while (cin >> amount && ! (amount == "0.00"))
	{
		int sum(0);
		for (int i = 0; i < amount.length(); i++)
		{
			if (amount[i] == '.') continue;

			sum *= 10;
			sum += (amount[i] - '0');
		}

		 printf("%6.2f%17lld\n", (double)sum / 100, go(sum, 0));
	}

	return 0;
}