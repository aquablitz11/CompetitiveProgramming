/**
 * APIO '17 - Travelling Merchant
 *
 * For every pair of node (u, v), we will precompute:
 * - shortest path from node u to v (dist[u][v])
 * - best profit gained from buying something at node u and selling it at node v (pro[u][v])
 *
 * Then, we binary search for the answer R:
 * - build a complete graph G with edge (u, v)'s weight equal to pro[u][v]-R*dist[u][v]
 * - check if there exists a non-negative cycle in this graph
 */

#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
const int N = 110;
const int T = 1010;
const ll INF = 1e18;
 
int n, m, t;
int B[N][T], S[N][T];
ll pro[N][N], dist[N][N], A[N][N];
 
bool check(ll r)
{
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j)
            A[i][j] = pro[i][j]-dist[i][j]*r;
        A[i][i] = -INF;
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j)
                A[i][j] = max(A[i][j], A[i][k]+A[k][j]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (A[i][i] >= 0)
            return true;
    }
    return false;
}
 
int main()
{
    scanf("%d%d%d", &n, &m, &t);
    for (int i = 1; i <= n; ++i) {
        dist[i][i] = 0;
        for (int j = 1; j <= t; ++j)
            scanf("%d%d", &B[i][j], &S[i][j]);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dist[i][j] = 1e9;
            for (int k = 1; k <= t; ++k) {
                if (B[i][k] != -1 && S[j][k] != -1)
                    pro[i][j] = max(pro[i][j], (ll)S[j][k]-B[i][k]);
            }
        }
        dist[i][i] = 0;
    }
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        dist[u][v] = w;
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j)
                dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
        }
    }
 
    ll b = 0, e = 1e9;
    while (b < e) {
        ll m = (b+e+1)/2;
        if (check(m))
            b = m;
        else 
            e = m-1;
    }
    printf("%lld\n", b);
 
    return 0;
}
