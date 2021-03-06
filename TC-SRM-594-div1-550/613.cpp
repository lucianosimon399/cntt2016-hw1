                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  // BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndGo3.cpp"
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
#define inf 700000000
using namespace std;
struct flows
{
	int first[201000],last[201000],des[201000],vol[201000],next[201000],opp[201000],cur[201000],tt,n;
	int dis[201000],cop[201000];
	void init(int pn)
	{
		for (int i=1;i<=n;i++) first[i]=last[i]=0;
		for (int i=1;i<=tt;i++) des[i]=vol[i]=next[i]=opp[i]=0;
		tt=0;n=pn;
	}
	void getin(int c,int d,int s)
	{
		des[++tt]=d;vol[tt]=s;opp[tt]=tt+1;
		if (!first[c]) first[c]=last[c]=tt;
		else last[c]=next[last[c]]=tt;
		
		des[++tt]=c;vol[tt]=0;opp[tt]=tt-1;
		if (!first[d]) first[d]=last[d]=tt;
		else last[d]=next[last[d]]=tt;
	}
	bool bfs(int s,int t)
	{
		for (int i=1;i<=n;i++) dis[i]=inf;dis[t]=0;
		int head=1,tail=0;cop[head]=t;
		while (head!=tail)
		{
			int p=cop[++tail];
			for (int k=first[p];k;k=next[k]) if ((vol[opp[k]])&&(dis[des[k]]==inf))
			{
				dis[des[k]]=dis[p]+1;
				cop[++head]=des[k];
			}
		}
		return dis[s]!=inf;
	}
	int dfs(int s,int t,int minvol=inf)
	{
		if (s==t) return minvol;
		int bg=0;
		for (int k=cur[s];k;k=next[k])
		{
			cur[s]=k;
			if ((vol[k])&&(dis[des[k]]==dis[s]-1))
			{
				int p=dfs(des[k],t,min(vol[k],minvol-bg));
				bg+=p;
				vol[k]-=p;vol[opp[k]]+=p;
				if (bg==minvol) break;
			}
		}
		return bg;
	}		
	int dinic(int s,int t)
	{
		int ans=0;
		while (bfs(s,t))
		{
			for (int i=1;i<=n;i++) cur[i]=first[i];
			ans+=dfs(s,t);
		}
		return ans;
	}
}flow;
class FoxAndGo3
{
        public:
        int maxEmptyCells(vector <string> board)
        {
			int n=board.size(),js=0;
			flow.init(n*n+2);
			for (int i=0;i<n;i++)
			for (int j=0;j<n;j++)
			{
				if (board[i][j]=='.')
				{
					flow.getin(n*n+1,i*n+j+1,1);
					js++;
					if ((i!=0)&&(board[i-1][j]=='o')) flow.getin(i*n+j+1,(i-1)*n+j+1,inf);
					if ((i!=n-1)&&(board[i+1][j]=='o')) flow.getin(i*n+j+1,(i+1)*n+j+1,inf);
					if ((j!=0)&&(board[i][j-1]=='o')) flow.getin(i*n+j+1,i*n+(j-1)+1,inf);
					if ((j!=n-1)&&(board[i][j+1]=='o')) flow.getin(i*n+j+1,i*n+(j+1)+1,inf);
				}
				else if (board[i][j]=='o') {flow.getin(i*n+j+1,n*n+2,1);js++;}
			}
			return js-flow.dinic(n*n+1,n*n+2);
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"o.o",
 ".o.",
 "o.o"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(0, Arg1, maxEmptyCells(Arg0)); }
	void test_case_1() { string Arr0[] = {"...",
 ".o.",
 "..."}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(1, Arg1, maxEmptyCells(Arg0)); }
	void test_case_2() { string Arr0[] = {"xxxxx",
 "xxoxx",
 "xo.ox",
 "xxoxx",
 "xxxxx"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(2, Arg1, maxEmptyCells(Arg0)); }
	void test_case_3() { string Arr0[] = {".xox.",
 ".o.ox",
 "x.o.o",
 "ox.ox",
 ".ox.."}
 ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; verify_case(3, Arg1, maxEmptyCells(Arg0)); }
	void test_case_4() { string Arr0[] = {"o.o.o",
 ".ox..",
 "oxxxo",
 "..x..",
 "o.o.o"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; verify_case(4, Arg1, maxEmptyCells(Arg0)); }
	void test_case_5() { string Arr0[] = {"...",
 "...",
 "..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(5, Arg1, maxEmptyCells(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        FoxAndGo3 ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE