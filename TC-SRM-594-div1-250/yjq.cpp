#include<bits/stdc++.h>
using namespace std;typedef long long LL;const int MAXN=60;int dp[MAXN][MAXN];LL a[MAXN],b[MAXN];class AstronomicalRecords{public:int minimalPlanets(vector<int>A,vector<int>B){int n=A.size(),m=B.size();int ans=n+m;for(int i=0;i<n;i++)for(int j=0;j<m;j++){for(int k=1;k<=n;k++)a[k]=1LL*A[k-1]*B[j];for(int k=1;k<=m;k++)b[k]=1LL*B[k-1]*A[i];memset(dp,0,sizeof dp);for(int x=1;x<=n;x++)for(int y=1;y<=m;y++){dp[x][y]=max(dp[x-1][y],dp[x][y-1]);if(a[x]==b[y])dp[x][y]=max(dp[x][y],dp[x-1][y-1]+1);}if(n+m-dp[n][m]<ans)ans=n+m-dp[n][m];}return ans;}};