#include <bits/stdc++.h>
using namespace std;

vector<int> coins;
pair<int, int> dp[100][10001];

const int INF = 1e9;
int n, s;

pair<int, int> go(int sum, int pos)
{
	if (sum <= 0)
		return make_pair(0, 0);

	if (pos < 0)
		return make_pair(INF, INF);

	pair<int, int> &ans = dp[pos][sum];

	if (ans.first == 0)
	{
		ans = go(sum - coins[pos], pos - 1);

		ans.first += coins[pos];
		ans.second++;

		ans = min(ans, go(sum, pos - 1));
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
		cin >> s >> n;
		coins.clear();

		for (int i = 0; i < n; i++) 
		{
            for (int j = 0; j <= s; j++) 
            {
                dp[i][j].first = 0;
            }
        }

		for (int i = 0; i < n; i++)
		{
			int coin;
			cin >> coin;
			coins.push_back(coin);
		}

		auto ans = go(s, n - 1);
		cout << ans.first << " " << ans.second << endl;
	}

	return 0;
}