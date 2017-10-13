#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, k, m;
bool colour;
using pib = pair<int, bool>;
ll dp[51][51];

ostream& operator<<(ostream& os, vector<bool> v)
{
	for (size_t i = 0; i < v.size(); i++)
		os << (v[i] == false ? 0 : 1) << " ";
	os << "\n";
	return os;
}

ll solve (int n, int k)
{
	if (k == 0)
		return (n == 0);

	ll &ans = dp[n][k];
	if (ans != -1)
		return ans;

	ans = 0;

	for (int i = 1; i <= m; i++)
	{
		if (n - i >= 0)
			ans += solve(n - i, k - 1);
		else
			break;
	}

	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	while (cin >> n >> k >> m)
	{
		memset(dp, -1, sizeof dp);
		cout << solve(n, k) << endl;
	}

	return 0;
}