#include <bits/stdc++.h>
using namespace std;

// dp[n][k]
long long dp[51][51];

long long solve(int n, int m, int k)
{
	memset(dp, 0, sizeof dp);

	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= k; j++)
		{
			if (i == 0 && j == 0)
				dp[i][j] = 1;

			for (int k = 1; k <= m; k++)
			{
				if (i - k >= 0)
					dp[i][j] += dp[i - k][j - 1];
				else
					break;	
			}
		}
	}

	
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= k; j++)
		{
			cout << dp[i][j] << " ";
		}	
		cout << "\n";
	}

	return dp[n][k];
}

int main()
{
	int n, m, k;
	while (cin >> n >> k >> m)
	{
		long long result = solve(n, m, k);
		cout << result << "\n";
	}
}