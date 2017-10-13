#include <bits/stdc++.h>
using namespace std;
int N, M, Q, D;
vector<int> v;

int dp[210][210][20];

inline int go(int pos, int taken, int sum)
{
	if (taken == M)
	{
		if (sum == 0)
			return 1;
		return 0;
	}

	if (pos == N)
		return 0;

	int &ans = dp[pos][sum][taken];
	if (ans != -1)
		return ans;

	ans = go(pos + 1, taken + 1, (sum + v[pos]) % D) + go(pos + 1, taken, sum % D);
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	int query_no, set_no(1);

	while (cin >> N >> Q && ! (N == 0 && Q == 0))
	{
		v.clear();
		v.resize(N);
		
		cout << "SET " << set_no++ << ":\n";
		query_no = 1;

		for (int i = 0; i < N; i++) cin >> v[i];
		for (int i = 0; i < Q; i++)
		{
			memset(dp, -1, sizeof dp);
			cin >> D >> M;
			cout << "QUERY " << query_no++ << ": " << go(0, 0, 0) << "\n";
		}
	}


	return 0;
}