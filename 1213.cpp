#include <bits/stdc++.h>
using namespace std;
const int N = 2000;
const int K = 15;

vector<int> primes;
int n, k;
int pos;

int dp[N][K][N];

inline void sieve()
{
	vector<bool> is_prime(N, true);
	int lim = sqrt(N);

	for (int i = 2; i <= lim; i++)
	{
		if (is_prime[i])
		{
			for (int j = i * i; j <= N; j += i)
				is_prime[j] = false;
		}
	}

	for (int i = 2; i < N; i++)
		if (is_prime[i]) primes.push_back(i);
}


inline int ways(int sum, int left, int curr)
{
	if (left == 0)
	{
		if (sum == 0)
			return 1;
		return 0;
	}

	if (left < 0 || sum < 0 || primes[curr] > n)
		return 0;

	int &ans = dp[sum][left][curr];
	if (ans != -1)
		return ans;

	ans = ways(sum - primes[curr], left - 1, curr + 1) 
		+ ways(sum, left, curr + 1);

	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	sieve();

	while (cin >> n >> k && !(n == 0 && k == 0))
	{
		memset(dp, -1, sizeof dp);
		cout << ways(n, k, 0) << endl;
	}

	return 0;
			
}