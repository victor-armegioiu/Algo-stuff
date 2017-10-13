#include <bits/stdc++.h>
using namespace std;

int N, K;
const int mod = 1e6;
int dp[101][101];

inline int add(int a, int b)
{
	return (a % mod + b % mod) % mod;
}

int ways(int sum, int k)
{
	if (k == K)
		return sum == 0 ? 1 : 0;

	if (sum < 0 || k > K)
		return 0;

	if (dp[sum][k] != -1)
		return dp[sum][k];

	int ans(0);
	for (int i = 0; i <= N; i++)
	{
		ans = add(ans, ways(sum - i, k + 1));
	}

	return dp[sum][k] = ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	while (cin >> N >> K && !(N == 0 && K ==0))
	{
		memset(dp, -1, sizeof dp);
		cout << ways(N, 0) << endl;
	}

	return 0;
}