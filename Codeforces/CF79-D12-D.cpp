/**
 * Codeforces - 79D Password
 *
 * Instead of looking at the original array of 0s and 1s, we will look at the difference array instead:
 * 1s will be placed on position where number changes. For example, 1100111_ -> 10101001.
 * (We also add one more bit at the end for simplicity: number changes back from 1 to 0 after array ends.)
 * There will be at most 2K positions with 1s. Let's denote the number of positions as #K.
 *
 * Now, the problem becomes finding a way to set all #k positions from 0 to 1.
 * Notice that each of the original range flips is now turned into "flip two bits at the same time."
 * The only interesting operations fall into one of these two types:
 * 1) flip two bits in #k positions at the same time, or
 * 2) flip one bit of the #k positions, then another bit outside of the #k positions.
 * For type 2, we have to keep doing more operations until we move the outside bit to one of the #k positions
 * (precompute this distance with SSSP from each of the #k sources),
 * making this equivalent to type 1 operation with bigger cost. We could precompute the cost for these (#k)^2 interesting operations.
 *
 * We can solve SSSP from state "all 0s" to "all 1s," but an extra logarithmic factor would exceed the time limit.
 * The last thing to notice is that, when flipping two bits, we should always flip 00 to 11. (No 01 -> 10 or 10 -> 01 or 11 -> 10.)
 * There won't be a case where you need to do 000 -> 110 -> 101. Since operation 000 -> 101 is already available.
 * Removing those cases out, we will have a DAG which we could find shortest path via DP.
 *
 * Time Complexity: O(KNL + K^2 * 2^(2K))
 * - Precompute unweighted shortest path starting from each of the #k sources: O(NKL).
 * - Solve shortest path on DAG: O(2^(2K)) state * O(K^2) pairs.
 */

// headers
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
// types
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using dbl = double;
using ll = int64_t;
using ull = uint64_t;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pli = pair<ll, int>;
using piipi = pair<pii, int>;
using pipii = pair<int, pii>;
using plpii = pair<ll, pii>;
using ppii = pair<pii, pii>;
// loops
#define forx(i, x, y) for (int i = (x); i <= (y); ++i)
#define forn(i, n) for (int i = 0; i < (n); ++i)
#define for1(i, n) for (int i = 1; i <= (n); ++i)
#define rofx(i, x, y) for (int i = x; i >= y; --i)
#define rofn(i, n) for (int i = (n)-1; i >= 0; --i)
#define rof1(i, n) for (int i = n; i >= 1; --i)
#define fora(x, v) for (auto x : v)
// define shortcuts
#define all(x) begin(x), end(x)
#define pb push_back
#define eb emplace_back
#define F first
#define S second
#define X first
#define Y second
#define MP make_pair
#define MT make_tuple
// functions
template<class T> inline bool hasbit(T x, int i) { return x&(1<<i); }
template<class T> inline T togbit(T x, int i) { return x|(1<<i); }
template<class T> inline T setbit(T x, int i) { return x|(1<<i); }
template<class T> inline T rembit(T x, int i) { return x&~(1<<i); }
template<class T> inline bool setmax(T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> inline bool setmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template<class T> int compress(vector<T> &v) { sort(all(v)); v.resize(unique(all(v))-v.begin()); return v.size(); }
// read functions
// int _ = scanf... was for suppressing warn_unused_result warnings
int read_int() { int x; int _ = scanf("%d", &x); return x; }
ll read_ll() { ll x; int _ = scanf("%" SCNd64, &x); return x; }
ull read_ull() { ull x; int _ = scanf("%" SCNu64, &x); return x; }
dbl read_dbl() { dbl x; int _ = scanf("%lf", &x); return x; }
void _R(int &x) { x = read_int(); }
void _R(ll &x) { x = read_ll(); }
void _R(dbl &x) { x = read_dbl(); }
void R() {}
template<class T, class... U> void R(T &head, U &... tail) { _R(head); R(tail...); }
// print functions
template<class T> void _W(const T &x) { cout << x; }
void _W(const int &x) { printf("%d", x); }
void _W(const ll &x) { printf("%" PRId64, x); }
void _W(const ull &x) { printf("%" PRIu64, x); }
void _W(const double &x) { printf("%.16f", x); }
void _W(const char &x) { putchar(x); }
void _W(const char *x) { printf("%s", x); }
template<class T> void _W(const vector<T> &x) { for (auto i = x.begin(); i != x.end(); _W(*i++)) if (i != x.cbegin()) putchar(' '); }
void W() {}
template<class T, class... U> void W(const T &head, const U &... tail) { _W(head); putchar(sizeof...(tail) ? ' ' : '\n'); W(tail...); }
// pseudo-random number generator
template<class T, T x1, T x2, T x3, int y1, int y2, int y3>
struct PRNG {
    using S = typename make_signed<T>::type;
    T s;
    PRNG(T _s = 0) : s(_s) {}
    T next() {
        T z = (s += x1);
        z = (z ^ (z >> y1)) * x2;
        z = (z ^ (z >> y2)) * x3;
        return z ^ (z >> y3);
    }
    T next(T n) { return next() % n; }
    S next(S l, S r) { return l + next(r - l + 1); }
    T operator()() { return next(); }
    T operator()(T n) { return next(n); }
    S operator()(S l, S r) { return next(l, r); }
    static T gen(T s) { return PRNG(s)(); }
    template<class U>
    void shuffle(U first, U last) {
        size_t n = last - first;
        for (size_t i = 0; i < n; i++) swap(first[i], first[next(i + 1)]);
    }
};
PRNG<uint32_t, 0x9E3779B1, 0x85EBCA6B, 0xC2B2AE35, 16, 13, 16> r32;
PRNG<uint64_t, 0x9E3779B97F4A7C15, 0xBF58476D1CE4E5B9, 0x94D049BB133111EB, 30, 27, 31> r64;
// program

/************************************************************
                CODE STARTS BELOW THIS POINT
************************************************************/

const int N = 10010;
const int K = 21;
const int L = 110;
const int inf = 1e9;

vector<int> spots;
int dist[K][N];
int len[L];
int dp[1<<K];

int main()
{
    // input
    int n, k, l;
    R(n, k, l);
    forn(i, k) {
        int x; R(x);
        if (spots.empty() || spots.back() != x)
            spots.pb(x);
        else
            spots.pop_back();
        spots.pb(x+1);
    }
    k = spots.size();
    forn(i, l) R(len[i]);

    // precompute distance
    forn(si, k) {
        int s = spots[si];
        queue<int> Q;
        fill(dist[si], dist[si]+n+2, inf);
        dist[si][s] = 0;
        Q.push(s);
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            forn(i, l) {
                if (u+len[i] >= 1 && u+len[i] <= n+1 && dist[si][u+len[i]] == inf) {
                    dist[si][u+len[i]] = dist[si][u]+1;
                    Q.push(u+len[i]);
                }
                if (u-len[i] >= 1 && u-len[i] <= n+1 && dist[si][u-len[i]] == inf) {
                    dist[si][u-len[i]] = dist[si][u]+1;
                    Q.push(u-len[i]);
                }
            }
        }
    }

    // solve dp
    rofn(mask, 1<<k) {
        dp[mask] = inf;
        if (mask == (1<<k)-1)
            dp[mask] = 0;
        else forn(u, k) forn(v, k) if (u != v && !(mask&(1<<u)) && !(mask&(1<<v)))
            setmin(dp[mask], dp[mask|(1<<u)|(1<<v)] + dist[v][spots[u]]);
    }
    W(dp[0] == inf ? -1 : dp[0]);

    return 0;
}
