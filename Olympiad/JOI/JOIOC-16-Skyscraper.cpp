/**
 * JOI Open Contest '16 - Skyscraper
 *
 * Consider starting with an empty array, and adding each number in ascending order in the array.
 * Let's say we're adding number i, we will say our array has j components iff
 * there are exactly j consecutive subsegments. We will also count the number of "ends" (index 1 and index N)
 * already filled. For example, [1, 5, ?, 2, 4, 3, ?] has 2 components and 1 filled end.
 *
 * Notice that, when adding a number x to the array, we have exactly 5 choices
 * - add a new component containing just x before or after all components, between some neighboring components
 * - add a new component containing just x before or after all components and marking it as an end
 * - prepend or append number x to some components
 * - prepend or append number x to the first or last component and marking it as an end
 * - insert x between some neighboring components and consider those components merged
 * In the end, a valid array must have exactly 1 component and 2 ends filled.
 *
 * The second observation required is that the cost can simply be computed as
 * the sum of A[i]-A[i-1] times the number of components within the array before deciding the position for number A[i]
 *
 * Use dynamic programming to count the number of valid array with cost <= L
 */

#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
const int N = 110;
const int L = 1010;
const int MOD = 1e9+7;
 
int n, l;
int A[N], dp[N][N][L][3];
bool vis[N][N][L][3];
 
ll solve(int i, int comp, int val, int ends)
{
    if (comp == 0 || val > l || ends == 3) return 0;
    if (i == n+1)
        return comp==1 && val<=l && ends==2 ? 1 : 0;
 
    if (vis[i][comp][val][ends]) return dp[i][comp][val][ends];
    vis[i][comp][val][ends] = true;
 
    int x = val+(2*comp-ends)*(A[i]-A[i-1]);
 
    ll ans = 0;
    // add new component
    ans = (ans + (comp+1-ends)*solve(i+1, comp+1, x, ends)) % MOD;
    // add new component to an end
    ans = (ans + (2-ends)*solve(i+1, comp+1, x, ends+1)) % MOD;
    // append to any components normally
    ans = (ans + (2*comp-ends)*solve(i+1, comp, x, ends)) % MOD;
    // append to a component and mark as an end
    ans = (ans + (2-ends)*solve(i+1, comp, x, ends+1)) % MOD;
    // merge components
    ans = (ans + (comp-1)*solve(i+1, comp-1, x, ends)) % MOD;
 
    //printf("dp[%d][%d][%d][%d] = %lld\n", i, comp, val, ends, ans);
    return dp[i][comp][val][ends] = ans;
}
 
int main()
{
    scanf("%d%d", &n, &l);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &A[i]);
    sort(A+1, A+n+1);
    ll ans = n == 1 ? 1 : (solve(2,1,0,0)+2*solve(2,1,0,1))%MOD;
    printf("%lld\n", ans);
 
    return 0;
}
