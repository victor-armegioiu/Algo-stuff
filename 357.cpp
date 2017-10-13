#include <bits/stdc++.h>
using namespace std;
//tle switch to 1d bottom-up ugh

int coins[] = {1, 5, 10, 25, 50};
int n;

long long dp[(const int)3e5 + 1][5];

string multiple_ways = "There are %lld ways to produce %d cents change.\n";
string one_way = "There is only 1 way to produce %d cents change.\n";

long long go(int curr_sum, int i)
{
	if (curr_sum == 0)
		return 1;

	if (i > 4)
		return 0;

	if (curr_sum < 0)
		return 0;

	long long &ans =  dp[curr_sum][i];
	return ans = go(curr_sum - coins[i], i) + go(curr_sum, i + 1);

}

int main()
{
	while (cin >> n)
	{
		memset(dp, -1, sizeof dp);
		long long ans = go(n, 0);

		switch (ans)
		{
			case 1:
				printf(one_way.c_str(), n);
			break;

			default:
				printf(multiple_ways.c_str(), ans, n);
			break;
		}
	}

	return 0;	
}