#include<bits/stdc++.h>
using namespace std;const int MAXN=60;const int INF=1000000007;struct Edge{int l,r,nxt;}e[MAXN*MAXN];int ecnt=0,hed[MAXN];void addedge(int l,int r){++ecnt,e[ecnt].l=l,e[ecnt].r=r,e[ecnt].nxt=hed[l],hed[l]=ecnt;}int f[MAXN][2];void Dfs(int x,int fr){f[x][0]=f[x][1]=0;int d=0,mind=1<<30;for(int i=hed[x];i;i=e[i].nxt){int to=e[i].r;if(to^fr){d++;Dfs(to,x);f[x][1]=max(f[x][1],f[to][1]);f[x][0]+=f[to][0];mind=min(mind,f[to][1]-f[to][0]);}}if(d==0){f[x][0]=1,f[x][1]=0;}else{if(mind<0)f[x][0]+=mind;if(f[x][0]==0)f[x][0]=1;if(d>1)f[x][1]=INF;}}int Solve(int x){Dfs(x,0);return min(f[x][0],f[x][1]);}class TPS{public:int minimalBeacons(vector<string>mp){int n=mp.size();if(n==1)return 0;for(int i=1;i<=n;i++){for(int j=1;j<=n;j++){if(mp[i-1][j-1]=='Y')addedge(i,j);}}int ans=1<<30;for(int i=1;i<=n;i++)ans=min(ans,Solve(i)+1);return ans;}};