// https://csacademy.com/contest/archive/task/minimize-max-diff/statement/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
int lg[MAXN + 1];

int n, k;

vector<vector<int>> dp;
vector<int> diffs;

inline void preproc(const vector<int> &v)
{
    lg[1] = 0;
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i / 2] + 1;

    int sz = lg[n];
    dp.assign(n, vector<int> (sz + 1));
    diffs.assign(n - 1, 0);
    
    for (int i = 1; i < n; i++)
        diffs[i - 1] = v[i] - v[i - 1];
    
    for (int i = 0; i < n - 1; i++)
        dp[i][0] = diffs[i];
        
    for (int len = 1; len <= sz; len++)
        for (int i = 0; (i + (1 << len)) <= n - 1; i++)
            dp[i][len] = max(dp[i][len - 1], dp[i + (1 << (len - 1))][len - 1]);
}

inline int rmq(int left, int right)
{
    int j = lg[right - left + 1];
    return max(dp[left][j], dp[right - (1 << j) + 1][j]);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin >> n >> k;
    
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
        
    int len = n - k;
    int ans(1e9);
    
    preproc(v);
    for (int i = 0; i + len - 1 < n; i++)
        ans = min(ans, rmq(i, i + len - 2));
        
    cout << ans << endl;    
    return 0;
}
