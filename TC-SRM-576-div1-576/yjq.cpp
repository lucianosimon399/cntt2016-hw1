#include<bits/stdc++.h>
#define MOD 1000000009
using namespace std;int n;const int MAXN=310;int f[MAXN][MAXN],g[MAXN][MAXN],h[MAXN][MAXN];int w[MAXN],sum[MAXN];class TheExperiment{public:int countPlacements(vector<string>intensity,int m,int l,int a,int b){for(int i=0;i<intensity.size();i++){for(int j=0;j<intensity[i].length();j++)w[n++]=intensity[i][j]-'0';}for(int i=0;i<n;i++)sum[i+1]=sum[i]+w[i];g[0][0]=h[0][0]=1;for(int i=1;i<=n;i++){g[i][0]=h[i][0]=1;for(int j=1;j<=m;j++){for(int k=i-l;k<i;k++){if(sum[i]-sum[k]>=a&&sum[i]-sum[k]<=b){g[i][j]=(g[i][j]+g[k][j-1])%MOD;if(i-k==l)f[i][j]=(f[i][j]+g[k][j-1])%MOD;else f[i][j]=(f[i][j]+f[k][j-1])%MOD;}}h[i][j]=(f[i][j]+h[i-1][j])%MOD;g[i][j]=(g[i][j]+h[i-1][j])%MOD;}}return h[n][m];}};