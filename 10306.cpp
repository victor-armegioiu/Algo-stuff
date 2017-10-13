#include <bits/stdc++.h>
using namespace std;

int S, M;
int dp[301][301][40];
const int INF = 100000;

struct Coin
{
	int x;
	int y;

	Coin(int _x, int _y) : x(_x), y(_y){}
};

vector<Coin> coins;

int go(int x, int y, int pos)
{
	if (x * x + y * y == S * S)
		return 0;

	if (x * x + y * y > S * S || pos == M)
		return INF;

	int &ans = dp[x][y][pos];
	if (ans != -1)
		return ans;

	ans = min(1 + go(x + coins[pos].x, y + coins[pos].y, pos)
		  	  , go(x, y, pos + 1));

	return ans;
}


int main()
{
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;

	while (n--)
	{
		cin >> M >> S;

		memset(dp, -1, sizeof dp);
		coins.clear();

		for (int i = 0; i < M; i++)
		{
			int c, v;
			cin >> c >> v;

 			coins.push_back(Coin(c, v));
		}

		int ans = go(0, 0, 0);
		cout << (ans == INF ? "not possible\n" : to_string(ans) + "\n");
	}

	return 0;
}