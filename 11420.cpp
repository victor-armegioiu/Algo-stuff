#include <bits/stdc++.h>
using namespace std;

int N, S;
typedef long long ll;
ll dp[66][66][2];

ll ways(int n, int s, int state)
{
	if (s > S)
		return 0;

	if (n == N)
		return s == S;

	ll &ans = dp[n][s][state];
	if (ans != -1)
		return ans;

	ans = ways(n + 1, s, 0) + ways(n + 1, s + (state ? 1 : 0), 1);
	return ans; 
}

int main()
{
	while (scanf("%d %d", &N, &S) == 2)
	{
		if (N == -1)
			break;
		memset(dp, -1, sizeof dp);
		printf("%lld\n", ways(0, 0, 1));
	}

	return 0;
}