/**
 * Balkan OI '11 - Trapezoid
 *
 * It's sufficient to check whether upper and lower segments intersect to determine whether two trapezoids are independent or not.
 * Simple DP solution would be: DP[i] = max(1 + DP[j]) where trapezoid j must be completely to the right of trapezoid i.
 * We'll sort trapezoids by values of A, B, C, D, respectively and deal with those in reversed order.
 * For each trapezoid, we compute maximum value stored in a data structure for x >= C and y >= D,
 * set answer to DP then update the data structure at position x = A, y = B.
 * You can use fenwick tree on fenwick tree for these operations.
 *
 * Time complexity: O(N log^2 N)
 */

#include <bits/stdc++.h>
using namespace std;
 
using pii = pair<int, int>;
using piipii = pair<pii, pii>;
using pipii = pair<int, pii>;
#define all(x) x.begin(), x.end()
#define mp make_pair
#define F first
#define S second
 
pii comb(pii a, pii b) {
    if (a.F == b.F)
        return pii(a.F, (a.S+b.S)%30013);
    else
        return max(a, b);
}
 
const int N = 1<<17;
int n;
piipii A[N];
 
struct data {
    vector<int> key;
    vector<pii> val;
    data() {}
} ft[N];
vector<pii> coord;

pii queryft(vector<pii> &ft, int i) {
    pii ans(0, 0);
    for (; i < ft.size(); i += i&-i)
        ans = comb(ans, ft[i]);
    return ans;
}

void updateft(vector<pii> &ft, int i, pii v) {
    for (; i > 0; i -= i&-i)
        ft[i] = comb(ft[i], v);
}

pii query(int x, int y) {
    pii ans(0, 0);
    for (; x <= n; x += x&-x) {
        int p = lower_bound(all(ft[x].key), y)-ft[x].key.begin()+1;
        ans = comb(ans, queryft(ft[x].val, p));
    }
    return ans;
}

void update(int x, int y, pii v) {
    for (; x > 0; x -= x&-x) {
        int p = lower_bound(all(ft[x].key), y)-ft[x].key.begin()+1;
        updateft(ft[x].val, p, v);
    }
}

void build() {
    for (int i = 1; i <= n; ++i) {
        for (int j = i-(i&-i); j > 0; j -= j&-j)
            ft[j].key.push_back(A[i-1].F.S);
        for (int j = i; j <= n; j += j&-j)
            ft[j].key.push_back(A[i-1].F.S);
    }
    for (int i = 1; i <= n; ++i) {
        sort(all(ft[i].key));
        ft[i].val.resize(ft[i].key.size()+1, pii(0, 0));
        //printf("\n%d:", A[i].F.F);
        //for (auto x : ft[i].key) printf(" %d", x);
    }
}
 
int pos(int x) {
    return lower_bound(all(coord), pii(x, 0))-coord.begin()+1;
}
 
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d%d%d%d", &A[i].F.F, &A[i].S.F, &A[i].F.S, &A[i].S.S);
    sort(A, A+n);
    for (int i = 0; i < n; ++i)
        coord.push_back(pii(A[i].F.F, i));
    sort(coord.begin(), coord.end());
    build();
 
    pii ans(0, 0);
    for (int i = n-1; i >= 0; --i) {
        int ul = A[i].F.F, dl = A[i].F.S;
        int ur = A[i].S.F, dr = A[i].S.S;
        pii best = query(pos(ur), dr);
        ++best.F;
        if (best == pii(1, 0))
            best.S = 1;
        ans = comb(ans, best);
        update(pos(ul), dl, best);
        //printf("ul=%d, dl=%d, update to %d %d\n", ul, dl, best.F, best.S);
    }
    printf("%d %d\n", ans.F, ans.S);
 
    return 0;
}
