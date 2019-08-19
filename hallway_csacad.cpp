// https://csacademy.com/contest/archive/task/hallway/

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
const int N = 5010;

vector<vector<long long>> dist(N, vector<long long> (N));
vector<long long> btlnk_dist(N, 1e18);

int main()
{
    ios_base::sync_with_stdio(false);
    vector<pii> obstacles;
    
    auto sq = [](int x)
    {
        return 1ll * x * x;    
    };
    
    auto euclid_dist = [&](const pii &p1, const pii &p2)
    {
        return sq(p1.first - p2.first) + sq(p1.second - p2.second); 
    };
    
    int n, m, k;
    cin >> n >> m >> k;
    obstacles.resize(k + 10);
    
    for (int i = 1; i <= k; i++)
    {
        int x, y;
        cin >> x >> y;
        obstacles[i] = {x, y};
    }
    
    for (int i = 1; i <= k; i++)
    {
        dist[i][k + 1] = dist[k + 1][i] = sq(obstacles[i].second);
        dist[i][k + 2] = dist[k + 2][i] = sq(m - obstacles[i].second);
        
        for (int j = 1; j <= k; j++)
            dist[i][j] = euclid_dist(obstacles[i], obstacles[j]);
    }
            
    dist[k + 1][k + 2] = dist[k + 2][k + 1] = 1ll * m * m;
    k += 2;
    
    vector<bool> visited(k + 10, false);
    vector<long long> btlnk_dist(k + 10, 1e9);
    btlnk_dist[k - 1] = 0;
    
    for (int u = 1; u <= k - 1; u++)
    {
        int v(-1);
        for (int j = 1; j <= k; j++)
            if (!visited[j] && (v == -1 || btlnk_dist[j] < btlnk_dist[v]))
                v = j;
        
        visited[v] = true;
        for (int j = 1; j <= k; j++)
            btlnk_dist[j] = min(btlnk_dist[j], max(btlnk_dist[v], dist[j][v]));
    }
    
    cout << fixed << setprecision(8) << sqrtl(btlnk_dist[k]) / 2.0 << endl;
    return 0;
}
