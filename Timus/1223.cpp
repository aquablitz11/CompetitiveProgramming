/**
 * Timus - 1223. Chernobyl’ Eagle on a Roof
 * 
 * Let dp[n][k] denotes the minimum number of experiments you need to conduct if
 * there are n+1 possible answers (0, 1, 2, ..., n) and you only have k eggs.
 * To minimize the number of tests for worst case, use the following recurrence:
 * dp[n][k] = min(max{dp[i-1][k-1], dp[n-i][k]}, 1 <= i <= n)
 * However, total time complexity would be O(N^3). It wouldn't be fast enough for this problem.
 *
 * Notice that the term max{dp[i-1][k-1], dp[n-i][k]} for 1 <= i <= n will be descending,
 * then ascending after a certain index. If the values were distinct for all i, you could use ternary search.
 * However, since the values aren't distinct, ternary search won't work properly. To fix this,
 * when values are the same, you have to look at which index of dp the value came from, which would be distinct.
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 1000;
const int inf = 1e9;

using pii = pair<int, int>;
int dp[N+1][N+1];

int main()
{
    for (int n = 1; n <= N; ++n) {
        dp[n][0] = inf;
        for (int k = 1; k <= N; ++k) {
            int b = 1, e = n;
            while (b < e) {
                int i = (b+e)/2;
                pii v1 = max(pii(dp[i-1][k-1], i-1), pii(dp[n-i][k], n-i));
                pii v2 = max(pii(dp[(i+1)-1][k-1], (i+1)-1), pii(dp[n-(i+1)][k], n-(i+1)));
                if (v1 < v2)
                    e = i;
                else
                    b = i+1;
            }
            int i = b;
            dp[n][k] = max(dp[i-1][k-1], dp[n-i][k])+1;
        }
    }

    while (true) {
        int k, n;
        scanf("%d%d", &k, &n);
        if (n == 0 && k == 0)
            break;
        printf("%d\n", dp[n][k]);
    }

    return 0;
}
