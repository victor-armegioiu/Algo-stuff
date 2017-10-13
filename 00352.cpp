#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> image;

const int d_i[] = {-1, 1, 0, 0, 1, 1, -1, -1};
const int d_j[] = {0, 0, -1, 1, 1, -1, 1, -1};

inline bool in_bounds(int i, int j)
{
	return (i >= 0 && i < n && j >= 0 && j < n);
}

void dfs(int i, int j)
{
	if (!in_bounds(i, j) || image[i][j] != '1')
		return;

	image[i][j] = '0';

	for (int cnt = 0; cnt < 8; cnt++)
	{
		int new_i = i + d_i[cnt];
		int new_j = j + d_j[cnt];

		dfs(new_i, new_j);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	int img_no(1);

	while (cin >> n)
	{
		image.resize(n);

		for (int i = 0; i < n; i++)
			cin >> image[i];

		int cc(0);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (image[i][j] == '1')
				{
					cc++;
					dfs(i, j);
				}

		cout << "Image number " << img_no++ << " contains " << cc << " war eagles.\n";
	}

	return 0;
}