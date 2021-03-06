#line 2 "FoxPaintingBalls.cpp"  
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


class FoxPaintingBalls {  
public:  
	long long theMax(long long R, long long G, long long B, ll n) {
		ll c[] = {R, G, B};
		ll tot = n * (n + 1) / 2;
		if(!(tot % 3)) {
			// the triangle contains the same number of three colors
			tot /= 3;
			return *std::min_element(c, c + 3) / tot;
		}
		else {
			// not same, (x, x, x + 1)
			tot /= 3;
			if(!tot) return c[0] + c[1] + c[2];
			std::sort(c, c + 3);
			// (c[0] - ans * tot) + (c[1] - ans * tot) + (c[2] - ans * tot) >= ans
			return std::min(c[0] / tot, (c[0] + c[1] + c[2]) / (3 * tot + 1));
		}
	}  
};
