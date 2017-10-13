#include <bits/stdc++.h>
using namespace std;
int L, S;

int dp[27][27][352];
string print_format = "Case %d: %d\n";

int ways(int len, int sum, int curr, string sol)
{
	if (len == 0)
		return sum == 0 ? 1 : 0; 

	if (sum < 0 || curr > 26 || len > 26 || sum > 351)
		return 0;

	int &ans = dp[len][curr][sum];
	if (ans != -1)
		return ans;

	ans = ways(len - 1, sum - curr, curr + 1) + ways(len, sum, curr + 1);
	return ans;
}

int main()
{
	int tc(1);

	while (cin >> L >> S && !(L == 0 && S == 0))
	{
		memset(dp, -1, sizeof dp);
		printf(print_format.c_str(), tc++, ways(L, S, 1));
	}

	return 0;
}