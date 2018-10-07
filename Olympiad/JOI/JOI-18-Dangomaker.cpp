/**
 * JOI '18 - Dango Maker
 *
 * Notice that the only way each group of 3's can interfere with each other would be a subset of this pattern:
 *        .
 *       R..
 *      RGB
 *     RGB
 *    RGB
 *   RGB
 *  ..B
 *   .
 * 
 * That means, you can solve each diagonal independently and sum them up to get the final answer.
 * Each diagonal can be solved with dynamic programming by sorting each group of 3's by x-pos,
 * alternating between horizontal and vertical groups,
 * and using bitmasks to denote whether previous two or three groups have been taken or not.
 */

#include <bits/stdc++.h>
using namespace std;
 
const int N = 6010;
char S[N][N];
int dp[N*2][8], val[N*2];
 
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
        scanf(" %s", S[i]);
    int ans = 0;
    for (int d = 0; d <= n+m-2; ++d) {
        for (int j = 0; j <= d; ++j) {
            int i = d-j;
            val[2*j] = (S[i][j] == 'R' && S[i][j+1] == 'G' && S[i][j+2] == 'W') ? 1 : 0;
            val[2*j+1] = (S[i][j] == 'R' && S[i+1][j] == 'G' && S[i+2][j] == 'W') ? 1 : 0;
        }
        fill(dp[2*d], dp[2*d]+8, 0);
        for (int i = 2*d+1; i >= 0; --i) {
            if (i%2 == 0) { // horizontal
                for (int j = 0; j <= 3; ++j) {
                    dp[i][j] = max(val[i]+dp[i+1][(j<<1)+1], dp[i+1][j<<1]);
                }
            } else { // vertical
                for (int j = 0; j <= 7; ++j) {
                    dp[i][j] = dp[i+1][j&3];
                    if (j == 0) dp[i][j] += val[i];
                }
            }
        }
        ans += dp[0][0];
    }
    printf("%d\n", ans);
 
    return 0;
}
