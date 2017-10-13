#include <bits/stdc++.h>
using namespace std;

vector< vector<char> > is_less_than;
vector<bool> visited;
string letters;
string line;
istringstream iss;
string constraints;

inline string trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

inline bool would_break_ordering(int node)
{
	for (int i = 0; i < is_less_than[letters[node]].size(); i++)
	{
		if (visited[is_less_than[letters[node]][i]])
			return true;
	}

	return false;
}

void dfs(string toposort)
{	
	if (toposort.length() == letters.length())
	{
		cout << toposort << endl;
		return;
	}

	for (int i = 0; i < letters.length(); i++)
	{
		if (!visited[letters[i]])
		{
			visited[letters[i]] = true;
			if (!would_break_ordering(i))
			{
				dfs(toposort + letters[i]);
			}

			visited[letters[i]] = false;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	bool blank(false);

	while (getline(cin, line))
	{
		is_less_than.assign(256, vector<char> ());
		visited.assign(256, false);
		iss.clear();

		letters = line;
		sort(letters.begin(), letters.end());
		letters = trim(letters);

		getline(cin, constraints);
		iss.str(constraints);

		char u, v;
		while (iss >> u >> v) is_less_than[u].push_back(v);

		if (blank)
			cout << endl;
		blank = true;

		dfs("");
	}

	return 0;
}