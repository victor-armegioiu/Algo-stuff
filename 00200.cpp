#include <bits/stdc++.h>
using namespace std;

string line;
vector<string> lines;
vector<bool> visited;
vector< vector<int> > g;
stack<int> toposort;
set<int> letters;

void dfs(int u)
{
	visited[u] = true;
	for (int &v : g[u])
		if (!visited[v])
			dfs(v);

	toposort.push(u);
}

int main()
{
	ios_base::sync_with_stdio(false);
	g.assign(26, vector<int> ());
	visited.assign(26, false);

	while (getline(cin, line), line != "#")
	{
		lines.push_back(line);
		for (char &chr : line)
			letters.insert(chr - 'A');
	}	

	for (int i = 0; i < lines.size() - 1; i++)
	{
		for (int j = 0; j < lines[i].length() && j < lines[i + 1].length(); j++)
		{
			if (lines[i][j] != lines[i + 1][j])
			{
				g[lines[i][j] - 'A'].push_back(lines[i + 1][j] - 'A');
				break;
			}
		}
	}

	for (const int &u : letters)
	{
		if (!visited[u])
			dfs(u);
	}

	while (!toposort.empty())
	{
		char letter = toposort.top() + 'A';
		cout << letter;
		toposort.pop();
	}

	cout << endl;
	return 0;
}