#include<bits/stdc++.h>
using namespace std;const int MAXN=200010;int Maxi[MAXN],Mini[MAXN],X[MAXN],Y[MAXN],K=100000;typedef long long LL;int get(LL x,int y){return(int)floor(1.0*x/y);}class ConvexPolygonGame{public:string winner(vector<int>x,vector<int>y){int n=x.size();x.push_back(x[0]);y.push_back(y[0]);int k=0;for(int i=0;i<n;i++)if(x[i]==x[i+1])Mini[x[i]+K]=min(y[i],y[i+1])+1,Maxi[x[i]+K]=max(y[i],y[i+1]);else if(x[i]>x[i+1])for(int j=x[i];j>=x[i+1];j--)Maxi[j+K]=get(1LL*y[i]*(x[i+1]-j)+1LL*y[i+1]*(j-x[i]),x[i+1]-x[i])+(j!=x[i]&&j!=x[i+1]);else for(int j=x[i];j<=x[i+1];j++)Mini[j+K]=get(1LL*y[i]*(x[i+1]-j)+1LL*y[i+1]*(j-x[i])+x[i+1]-x[i]-1,x[i+1]-x[i])+(j==x[i]||j==x[i+1]);for(int i=0;i<MAXN;i++)for(int j=Mini[i];j<Maxi[i];j++)if(X[++k]=i,Y[k]=j,k>MAXN-4)return"Masha";for(int i=3;i<=k;i++)if(1LL*(X[i]-X[1])*(Y[2]-Y[1])!=1LL*(X[2]-X[1])*(Y[i]-Y[1]))return"Masha";return"Petya";}};
