/**
 * AtCoder - AGC002-D Stamp Rally
 *
 * Notice that you can binary search the answer for each query.
 * However, checking the answer for each binary searching attempt would take too long.
 * Apply parallel binary search instead:
 * http://codeforces.com/blog/entry/45578
 */

#include <bits/stdc++.h>
using namespace std;
 
using pii = pair<int, int>;
 
const int N = 1e5+10;
 
int n, m;
int U[N], V[N], S[N], T[N], K[N], L[N], R[N];
vector<int> tests[N];
 
int par[N], sz[N];
int root(int u) {
    if (par[u] == 0) return u;
    return par[u] = root(par[u]);
}
void merge(int u, int v) {
    u = root(u), v = root(v);
    if (u != v) {
        sz[v] += sz[u];
        par[u] = v;
    }
}
void reset_dsu() {
    fill(par, par+n+1, 0);
    fill(sz, sz+n+1, 1);
}
int count(int u, int v) {
    u = root(u), v = root(v);
    if (u != v)
        return sz[u]+sz[v];
    else
        return sz[u];
}
 
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
        scanf("%d%d", &U[i], &V[i]);
 
    int Q;
    scanf("%d", &Q);
    for (int i = 1; i <= Q; ++i) {
        scanf("%d%d%d", &S[i], &T[i], &K[i]);
        L[i] = 1, R[i] = m;
    }
 
    while (true) {
        bool ok = false;
        for (int i = 1; i <= Q; ++i) {
            if (L[i] != R[i]) {
                int mid = (L[i]+R[i])/2;
                tests[mid].push_back(i);
                ok = true;
            }
        }
        if (!ok) break;
        reset_dsu();
        for (int t = 1; t <= m; ++t) {
            merge(U[t], V[t]);
            for (auto q : tests[t]) {
                int mid = (L[q]+R[q])/2;
                if (count(S[q], T[q]) >= K[q])
                    R[q] = mid;
                else
                    L[q] = mid+1;
            }
            tests[t].clear();
        }
    }
    for (int i = 1; i <= Q; ++i)
        printf("%d\n", L[i]);
 
    return 0;
}
