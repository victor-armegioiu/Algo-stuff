#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;

map<string, int> memo;

int collapsable(string s) 
{
    if (memo.count(s)) return memo[s];

    int r = 0;
    unsigned i = 0;

    while (i < s.size()) 
    {
        unsigned j = i + 1;
        while (j < s.size() && s[i] == s[j]) j++;
        if (j - i > 1)
        {
            r = collapsable(s.substr(0, i) + s.substr(j));
            if (r) break;
        }

        i = j;
    }

    return memo[s] = r;
}

int main() 
{
    memo[""] = 1;
    int tcc;
    cin >> tcc;

    string s;
    while (tcc--) 
    {
        cin >> s;
        cout << collapsable(s) << endl;
    }
}