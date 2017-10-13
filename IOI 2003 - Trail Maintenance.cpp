/*
	Author : Victor Armegioiu
	IOI 2003 : Trail Maintenance

	Had to use a multiset as multiple edges may map to the same cost.
	The multiset contains all the edges that are selected each week to be part of the MST.
	The ST is constructed incrementally, deleting edges that form cycles or adding new edges 
	to the tree.

	Used Kruskal's algorithm to produce the tree.

	Test archive may be found here : http://www.ioinformatics.org/locations/ioi03/contest/.
	The script that I used to test my code can be found at the end of this file.
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge
{
	int u, v, w;
	Edge (int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

	inline bool operator<(const Edge & other) const
	{
		return w < other.w;
	}
};

int n, e;
multiset<Edge> edges;
vector<int> parents, ranks;

inline void make_set()
{
	ranks.assign(n, 0);
	parents.assign(n, 0);

	for (int i = 0; i < n; i++)
		parents[i] = i;
}

int find_set(int u)
{
	if (u != parents[u])
		parents[u] = find_set(parents[u]);

	return parents[u];
}

inline bool unite_sets(int u, int v)
{
	int u_root = find_set(u);
	int v_root = find_set(v);

	if (u_root == v_root)
		return false;

	if (ranks[u_root] < ranks[v_root])
		parents[u_root] = v_root;

	else if (ranks[u_root] > ranks[v_root])
		parents[v_root] = u_root;

	else
	{
		parents[u_root] = v_root;
		ranks[v_root]++;
	}

	return true;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin >> n >> e;

	while (e--)
	{
		int x, y, c;
		cin >> x >> y >> c;
		x--, y--;

		make_set();

		edges.insert(Edge(x, y, c));
		int mst_cost(0), curr_size(0);

		multiset<Edge>::iterator edge, dummy;
		for (edge = edges.begin(); edge != edges.end(); )
		{
			int u = (*edge).u;
			int v = (*edge).v;
			int w = (*edge).w;

			if (unite_sets(u, v))
			{
				mst_cost += w;
				edge++;
			}

			else
			{
				dummy = edge;
				edge++;
				edges.erase(dummy);
			}
		}

		if (edges.size() == n - 1)
			cout << mst_cost << endl;

		else 
			cout << -1 << endl;
		
	}

	return 0;
}

/*

	Compile this source as follows : g++ ioi.cpp -o p -std=c++11
	and run the bash script below to check the results.

	#!/bin/bash

	for i in `seq 0 20`;
	do
		./p < maintain.$i.in > out
		diff out maintain.$i.out

		if [ $? -ne 0 ]
			then
			echo "Test $i FAILED."
		else
			echo "Test $i PASSED."
		fi
		
	done

*/