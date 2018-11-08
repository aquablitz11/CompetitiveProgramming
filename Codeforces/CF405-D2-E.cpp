/**
 * Codeforces - 405E/406C Graph Cutting
 *
 * Solve each component individually.
 * For each component, construct a DFS tree and start solving from the leaves up to the root.
 * When solving a node, try to pair up as many incident edges as possible,
 * prioritizing the edges which have already been rejected before in previous deeper recursion.
 * If there exists an unpaired prioritized edge, then there's no solution.
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
#define rofn(i, n) for (int i = n-1; i >= 0; --i)
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

const int N = 1e5+10;

vector<pii> G[N];
bool used[N];
int vis[N];
vector<piipi> ans;

void solve(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    vector<pipii> e;
    fora(v, G[u]) {
        if (!vis[v.F]) solve(v.F);
        if (!used[v.S]) e.eb(vis[v.F] == 2 ? 0 : 1, v);
    }
    sort(all(e));
    for (int i = 0; i+1 < e.size(); i += 2) {
        used[e[i].S.S] = used[e[i+1].S.S] = true;
        ans.pb(piipi(pii(e[i].S.F, u), e[i+1].S.F));
    }
    vis[u] = 2;
}

int main()
{
    int n, m;
    R(n, m);
    forn(i, m) {
        int u, v; R(u, v);
        G[u].eb(v, i);
        G[v].eb(u, i);
    }
    for1(i, n) if (!vis[i])
        solve(i);
    bool ok = true;
    forn(i, m) if (!used[i])
        ok = false;
    if (ok) fora(x, ans)
        W(x.F.F, x.F.S, x.S);
    else
        W("No solution");

    return 0;
}
