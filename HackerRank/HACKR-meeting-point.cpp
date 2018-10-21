/**
 * HackerRank - Meeting Point
 * 
 * Let's think "what if it was Manhattan distance" instead.
 * The solution would be obvious. Calculate sum of x and y distances using each point at the origin.
 * Then, find the point which has minimum sum.
 * 
 * Now, since we're using Chebyshev distance, it's not exactly easy to combine `max` values.
 * Luckliy, there's a way to easily transform point coordinates such that you could use Manhattan distance instead:
 * Substitute point (x, y) with point ((x+y)/2, (x-y)/2).
 * Since we don't want to deal with floating point numbers here, we'll just ignore the /2,
 * calculate the answer normally, then just divide by 2 when printing answer.
 */

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pli = pair<ll, int>;
#define mp make_pair
#define F first
#define S second

const int N = 1e5+10;
int n;
ll x[N], y[N], ans[N];
pli sx[N], sy[N];
ll qsl[N], qsr[N];

void solve(pli srt[])
{
    for (int i = 1; i <= n; ++i)
        qsl[i] = qsl[i-1]+srt[i].F;
    for (int i = n; i >= 1; --i)
        qsr[i] = qsr[i+1]+(-srt[i].F);
    for (int i = 1; i <= n; ++i) {
        int p = srt[i].S;
        ll ansl = (qsl[n]-qsl[i])-(n-i)*(srt[i].F);
        ll ansr = (qsr[1]-qsr[i])-(i-1)*(-srt[i].F);
        ans[p] += ansl+ansr;
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        x[i] = a+b, y[i] = a-b;
        sx[i] = mp(x[i], i);
        sy[i] = mp(y[i], i);
    }
    sort(sx+1, sx+n+1);
    sort(sy+1, sy+n+1);
    solve(sx);
    solve(sy);
    ll mn = 1e18;
    for (int i = 1; i <= n; ++i)
        mn = min(mn, ans[i]);
    printf("%lld\n", mn/2);

    return 0;
}
