/*
	Author : Victor Armegioiu
	UVa 11686 - Ancient Messages

	Each hieroglyph has an unique number of white connected components.
	Pixels come encoded in hex, used a lambda to decode them to binary 
	(1 for black pixels, 0 for white).

	Used a DFS based flood fill algorithm to identify the background pixels
	in the first part of the algorithm
    (traverse_countour=false mode enables only flooding adjacent
	background pixels). After the background has been determined, the same
	dfs function is used in order to count the holes within each hieroglyph, by
	flooding the contour of the symbols and increment the number of holes each time
	a non-backgound empty pixel is found (the holes are filled thereafter).	
*/

#include <bits/stdc++.h>
#define BACKGROUND_PIXEL 9
#define SEEN_BLACK_PIXEL 2
#define BLACK_PIXEL 1
#define EMPTY_PIXEL 0
#define BOUNDED_PIXEL 3

using namespace std;

unordered_map<int, char> hieroglyph;

int image[210][210];

const int d_x[] = {0, 0, -1, 1};  
const int d_y[] = {-1, 1, 0, 0};  

int h, w;
int holes;

inline bool in_bounds(int x, int y)
{
	return (y >= 0 && y < w * 4 && x >= 0 && x < h);
}

void dfs(int x, int y, int colour, bool traverse_contour=false)
{
    image[x][y] = colour;

    for (int cnt = 0; cnt < 4; cnt++)
    {
    	int new_x = x + d_x[cnt];
    	int new_y = y + d_y[cnt];

    	if (!traverse_contour)
    	{	
    		if (in_bounds(new_x, new_y) && image[new_x][new_y] == EMPTY_PIXEL)
    			dfs(new_x, new_y, colour);
    	}

    	else 
    	{
    		if (in_bounds(new_x, new_y))
    		{
    			if (image[new_x][new_y] == BLACK_PIXEL)
    				dfs(new_x, new_y, SEEN_BLACK_PIXEL, traverse_contour=true);

    			else if (image[new_x][new_y] == EMPTY_PIXEL)
    			{
    				++holes;
    				dfs(new_x, new_y, BOUNDED_PIXEL);
    			}
    		}	
    	}
    }
}

int main()
{
	ios_base::sync_with_stdio(false);
	int test(1);

	hieroglyph[1] = 'A';
	hieroglyph[3] = 'J';
	hieroglyph[5] = 'D';
	hieroglyph[4] = 'S';
	hieroglyph[0] = 'W';
	hieroglyph[2] = 'K';

	auto binary_code = [](int x) -> string 
	{
		string res; 
		x >= 'a' ? x -= 87 : x -= 48;

		do {
		 	(x & 1) ? res += '1' : res += '0'; 
		 	x >>= 1; 
		} while (x);

		while (res.length() < 4) res += '0';
		reverse(res.begin(), res.end());

		return res; 
	};

	while (cin >> h >> w && (h | w))
	{
		memset(image, 0, sizeof image);
		string line;
		string ans;

		for (int i = 0; i < h; i++)
		{
			cin >> line;
			int curr_col(0);

			for (char hex_chr : line)
			{
				string binary = binary_code(hex_chr);
				for (int j = 0; j < 4; j++)
					image[i][curr_col++] = binary[j] - '0';
			}
		}

		for (int x = 0; x < h; x++)
		{
			if (image[x][0] == EMPTY_PIXEL)
				dfs(x, 0, BACKGROUND_PIXEL);

			if (image[x][w * 4 - 1] == EMPTY_PIXEL)
				dfs(x, w * 4 - 1, BACKGROUND_PIXEL);
		}

		for (int y = 0; y < w * 4; y++)
		{	
			if (image[0][y] == EMPTY_PIXEL)
				dfs(0, y, BACKGROUND_PIXEL);

			if (image[h - 1][y] == EMPTY_PIXEL)
				dfs(h - 1, y, BACKGROUND_PIXEL);
		}

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w * 4; j++)
			{
				if (image[i][j] == BLACK_PIXEL)
				{
					holes = 0;
					dfs(i, j, SEEN_BLACK_PIXEL, true);

					ans += hieroglyph[holes];
				}
			}
		}

		sort(ans.begin(), ans.end());
		cout << "Case " << test++ << ": " << ans << endl;
	}

	return 0;
}
