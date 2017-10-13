#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	int t, cases(1);
	cin >> t;

	while (t--)
	{
		int n;
		cin >> n;

		int l(0x3f3f3f), r, tmp(1);
		int sum(0), ans(0);

		for (int i = 2; i <= n; i++)
		{
			int x;
			cin >> x;

			sum += x;
			if (sum < 0)
			{
				sum = 0;
				tmp = i;
			}

			if (sum >= ans)
			{
				if ((sum > ans) || (sum == ans && (i - tmp > r - l)))
				{
					l = tmp;
					r = i;
				}

				ans = sum;
			}

		}

		if (ans <= 0)
		{
			cout << "Route " << cases++ << " has no nice parts" << endl;
			continue;

		}

		cout << "The nicest part of route " << cases++ << " is between stops " << l << " and " << r << "\n";
	}
	return 0;
}