/**
 * Baltic OI '17 - Political Development
 *
 * - Pick the node with minimum degree in the graph: u
 * - Consider all subsets of vertices connected to node u,
 *   if they form complete subgraph, maximize the answer
 * - Remove the node from the graph and repeat until all nodes are removed
 */

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
const int N = 5e4+10;

bool solved[N];
set<int> G[N];

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    priority_queue<pii> Q;
    for (int i = 0; i < n; ++i) {
        int x; scanf("%d", &x);
        while (x--) {
            int j; scanf("%d", &j);
            G[i].insert(j);
        }
        Q.emplace(-G[i].size(), i);
    }
    int ans = 1;
    while (!Q.empty()) {
        int u = Q.top().second; Q.pop();
        if (solved[u]) continue;
        solved[u] = true;
        int z = G[u].size();
        vector<int> V(G[u].begin(), G[u].end());
        //printf("currently doing node %d:", u);
        //for (auto v : V) printf(" %d", v);
        //printf("\n");
        for (int b = 0; b < (1<<z); ++b) {
            bool ok = true;
            for (int i = 0; i < z && ok; ++i) if ((1<<i)&b) {
                for (int j = i+1; j < z && ok; ++j) if ((1<<j)&b) {
                    if (!G[V[i]].count(V[j]))
                        ok = false;
                }
            }
            if (ok)
                ans = max(ans, __builtin_popcount(b)+1);
        }
        for (auto v : G[u]) {
            G[v].erase(u);
            Q.emplace(-G[v].size(), v);
        }
    }
    printf("%d\n", ans);

    return 0;
}
