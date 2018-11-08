/**
 * Codeforces 986C/987F - Graph Cutting
 * http://codeforces.com/blog/entry/59758
 */

#include <bits/stdc++.h>
using namespace std;

const int M = 1<<22;
int X[M];

int n, m;
bool exi[M], vis[M];

void dfs(int u) {
    if (vis[u]) return;
    //printf("visiting %d\n", u);
    vis[u] = true;
    if (exi[u]) {
        exi[u] = false;
        dfs(((1<<n)-1)^u);
    }
    for (int i = 0; i < n; ++i) {
        int v = u-(1<<i);
        if ((u&(1<<i)) && !vis[v]) dfs(v);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d", &X[i]);
        exi[X[i]] = true;
    }
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        if (exi[X[i]]) {
            //printf("doing %d\n", X[i]);
            ++cnt;
            dfs(((1<<n)-1)^X[i]);
        }
    }
    printf("%d\n", cnt);

    return 0;
}
