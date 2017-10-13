#include <bits/stdc++.h>
using namespace std;

int N;
int dp[(const int)1e4 + 1];

int go(int sum)
{
	if (sum < 0)
		return 1e9;

	if (sum == 0)
		return 0;

	int &ans = dp[sum];
	if (ans != 0)
		return ans;

	ans = 1e9 + 1;

	for (int i = 1; i * i <= N; i++)
	{
		ans = min(ans, 1 + go(sum - i * i));
	}

	return ans;
}	

int main()
{
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;

	while (t--)
	{
		cin >> N;
		cout << go(N) << endl;
	}

	return 0;
}