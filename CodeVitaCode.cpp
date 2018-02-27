// Four Russian Matrix Multiplication & Exponentiation
// Use Bitset
#include<bits/stdc++.h>
using namespace std;

/*==================!!-Code-Starts-From-Here-!!==================*/

const int N = 512,B=300;
int dp[33][65][B][N]={};  // dp[k][m][b] -> Preprocessed A^(K)'s , m'th group , b'th index
int AK[33][N][N]={};  // AK[k] -> K-th power of A
int A[N][N];  // A -> original matrix
int ans[N]; // Single row to calculate answer
int temp[N];
int n,m,t; // n -> matrix dimension, m -> number of groups, t -> number of row's/coloumn's per group
vector<int> bits; // -> selection of subsets [1 at a time, 2 at a time ,... t at a time]

bool cmp(int a,int b) { // sort by number of set bits accending
	if(__builtin_popcount(a) == __builtin_popcount(b))
		return a < b;
	return __builtin_popcount(a) < __builtin_popcount(b);
}

void preProcessAK(int k) { // Preprocess A^(K) K={0,1,2,4,8,....}
	for(int g=0;g<m;g++) {
		for(int b=0;b<bits.size();b++) {
			int rr;
			for(rr=0;(bits[b]&(1<<rr))==0;rr++); // find least significant bit
			for(int cc=0;cc<n;cc++) {
				dp[k][g][bits[b]][cc] = dp[k][g][bits[b]][cc] || dp[k][g][bits[b]^(1<<rr)][cc] ||  AK[k][(g*t)+rr][cc];
				// dp[bit-index][col] = dp[bit-index ^ lsb][col] || A[lsb + offset of group][col]
			}
		}
	}

	int left=n%t; // group with less than t-rows
	for(int b=0;b<bits.size();b++) {
		int msb = 32 - __builtin_clz(bits[b]);
		if(msb > left) continue;
		int rr;
		for(rr=0;(bits[b]&(1<<rr))==0;rr++); // find least significant bit
		for(int cc=0;cc<n;cc++) {
			dp[k][m][bits[b]][cc] = dp[k][m][bits[b]][cc] || dp[k][m][bits[b]^(1<<rr)][cc] || AK[k][(m*t)+rr][cc];
		}
	}
	return;
}

void Init(int p) { // Initialization to calculate all A^(k)'s and preprocess them
	t = log2(n); // division of  'n' into 'm' groups of size 't'
	m = n/t;
	for(int i=1;i<(1<<t);i++) { // find all 2^(t)-1 combinations and sort by N(set-bits)
		bits.push_back(i);
	}
	sort(bits.begin(),bits.end(),cmp);

	for(int i=0;i<n;i++) { // Preprocess Initial Matrix A^(0) = A
		for(int j=0;j<n;j++) {
			AK[0][i][j] = A[i][j];
		}
	}
	preProcessAK(0);

	for(int k=1;k<p;k++) { // Power - k
		for(int rr=0;rr<n;rr++) { // Row - rr
			for(int g=0;g<m;g++) { // Group - g
				int b=0;
				for(int cc=0;cc<t;cc++) { // bit-index - b
					b = b | (AK[k-1][rr][(g*t)+cc]<<cc);
				}
				for(int cc=0;cc<n;cc++) {
					AK[k][rr][cc] = AK[k][rr][cc] || dp[k-1][g][b][cc];
					// A^(k) [row][col] = A^(k) [row][col] or DP(A^(k-1))[group][bit-index][col];
				}
			}

			int left = n%t; // group with less than 't' bits
			int b=0;
			for(int cc=0;cc<left;cc++) {
				b = b | (AK[k-1][rr][(m*t)+cc]<<cc);
			}
			for(int cc=0;cc<n;cc++) {
				AK[k][rr][cc] = AK[k][rr][cc] || dp[k-1][m][b][cc];
			}
		}
		preProcessAK(k);
	}
}

void solve(int rr,int p) { // row-rr , power-p of A needed
	memset(ans,0,sizeof(ans));
	int k=0; // power-k of A used now {0,1,2,4,8,....}
	bool ok=false;
	while(p) {
		if((p&1)) { // current power-k is needed
			if(!ok) { // first - needed ans[col] = A^(K)[row][col]
				for(int cc=0;cc<n;cc++) {
					ans[cc]=AK[k][rr][cc];
				}
				k++;
				p=p>>1;
				ok=true;
				continue;
			}

			for(int cc=0;cc<n;cc++) { // from second need of A^(k)
				temp[cc]=ans[cc];
				ans[cc]=0;
			}
			for(int g=0;g<m;g++) { // group - g
				int b=0;
				for(int cc=0;cc<t;cc++) { // bit-index - b
					b = b | (temp[(g*t)+cc]<<cc);
				}
				for(int cc=0;cc<n;cc++) {
					ans[cc] = ans[cc] || dp[k][g][b][cc];
					// ans[col] = ans[col] or DP(A^(K))[group][bit-index][col]
				}
			}

			int left = n%t; // group with less than t - rows/cols
			int b=0;
			for(int cc=0;cc<left;cc++) {
				b = b | (temp[(m*t)+cc]<<cc);
			}
			for(int cc=0;cc<n;cc++) {
				ans[cc] = ans[cc] || dp[k][m][b][cc];
			}
		}

		p=p>>1;
		k++;
	}
}
int main() {
	scanf("%d",&n); // get - dimension of square matrix
	for(int rr=0;rr<n;rr++) { // and also matrix
		for(int cc=0;cc<n;cc++) {
			scanf("%d",&A[rr][cc]);
		}
	}

	if(n==1) { // special case dimension - 1x1
		int test,k,rr;
		scanf("%d",&test);
		while(test--) {
			scanf("%d",&k);scanf("%d",&rr);
			if(k==0 || (A[0][0]==1)) {
				puts("1\n1");
			} else {
				puts("0\n-1");
			}
		}
		return 0;
	}

	Init(32); // Precompute - all DP[A^(K)] k:{0,1,2,...31}

	int test;
	scanf("%d",&test);

	while(test--) {
		int k,rr;
		scanf("%d",&k);scanf("%d",&rr);
		rr--;
		if(k==0) { // Base-case
			printf("1\n%d\n",rr+1);
			continue;
		}

		solve(rr,k); // solve for row -rr of A^(k)
		vector<int> val;
		for(int cc=0;cc<n;cc++) {
			if(ans[cc]==1) val.push_back(cc+1);
		}

		printf("%d\n",(int)val.size());
		if(val.size()==0) printf("-1");
		for(int cc=0;cc<val.size();cc++) {
			printf("%d ",val[cc]);
		}
		printf("\n");
	}
	return 0;
}

/*=======================!!-End-Of-Code-!!=======================*/

///////////////////////////////////////////////////////////////////
// Convex Hull Problem
/*
	Coder	: R Sampath Sukesh.
	Handle	: rsampaths16.
	Email	: rsampaths16@gmail.com.
	Country	: India.
*/


#pragma comment(linker, "/STACK:36777216")
#include<bits/stdc++.h>
using namespace std;

#define ONLINE
#ifndef ONLINE
	#define TRACE
	#define DEBUG
#endif

#ifdef TRACE
	#define trace()             cerr<<__FUNCTION__<<" : "<<__LINE__<<endl
	#define trace1(a)           cerr<<__FUNCTION__<<" : "<<__LINE__<<" | "<<#a<<'='<<a<<endl
	#define trace2(a,b)         cerr<<__FUNCTION__<<" : "<<__LINE__<<" | "<<#a<<'='<<a <<" | "<<#b<<'='<<b<<endl
	#define trace3(a,b,c)       cerr<<__FUNCTION__<<" : "<<__LINE__<<" | "<<#a<<'='<<a <<" | "<<#b<<'='<<b<<" | "<<#c<<'='<<c<<endl
	#define trace4(a,b,c,d)     cerr<<__FUNCTION__<<" : "<<__LINE__<<" | "<<#a<<'='<<a <<" | "<<#b<<'='<<b<<" | "<<#c<<'='<<c<<" | "<<#d<<'='<<d<<endl
	#define trace5(a,b,c,d,e)   cerr<<__FUNCTION__<<" : "<<__LINE__<<" | "<<#a<<'='<<a <<" | "<<#b<<'='<<b<<" | "<<#c<<'='<<c<<" | "<<#d<<'='<<d<<" | "<<#e<<'='<<e<<endl
	#define trace6(a,b,c,d,e,f) cerr<<__FUNCTION__<<" : "<<__LINE__<<" | "<<#a<<'='<<a <<" | "<<#b<<'='<<b<<" | "<<#c<<'='<<c<<" | "<<#d<<'='<<d<<" | "<<#e<<'='<<e<<" | "<<#f<<'='<<f<<endl
#else
	#define trace()
	#define trace1(a)
	#define trace2(a,b)
	#define trace3(a,b,c)
	#define trace4(a,b,c,d)
	#define trace5(a,b,c,d,e)
	#define trace6(a,b,c,d,e,f)
#endif

#ifdef DEBUG
	#define pause system("sleep 0.5s")
	#define putx(x) x
	#define msg(MSG) cerr <<__FUNCTION__<<" : msg :- "<< MSG <<endl
	#define debug(x) cerr << '>' << #x << ':' << x << endl
#else
	#define pause
	#define putx(x)
	#define msg(MSG)
	#define debug(x)
#endif

typedef long long ll;
typedef long double ld;
typedef istringstream iss;
typedef ostringstream oss;
typedef pair<int,int> pii;

// My Macros

// I/O
// special i/o
#define fast() ios::sync_with_stdio(false)
#define pw putchar(' ')
#define pn putchar('\n')
#define dg(s,i) printf("%s %d",s,i)

// num i/o
#define si(n) scanf("%d",&n)
#define pi(n) printf("%d",n)
#define sl(n) scanf("%lld",&n)
#define pl(n) printf("%lld",n)
#define sd(n) scanf("%Lf",&n)
#define pd(n) printf("%Lf",n)

// char i/o
#define gc(n) n=getchar()
#define pc(n) putchar(n)
#define gs(n) scanf("%s",n)
#define ps(n) printf("%s",n)
#define gcc(n) n=getchar_unlocked()
#define pcc(n) puchar_unlocked(n)

// Access
#define sz size()
#define ln length()
#define ff first
#define ss second
#define pb push_back //pop_back
#define pp pop_back
#define mp make_pair

// loops
// int
#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define RFOR(i,a,b) for(int i=(a);i>=(b);i--)

// STL
#define forall(it, x) for(__typeof((x).begin()) it=(x).begin();it!=(x).end();it++)
#define rep(i,z) for(int i=0;i<(z.sz);i++)
#define rforall(it, x) for(__typeof((x).rbegin()) it=(x).rbegin();it!=(x).rend();it++)
#define rrep(i,z) for(int i=((z.sz)-1);i>=0;i--)

// special
#define mset(a,val) memset(a,val,sizeof(a))
#define mcpy(a,b)   memcpy(a,b,sizeof(a))
#define mcmp(a,b)   memcmp(a,b,sizeof(a))
#define all(a)  a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define ins(A, P, B) A.insert(A.begin() + P, B)
#define ers(A, P) A.erase(A.begin() + P)
#define lbnd(A, x) (lower_bound(all(A), x) - A.begin())
#define is_in(T, x) (T.find(x) != T.end())
template<class T> void unq(T &A){ sort(all(A));A.resize(unique(all(A))-A.begin());}

// Constant's
// [[360`Deg]==[2PI`Rad]]
const int Inf = 0x3f3f3f3f;
const ll Inff = 0x3f3f3f3f3f3f3f3fLL;
const int MAX = ll(1e9+7);  // const int MAX=1000000007;
const ld  ESP = ld(1e-9);
const ld PI=ld(3.1415926535897932384626); // M_PI
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};

#define imax numeric_limits<int>::max()
#define imin numeric_limits<int>::min()
#define lmax numeric_limits<ll>::max()
#define lmin numeric_limits<ll>::min()

/*==================!!-Code-Starts-From-Here-!!==================*/
#define dist2(a,b) (((a.x-b.x)*(a.x-b.x))+((a.y-b.y)*(a.y-b.y)))
#define dist(a,b) (sqrt(dist2(a,b)))
struct point
{
	ll x,y;
	int id;
	void get(int i,int j,int k) { x=i;y=j;id=k; };
	bool operator < (const point& a)
	{
		if(y==a.y && x==a.x) return id>a.id;
		if(y==a.y) return x<a.x;
		return y<a.y;
	}
	bool operator == (const point& a)
	{
		return (y==a.y && x==a.x);
	}
};
point points[100006];
point P0;
int orientation(point a,point b,point c)
{
	int val=(b.y-a.y)*(c.x-b.x)-(c.y-b.y)*(b.x-a.x);
	if(val==0) return 0;
	return val>0 ? 1:2;
}
bool cmp(const point& P1,const point& P2)
{
	int val=orientation(P0,P1,P2);
	if((val==2) || (val==0 && dist2(P0,P1)<dist2(P0,P2))) return true;
	return false;
}
void convexHull(int n)
{
	int pos=0;
	for(int i=1;i<n;i++)
		if(points[i]<points[pos])
			pos=i;
	swap(points[0],points[pos]);
	P0=points[0];
	sort(points+1,points+n,cmp);
	int p=1,q=0;
	for(q=1;q<n;q++)
	{
		if(q<n-1 && orientation(points[0],points[q],points[q+1])==0) continue;
		points[p]=points[q];
		p++;
	}
	n=p;
	if(n==0)
	{
		printf("0.00\n\n");
		return;
	}
	if(n==1)
	{
		printf("0.00\n%d\n\n",points[0].id);
		return;
	}
	if(n==2)
	{
		double ans=0;
		ans+=dist(points[0],points[1]);
		ans*=2;
		printf("%.2f\n%d %d\n\n",ans,points[0].id,points[1].id);
		return;
	}
	vector<point> Hull;
	Hull.pb(points[0]);
	Hull.pb(points[1]);
	Hull.pb(points[2]);

	for(int i=3;i<n;i++)
	{
		while(orientation(Hull[Hull.sz-2],Hull[Hull.sz-1],points[i])!=2)
		{
			Hull.pop_back();
		}
		Hull.pb(points[i]);
	}

	double ans=0;
	ans+=dist(Hull[0],Hull[Hull.sz-1]);
	for(int i=0;i<Hull.sz-1;i++) ans+=dist(Hull[i],Hull[i+1]);
	printf("%.2f\n",ans);
	for(int i=0;i<Hull.sz;i++)
	{
		pi(Hull[i].id);pw;
	}
	pn;pn;
	return;
}
int main(void)
{
	int t,n;
	si(t);
	while(t--)
	{
		si(n);
		int x,y;
		for(int i=0;i<n;i++)
		{
			si(x);si(y);
			points[i].get(x,y,(i+1));
		}
		sort(points,points+n);
		x=0,y=0;
		for(y=0;y<n;y++)
		{
			if(y<n-1 && points[y]==points[y+1]) continue;
			points[x]=points[y];
			x++;
		}
		n=x;
		convexHull(n);
	}
	return 0;
}
/*=======================!!-End-Of-Code-!!=======================*/
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// Longest Common SubSequence
// I am +++++++++++[>++++++<-]>.+<+++++[>++++++<-]>.+++<++[>+++++<-]>..+++++++. 

#pragma comment(linker, "/STACK:36777216")
#include<bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
	#define TRACE
	#define DEBUG
#endif

#ifdef TRACE
	#define trace()             cerr<<__FUNCTION__<<" : "<<__LINE__<<endl
	#define trace1(a)           cerr<<__FUNCTION__<<" : "<<__LINE__<<" | "<<#a<<'='<<a<<endl
	#define trace2(a,b)         cerr<<__FUNCTION__<<" : "<<__LINE__<<" | "<<#a<<'='<<a <<" | "<<#b<<'='<<b<<endl
	#define trace3(a,b,c)       cerr<<__FUNCTION__<<" : "<<__LINE__<<" | "<<#a<<'='<<a <<" | "<<#b<<'='<<b<<" | "<<#c<<'='<<c<<endl
	#define trace4(a,b,c,d)     cerr<<__FUNCTION__<<" : "<<__LINE__<<" | "<<#a<<'='<<a <<" | "<<#b<<'='<<b<<" | "<<#c<<'='<<c<<" | "<<#d<<'='<<d<<endl
	#define trace5(a,b,c,d,e)   cerr<<__FUNCTION__<<" : "<<__LINE__<<" | "<<#a<<'='<<a <<" | "<<#b<<'='<<b<<" | "<<#c<<'='<<c<<" | "<<#d<<'='<<d<<" | "<<#e<<'='<<e<<endl
	#define trace6(a,b,c,d,e,f) cerr<<__FUNCTION__<<" : "<<__LINE__<<" | "<<#a<<'='<<a <<" | "<<#b<<'='<<b<<" | "<<#c<<'='<<c<<" | "<<#d<<'='<<d<<" | "<<#e<<'='<<e<<" | "<<#f<<'='<<f<<endl
#else
	#define trace()
	#define trace1(a)
	#define trace2(a,b)
	#define trace3(a,b,c)
	#define trace4(a,b,c,d)
	#define trace5(a,b,c,d,e)
	#define trace6(a,b,c,d,e,f)
#endif

#ifdef DEBUG
	#define pause system("sleep 0.5s")
	#define putx(x) x
	#define msg(MSG) cerr <<__FUNCTION__<<" : msg :- "<< MSG <<endl
	#define debug(x) cerr << '>' << #x << ':' << x << endl
#else
	#define pause
	#define putx(x)
	#define msg(MSG)
	#define debug(x)
#endif

typedef long long ll;
typedef long double ld;
typedef istringstream iss;
typedef ostringstream oss;
typedef pair<int,int> pii;

// My Macros

// I/O
// special i/o
#define fast() ios::sync_with_stdio(false)
#define pw putchar(' ')
#define pn putchar('\n')
#define dg(s,i) printf("%s %d",s,i)

// num i/o
#define si(n) scanf("%d",&n)
#define pi(n) printf("%d",n)
#define sl(n) scanf("%lld",&n)
#define pl(n) printf("%lld",n)
#define sd(n) scanf("%Lf",&n)
#define pd(n) printf("%Lf",n)

// char i/o
#define gc(n) n=getchar()
#define pc(n) putchar(n)
#define gs(n) scanf("%s",n)
#define ps(n) printf("%s",n)
#define gcc(n) n=getchar_unlocked()
#define pcc(n) puchar_unlocked(n)

// Access
#define sz size()
#define ln length()
#define ff first
#define ss second
#define pb push_back //pop_back
#define pp pop_back
#define mp make_pair

// loops
// int
#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define RFOR(i,a,b) for(int i=(a);i>=(b);i--)

// STL
#define forall(it, x) for(__typeof((x).begin()) it=(x).begin();it!=(x).end();it++)
#define rep(i,z) for(int i=0;i<(z.sz);i++)
#define rforall(it, x) for(__typeof((x).rbegin()) it=(x).rbegin();it!=(x).rend();it++)
#define rrep(i,z) for(int i=((z.sz)-1);i>=0;i--)

// special
#define mset(a,val) memset(a,val,sizeof(a))
#define mcpy(a,b)   memcpy(a,b,sizeof(a))
#define mcmp(a,b)   memcmp(a,b,sizeof(a))
#define all(a)  a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define ins(A, P, B) A.insert(A.begin() + P, B)
#define ers(A, P) A.erase(A.begin() + P)
#define lbnd(A, x) (lower_bound(all(A), x) - A.begin())
#define is_in(T, x) (T.find(x) != T.end())
template<class T> void unq(T &A){ sort(all(A));A.resize(unique(all(A))-A.begin());}

// Constant's
// [[360`Deg]==[2PI`Rad]]
const int Inf = 0x3f3f3f3f;
const ll Inff = 0x3f3f3f3f3f3f3f3fLL;
const int MAX = ll(1e9+7);  // const int MAX=1000000007;
const ld  ESP = ld(1e-9);
const ld PI=ld(3.1415926535897932384626); // M_PI
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};

#define imax numeric_limits<int>::max()
#define imin numeric_limits<int>::min()
#define lmax numeric_limits<ll>::max()
#define lmin numeric_limits<ll>::min()

/*==================!!-Code-Starts-From-Here-!!==================*/
int mat[101][101];
string a,b,c,d,ans;
void lcs() {
	int n=a.sz;
	int m=b.sz;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(a[i-1]==b[j-1]) {
				mat[i][j] = mat[i-1][j-1]+1;
			} else {
				mat[i][j] = max(mat[i-1][j],mat[i][j-1]);
			}
		}
	}
}

void formStr() {
	int n=a.sz;
	int m=b.sz;
	c=a;d=b;
	for(int i=n,j=m;i>0 && j>0;) {
		if(a[i-1] == b[j-1]) {
			c[i-1]=0;
			d[j-1]=0;
			i--;
			j--;
		} else if(mat[i-1][j] > mat[i][j-1]) {
			i--;
		} else {
			j--;
		}
	}
	ans="";
	int i,j;
	for(i=0,j=-1;i<n;i++) {
		if(c[i]!=0) {
			ans+=a[i];
		} else {
			for(j=j+1;d[j]!=0 && j<m;j++) {
				ans+=b[j];
			}
			ans+=b[j];
		}
	}
	for(j=j+1;j<m;j++) ans+=b[j];
}

int main() {
	while(true) {
		mset(mat,0);
		cin >> a >> b;
		if(cin.eof()) return 0;
		lcs();
		formStr();
		cout << ans << endl;
	}
}



/*=======================!!-End-Of-Code-!!=======================*/
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// Max-flow
// I am +++++++++++[>++++++<-]>.+<+++++[>++++++<-]>.+++<++[>+++++<-]>..+++++++. 

#pragma comment(linker, "/STACK:36777216")
#include<bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
	#define TRACE
	#define DEBUG
#endif

#ifdef TRACE
	#define trace()             cerr<<__FUNCTION__<<" : "<<__LINE__<<endl
	#define trace1(a)           cerr<<__FUNCTION__<<" : "<<__LINE__<<" | "<<#a<<'='<<a<<endl
	#define trace2(a,b)         cerr<<__FUNCTION__<<" : "<<__LINE__<<" | "<<#a<<'='<<a <<" | "<<#b<<'='<<b<<endl
	#define trace3(a,b,c)       cerr<<__FUNCTION__<<" : "<<__LINE__<<" | "<<#a<<'='<<a <<" | "<<#b<<'='<<b<<" | "<<#c<<'='<<c<<endl
	#define trace4(a,b,c,d)     cerr<<__FUNCTION__<<" : "<<__LINE__<<" | "<<#a<<'='<<a <<" | "<<#b<<'='<<b<<" | "<<#c<<'='<<c<<" | "<<#d<<'='<<d<<endl
	#define trace5(a,b,c,d,e)   cerr<<__FUNCTION__<<" : "<<__LINE__<<" | "<<#a<<'='<<a <<" | "<<#b<<'='<<b<<" | "<<#c<<'='<<c<<" | "<<#d<<'='<<d<<" | "<<#e<<'='<<e<<endl
	#define trace6(a,b,c,d,e,f) cerr<<__FUNCTION__<<" : "<<__LINE__<<" | "<<#a<<'='<<a <<" | "<<#b<<'='<<b<<" | "<<#c<<'='<<c<<" | "<<#d<<'='<<d<<" | "<<#e<<'='<<e<<" | "<<#f<<'='<<f<<endl
#else
	#define trace()
	#define trace1(a)
	#define trace2(a,b)
	#define trace3(a,b,c)
	#define trace4(a,b,c,d)
	#define trace5(a,b,c,d,e)
	#define trace6(a,b,c,d,e,f)
#endif

#ifdef DEBUG
	#define pause system("sleep 0.5s")
	#define putx(x) x
	#define msg(MSG) cerr <<__FUNCTION__<<" : msg :- "<< MSG <<endl
	#define debug(x) cerr << '>' << #x << ':' << x << endl
#else
	#define pause
	#define putx(x)
	#define msg(MSG)
	#define debug(x)
#endif

typedef long long ll;
typedef long double ld;
typedef istringstream iss;
typedef ostringstream oss;
typedef pair<int,int> pii;

// My Macros

// I/O
// special i/o
#define fast() ios::sync_with_stdio(false)
#define pw putchar(' ')
#define pn putchar('\n')
#define dg(s,i) printf("%s %d",s,i)

// num i/o
#define si(n) scanf("%d",&n)
#define pi(n) printf("%d",n)
#define sl(n) scanf("%lld",&n)
#define pl(n) printf("%lld",n)
#define sd(n) scanf("%Lf",&n)
#define pd(n) printf("%Lf",n)

// char i/o
#define gc(n) n=getchar()
#define pc(n) putchar(n)
#define gs(n) scanf("%s",n)
#define ps(n) printf("%s",n)
#define gcc(n) n=getchar_unlocked()
#define pcc(n) puchar_unlocked(n)

// Access
#define sz size()
#define ln length()
#define ff first
#define ss second
#define pb push_back //pop_back
#define pp pop_back
#define mp make_pair

// loops
// int
#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define RFOR(i,a,b) for(int i=(a);i>=(b);i--)

// STL
#define forall(it, x) for(__typeof((x).begin()) it=(x).begin();it!=(x).end();it++)
#define rep(i,z) for(int i=0;i<(z.sz);i++)
#define rforall(it, x) for(__typeof((x).rbegin()) it=(x).rbegin();it!=(x).rend();it++)
#define rrep(i,z) for(int i=((z.sz)-1);i>=0;i--)

// special
#define mset(a,val) memset(a,val,sizeof(a))
#define mcpy(a,b)   memcpy(a,b,sizeof(a))
#define mcmp(a,b)   memcmp(a,b,sizeof(a))
#define all(a)  a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define ins(A, P, B) A.insert(A.begin() + P, B)
#define ers(A, P) A.erase(A.begin() + P)
#define lbnd(A, x) (lower_bound(all(A), x) - A.begin())
#define is_in(T, x) (T.find(x) != T.end())
template<class T> void unq(T &A){ sort(all(A));A.resize(unique(all(A))-A.begin());}

// Constant's
// [[360`Deg]==[2PI`Rad]]
const int Inf = 0x3f3f3f3f;
const ll Inff = 0x3f3f3f3f3f3f3f3fLL;
const int MAX = ll(1e9+7);  // const int MAX=1000000007;
const ld  ESP = ld(1e-9);
const ld PI=ld(3.1415926535897932384626); // M_PI
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};

#define imax numeric_limits<int>::max()
#define imin numeric_limits<int>::min()
#define lmax numeric_limits<ll>::max()
#define lmin numeric_limits<ll>::min()

/*==================!!-Code-Starts-From-Here-!!==================*/
map<char,int> maps;
int cap[100][100]={};
int flow[100][100]={};
int res[100][100]={};
int vst[100];
void printer(int cc) {
	for(map<char,int>::iterator it=maps.begin();it!=maps.end();it++) {
		cerr << it->ff << " : " << it->ss << endl;
	}
	cerr << endl << "Flow" << endl;
	for(int i=0;i<cc;i++) {
		for(int j=0;j<cc;j++) {
			cerr << flow[i][j] << " ";
		}
		cerr << endl;
	}
	cerr << endl << "Residue" << endl;
	for(int i=0;i<cc;i++) {
		for(int j=0;j<cc;j++) {
			cerr << res[i][j] << " ";
		}
		cerr << endl;
	}
	cerr << endl << "Capacity" << endl;
	for(int i=0;i<cc;i++) {
		for(int j=0;j<cc;j++) {
			cerr << cap[i][j] << " ";
		}
		cerr << endl;
	}
	cerr << endl;
}
int bfs(int s,int t,int cc) {
	mset(vst,-1);
	queue<int> Q;
	Q.push(s);
	vst[s]=s;
	while(!Q.empty()) {
		int u=Q.front();
		Q.pop();
		for(int v=0;v<cc;v++) {
			if(vst[v]==-1 && ((cap[u][v]>0 && res[u][v]==0) || (cap[u][v]==0 && res[u][v]>0))) {
				vst[v]=u;
				Q.push(v);
				if(v==t) {
					int path_cap=imax;
					int x,y;
					x=u;y=v;
					while(x!=y) {
						if(cap[x][y]!=0) path_cap=min(path_cap,cap[x][y]);
						else path_cap=min(path_cap,res[x][y]);
						x=vst[x];
						y=vst[y];
					}
					while(u!=v) {
						if(cap[u][v]!=0) {
							flow[u][v]+=path_cap;
							res[v][u]+=path_cap;
							cap[u][v]-=path_cap;
							cap[v][u]-=path_cap;
						} else {
							flow[v][u]-=path_cap;
							res[u][v]-=path_cap;
							cap[u][v]+=path_cap;
							cap[v][u]+=path_cap;
						}
						u=vst[u];
						v=vst[v];
					}
					return path_cap;
				}
			}
		}
	}
	return 0;
}

int main() {
	int n;
	int cc=0;
	si(n);
	char x,y;
	int z;
	for(int i=0;i<n;i++) {
		int u,v;
		cin >> x >> y >> z;
		if(maps.count(x)==0) maps[x]=cc++;
		if(maps.count(y)==0) maps[y]=cc++;
		u=maps[x];
		v=maps[y];
		cap[u][v]+=z;
		cap[v][u]+=z;
	}
	int max_flow=0;
	int A=maps['A'];
	int Z=maps['Z'];
//	printer(cc);
	while(true) {
		z=bfs(A,Z,cc);
		debug(z);
		if(z==0) break;
		max_flow+=z;
	}
//	printer(cc);
	pi(max_flow);pn;
	return 0;
}




/*=======================!!-End-Of-Code-!!=======================*/
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// Maximum Bipartite Matching
// A C++ program to find maximal Bipartite matching.
#include <iostream>
#include <string.h>
using namespace std;
 
// M is number of applicants and N is number of jobs
#define M 6
#define N 6
 
// A DFS based recursive function that returns true if a
// matching for vertex u is possible
bool bpm(bool bpGraph[M][N], int u, bool seen[], int matchR[])
{
    // Try every job one by one
    for (int v = 0; v < N; v++)
    {
        // If applicant u is interested in job v and v is
        // not visited
        if (bpGraph[u][v] && !seen[v])
        {
            seen[v] = true; // Mark v as visited
 
            // If job 'v' is not assigned to an applicant OR
            // previously assigned applicant for job v (which is matchR[v]) 
            // has an alternate job available. 
            // Since v is marked as visited in the above line, matchR[v] 
            // in the following recursive call will not get job 'v' again
            if (matchR[v] < 0 || bpm(bpGraph, matchR[v], seen, matchR))
            {
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}
 
// Returns maximum number of matching from M to N
int maxBPM(bool bpGraph[M][N])
{
    // An array to keep track of the applicants assigned to
    // jobs. The value of matchR[i] is the applicant number
    // assigned to job i, the value -1 indicates nobody is
    // assigned.
    int matchR[N];
 
    // Initially all jobs are available
    memset(matchR, -1, sizeof(matchR));
 
    int result = 0; // Count of jobs assigned to applicants
    for (int u = 0; u < M; u++)
    {
        // Mark all jobs as not seen for next applicant.
        bool seen[N];
        memset(seen, 0, sizeof(seen));
 
        // Find if the applicant 'u' can get a job
        if (bpm(bpGraph, u, seen, matchR))
            result++;
    }
    return result;
}
 
// Driver program to test above functions
int main()
{
    // Let us create a bpGraph shown in the above example
    bool bpGraph[M][N] = {  {0, 1, 1, 0, 0, 0},
                        {1, 0, 0, 1, 0, 0},
                        {0, 0, 1, 0, 0, 0},
                        {0, 0, 1, 1, 0, 0},
                        {0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 1}
                      };
 
    cout << "Maximum number of applicants that can get job is "
         << maxBPM(bpGraph);
 
    return 0;
}
///////////////////////////////////////////////////////////////////
