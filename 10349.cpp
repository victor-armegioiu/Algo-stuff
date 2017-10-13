/*
    Author : Victor Armegioiu
    UVa 10349 : Antenna Placement

    This is one of my favourite problems. It clearly shows a beautiful bijection between
    two seemingly unrelated concepts, namely positioning antennae in an efficient manner
    and maximum cardinality matching, using Konig's theorem.

    The problem boils down to constructing a graph by labeling the grid cells as either black or white,
    exactly like on a chessboard. Since we enforce this specific type of colouring, it's easy to notice
    that given any pair of indices i, j such that (i + j) is odd we can safely assert the colour of this 
    cell.

    Proceed with findind a maximum cardinality matching by counting the number of augmenting paths.  
*/


#include <bits/stdc++.h>
#define pb push_back

namespace init
{
    int h, w, t;
    int stars, MCBM;

    std::vector< std::vector<char> > matrix;
    std::vector< std::vector<int> > graph;

    std::set<int> left_set;
    
    std::map<int, bool> visited;
    std::map<int, int> match;
}

using namespace std;
using namespace init;

inline bool is_valid(int i, int j)
{
    if (i < h && j < w && i >= 0 && j >= 0 && matrix[i][j] == '*')
        return true;

    return false;
}

inline void add_edge(int u, int v)
{
    left_set.insert(u);

    graph[u].pb(v);
    graph[v].pb(u);
}

inline bool augment(int u)
{
    if (visited[u])
        return false;

    visited[u] = true;

    for (int v : graph[u])
        if (match[v] == 0 || augment(match[v]))
        {
            match[v] = u;
            return true;
        }

    return false;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    cin >> t;

    while (t--)
    {
        cin >> h >> w;

        matrix.assign(h, vector<char> (w, 'o'));
        graph.assign(h * w + 1, vector<int> ());

        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                cin >> matrix[i][j];
            
        for (int i = 0; i < h; i++)
        {    for (int j = 0; j < w; j++)
            {
                if (matrix[i][j] == '*')
                {
                    stars++;
                    if ((i + j) & 1)
                    {
                        if (is_valid(i - 1, j))
                            add_edge(i * w + j, (i - 1) * w + j);

                        if (is_valid(i + 1, j))
                            add_edge(i * w + j, (i + 1) * w + j); 

                        if (is_valid(i, j - 1))
                            add_edge(i * w + j, i * w + (j - 1));

                        if (is_valid(i, j + 1))
                            add_edge(i * w + j, i * w + (j + 1));  
                    }
                }
            }
        }

        match.clear();
        for (const int& node : left_set)
        {
            visited.clear();
            MCBM += augment(node);
        }

        cout << stars - MCBM << endl;

        left_set.clear();

        stars = 0;
        MCBM = 0;
    }

    return 0;
}