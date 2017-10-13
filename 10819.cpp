#include <bits/stdc++.h>
using namespace std;

const int P = 4010;
const int f = 10;

int M, N;
vector<int> fav, cost;

int dp[10201][110];

inline int go(int money, int curr)
{
	if (money > M && M < 1800)
		return -1000;

	if (money > M + 200)
		return -1000;

	if (curr == N)
	{
		if (money > M && money <= 2000)
			return -1000;
		return 0;
	}

	int &ans = dp[money][curr];
	if (ans != -1)
		return ans;

	ans = max(go(money + cost[curr], curr + 1) + fav[curr],  go(money, curr + 1));
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);

	while (cin >> M >> N)
	{
		fav.clear();
		cost.clear();

		fav.resize(N);
		cost.resize(N);
		memset(dp, -1, sizeof dp);

		for (int i = 0; i < N; i++)
		{
			cin >> cost[i] >> fav[i];
		}

		cout << go(0, 0) << endl;
	}

	return 0;
}