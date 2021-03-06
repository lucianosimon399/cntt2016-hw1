#line 2 "YamanoteLine.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 50;
const ll INF = 1e18;

std::pair<ll, ll> operator + (const std::pair<ll, ll> &p, const std::pair<ll, ll> &q) {
	return mp(p.fi + q.fi, p.se + q.se);
}

class YamanoteLine {  
public:
	std::pair<bool, ll> get(int n, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2, ll x) {
		std::pair<ll, ll> dis[N + 9];
		std::vector<std::pair<int, std::pair<ll, ll> > > adj[N + 9];
		std::queue<int> q;
		std::fill(dis, dis + n + 1, mp(INF, 0));
		dis[0] = mp(0, 0), q.push(0);
		for(int i = 1; i <= n; ++i) adj[i].pb(mp(i - 1, mp(-1, 0)));// pre[i] >= pre[i - 1] + 1 -> pre[i - 1] <= pre[i] - 1
		for(int i = 0; i < SZ(s1); ++i)
			if(s1[i] < t1[i]) adj[t1[i]].pb(mp(s1[i], mp(-l1[i], 0)));// pre[t1[i]] - pre[s1[i]] >= l1[i] -> pre[s1[i]] <= pre[t1[i]] - l1[i]
			else adj[t1[i]].pb(mp(s1[i], mp(x - l1[i], 1)));// pre[s1[i]] - pre[t1[i]] <= x - l1[i] -> pre[s1[i]] <= pre[t1[i]] + x - l1[i]
		for(int i = 0; i < SZ(s2); ++i)
			if(s2[i] < t2[i]) adj[s2[i]].pb(mp(t2[i], mp(l2[i], 0)));// pre[t2[i]] <= l2[i] + pre[s2[i]]
			else adj[s2[i]].pb(mp(t2[i], mp(-x + l2[i], -1)));// pre[s2[i]] - pre[t2[i]] >= x - l2[i] -> pre[t2[i]] <= pre[s2[i]] - x + l2[i]
		adj[n].pb(mp(0, mp(-x, -1)));// pre[n] - pre[0] >= x -> pre[0] <= pre[n] - x
		adj[0].pb(mp(n, mp(x, 1)));// pre[n] - pre[0] <= x -> pre[n] <= pre[0] + x
		int cnt[N + 9] = {0};
		bool in[N + 9] = {true};
		ll last[N + 9] = {0};
		// spfa
		while(!q.empty()) {
			int x = q.front();
			in[x] = false;
			cnt[x]++;
			if(cnt[x] > n) return mp(false, dis[x].se - last[x]);// check negative circle
			last[x] = dis[x].se;
			q.pop();
			for(int i = 0; i < SZ(adj[x]); ++i)
				if(dis[adj[x][i].fi].fi > dis[x].fi + adj[x][i].se.fi) {
					dis[adj[x][i].fi] = dis[x] + adj[x][i].se;
					if(dis[adj[x][i].fi].fi < 0) return mp(false, dis[adj[x][i].fi].se);// check dis < 0
					if(!in[adj[x][i].fi]) in[adj[x][i].fi] = true, q.push(adj[x][i].fi);
				}
		}
		return mp(true, 0);
	}
	long long howMany(int n, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2) {  
		ll lb = INF, ub = 0, l, r;

		// binary search for lower bound
		l = 0, r = INF;
		while(l < r) {
			ll mid = (l + r) >> 1;
			std::pair<bool, ll> p = get(n, s1, t1, l1, s2, t2, l2, mid);
			if(p.first || p.second < 0) {
				if(p.first) lb = mid;
				r = mid;
			}
			else l = mid + 1;
		}

		// binary search for upper bound
		l = 0, r = INF;
		while(l < r) {
			ll mid = (l + r + 1) >> 1;
			std::pair<bool, ll> p = get(n, s1, t1, l1, s2, t2, l2, mid);
			if(p.first || p.second > 0) {
				if(p.first) ub = mid;
				l = mid;
			}
			else r = mid - 1;
		}
		
		if(lb >= n && ub == INF) return -1;
		else if(lb > ub) return 0;
		else return ub - lb + 1;
	}  
};  
