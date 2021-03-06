#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <cctype>
#include <queue>
#include <map>
using namespace std;
const int MAXN = 5050, MAXM = 20202, oo = 1010101010;
class Edge
{
	public:
		int to, v, next;
};
Edge e[MAXM];
int head[MAXN], en = 1, start[MAXN], height[MAXN], S, T;
void clearedge()
{
	memset(head, -1, (T + 1) * sizeof(int));
	en = 1;
}
void insert(int u, int v, int w)
{
	e[++en].to = v;
	e[en].v = w;
	e[en].next = head[u];
	head[u] = en;
	e[++en].to = u;
	e[en].v = 0;
	e[en].next = head[v];
	head[v] = en;
}
bool bfs()
{
	static queue <int> q;
	memset(height, 63, (T + 1) * sizeof(int));
	height[S] = 0;
	q.push(S);
	while(!q.empty())
	{
		int now = q.front();
		q.pop();
		for(int i = head[now]; i > 0; i = e[i].next)
			if(e[i].v && height[e[i].to] > height[now] + 1)
			{
				height[e[i].to] = height[now] + 1;
				q.push(e[i].to);
			}
	}
	return height[T] < oo;
}
int dfs(int p, int maxflow)
{
	if(p == T)
		return maxflow;
	int allflow = maxflow;
	for(int &i = start[p]; i > 0; i = e[i].next)
		if(e[i].v && height[e[i].to] > height[p])
		{
			int tmp = dfs(e[i].to, e[i].v < maxflow ? e[i].v : maxflow);
			e[i].v -= tmp;
			e[i ^ 1].v += tmp;
			if(!(maxflow -= tmp))
				break;
		}
	return allflow - maxflow;
}
int dinic()
{
	int allflow = 0;
	while(bfs())
	{
		memcpy(start, head, (T + 1) * sizeof(int));
		allflow += dfs(S, oo);
	}
	return allflow;
}
class TheTilesDivOne
{
public:
	int find(vector<string> board)
	{
		#define check(x, y, rev) do\
		if((x) >= 0 && (x) < n && (y) >= 0 && (y) < m && board[(x)][(y)] == '.')\
		{\
			if(rev)\
				insert(n * m + (x) * m + (y), i * m + j, 1);\
			else\
				insert(n * m + i * m + j, (x) * m + (y), 1);\
		}\
		while(0)//avoid ambiguous 'else' or redundant semicolon
		int n = board.size(), m = board[0].size();
		S = n * m * 2;
		T = S + 1;
		clearedge();
		for(int i = 0; i < n; i++)//build graph
			for(int j = 0; j < m; j++)
				if(board[i][j] == '.')
				{
					insert(i * m + j, n * m + i * m + j, 1);
					if((i + j) & 1)//white
						if(j & 1)//type 1
							insert(S, i * m + j, 1);
						else//type 2
							insert(n * m + i * m + j, T, 1);
					else//black
					{
						check(i - 1, j, j & 1);
						check(i + 1, j, j & 1);
						check(i, j - 1, ~j & 1);
						check(i, j + 1, ~j & 1);
					}
				}
		return dinic();//max flow
	}
};

