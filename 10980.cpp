#include <bits/stdc++.h>
using namespace std;

struct Offer
{
	int size;
	double price;

	Offer(int _size, double _price) : size(_size), price(_price){}
};

vector<int> wanted;
vector<Offer> offers;
double dp[110][27];

inline void build_wanted(string &w)
{
	stringstream stream(w);
	int n;

	while (stream >> n) wanted.push_back(n);
}

double cheapest_way(int items, int pos)
{
	if (items <= 0)
		return 0;

	if (pos == offers.size())
		return 10000;

	double &ans = dp[items][pos];
	if (ans != 1e9)
		return ans;

	ans = min(cheapest_way(items, pos + 1),
		      cheapest_way(items - offers[pos].size, pos) + offers[pos].price);
	return ans;

}

int main()
{
	ios_base::sync_with_stdio(false);
	double price;
	int items;
	int tc(1);

	while (cin >> price >> items)
	{

		for (int i = 0; i < 110; i++) for (int j = 0; j < 21; j++) dp[i][j] = 1e9;
		offers.clear();
		offers.push_back(Offer(1, price));
		wanted.clear();

		for (int i = 0; i < items; i++)
		{
			int size;
			double price;

			cin >> size >> price;
			offers.push_back(Offer(size, price));
		}

		string w;

		getline(std::cin, w);
		getline(std::cin, w);

		build_wanted(w);

		cout << "Case " << tc++ << ":\n";
		cout << fixed << setprecision(2);
		
		for (int no_items : wanted)
			cout << "Buy " << no_items << " for " << "$" << cheapest_way(no_items, 0) << "\n";
	}

	return 0;
}