#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	int n;

	while (cin >> n && !(n == 0))
	{
		int sum(0), ans(0);

		for (int i = 0; i < n; i++)
		{
			int x;
			cin >> x;

			sum += x;
			if (sum < 0)
				sum = 0;

			ans = max(ans, sum);
		}

		if (ans > 0)
			cout << "The maximum winning streak is " << ans  << ".\n";
		else
			cout << "Losing streak.\n";
	}
	return 0;
}