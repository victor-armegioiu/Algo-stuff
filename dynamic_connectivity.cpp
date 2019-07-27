// Dynamic connectivity https://codeforces.com/gym/100551/problem/A

#include <bits/stdc++.h>
using namespace std;
 
ifstream fin("connect.in");
ofstream fout("connect.out");
 
struct dsu_save {
    int v, rnkv, u, rnku;
 
    dsu_save() {}
 
    dsu_save(int _v, int _rnkv, int _u, int _rnku)
        : v(_v), rnkv(_rnkv), u(_u), rnku(_rnku) {}
};
 
struct dsu_with_rollbacks
{
    vector<int> p, rnk;
    int comps;
    stack<dsu_save> op;
 
    dsu_with_rollbacks() {}
 
    dsu_with_rollbacks(int n)
    {
        p.resize(n);
        rnk.resize(n);
        for (int i = 0; i < n; i++)
        {
            p[i] = i;
            rnk[i] = 0;
        }
        comps = n;
    }
 
    int find_set(int v)
    {
        return (v == p[v]) ? v : find_set(p[v]);
    }
 
    bool unite(int v, int u)
    {
        v = find_set(v);
        u = find_set(u);
        if (v == u)
            return false;
        comps--;
        if (rnk[v] > rnk[u])
            swap(v, u);
        op.push(dsu_save(v, rnk[v], u, rnk[u]));
        p[v] = u;
        if (rnk[u] == rnk[v])
            rnk[u]++;
        return true;
    }
 
    void rollback()
    {
        if (op.empty())
            return;
        dsu_save x = op.top();
        op.pop();
        comps++;
        p[x.v] = x.v;
        rnk[x.v] = x.rnkv;
        p[x.u] = x.u;
        rnk[x.u] = x.rnku;
    }
};
 
struct query
{
    int v, u;
    bool united;
    query(int _v, int _u) : v(_v), u(_u) {}
};
 
struct QueryTree
{
    vector<vector<query>> t;
    dsu_with_rollbacks dsu;
    int T;
 
    QueryTree() {}
 
    QueryTree(int _T, int n) : T(_T)
    {
        dsu = dsu_with_rollbacks(n);
        t.resize(4 * T + 4);
    }
 
    void add_to_tree(int v, int l, int r, int ul, int ur, query& q)
    {
        if (ul > ur || l > r || ul > r || ur < l)
            return;
        if (l == r) {
            t[v].push_back(q);
            return;
        }
        int mid = (l + r) / 2;
        add_to_tree(2 * v, l, mid, ul, ur, q);
        add_to_tree(2 * v + 1, mid + 1, r, ul, ur, q);
    }
 
    void add_query(query q, int l, int r)
    {
        add_to_tree(1, 0, T - 1, l, r, q);
    }
 
    void dfs(int v, int l, int r, vector<int>& ans)
    {
        for (query& q : t[v])
        {
            q.united = dsu.unite(q.v, q.u);
        }
        
        if (l == r)
            ans[l] = dsu.comps;
        else
        {
            int mid = (l + r) / 2;
            dfs(2 * v, l, mid, ans);
            dfs(2 * v + 1, mid + 1, r, ans);
        }
        
        for (query q : t[v])
        {
            if (q.united)
                dsu.rollback();
        }
    }
 
    vector<int> solve()
    {
        vector<int> ans(T);
        dfs(1, 0, T - 1, ans);
        return ans;
    }
};
 
struct interval
{
  int u, v, l, r;
  interval();
  interval(int _u, int _v, int _l, int _r) : u(_u), v(_v), l(_l), r(_r) {}
};
 
int main()
{
  ios_base::sync_with_stdio(false);
  int n, t;
  
  fin >> n >> t;
 
  QueryTree qt(t + 1, n);
  map<pair<int, int>, int> qs;
  map<pair<int, int>, int> seen;
  vector<interval> intervals;
  vector<int> qpos;
 
  for (int i = 0; i < t; i++)
  {
    char type;
    fin >> type;
 
    if (type == '+' || type == '-')
    {
      int u, v;
      fin >> u >> v;
 
      --u, --v;
      if (u > v) swap(u, v);
 
      if (type == '-')
      {
        assert(seen.count({u, v}) == true);
        intervals.push_back(interval(u, v, seen[{u, v}], i - 1));
        seen.erase({u, v});
      }
 
      else
         seen[{u, v}] = i;
    }
 
    else
      qpos.push_back(i);
 
  }
 
  for (const auto& entry : seen)
  {
    int u = entry.first.first;
    int v = entry.first.second;
    int l = entry.second;
 
    intervals.push_back(interval(u, v, l, t));
  }
 
  for (const auto& interval : intervals)
  {
    int u = interval.u;
    int v = interval.v;
 
    int l = interval.l;
    int r = interval.r;
 
    qt.add_query(query(u, v), l, r);
  }
 
  auto sol = qt.solve();
  for (int &pos : qpos)
    fout << sol[pos] << endl;
 
  return 0;
}
