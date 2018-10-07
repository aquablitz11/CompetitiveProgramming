/**
 * APIO '16 - Gap
 *
 * Subtask 1
 * - query the whole range to get min and max values
 * - query the range [min+1, max-1] to get second-min/second-max values
 * - keep going until we get all N elements in the array
 *
 * Subtask 2
 * - query the whole range to get min and max values
 * - divide the range [min+1, max-1] into N-2 ranges of equal size
 * - query each of them for the ends of each range
 * Notice that the answer is always difference between consecutive ends of each range
 * If n-2 numbers fall into exactly N-2 different ranges, the answer is obviously correct.
 * If at least one of the N-2 numbers fall into the same range, there exists at least one empty range,
 * the answer obtained from finding the difference between consecutive ends of each range
 * is always better than attempting to find the gap within the same range.
 */

#include <bits/stdc++.h>
#include "gap.h"
using namespace std;
 
using ll = long long;
const int N = 1e5+10;
ll A[N];
 
long long findGap(int t, int n)
{
    if (t == 1) {
        ll mn = 0, mx = 1e18;
        for (int i = 1; i <= (n+1)/2; ++i) {
            MinMax(mn, mx, &mn, &mx);
            A[i] = mn++;
            A[n-i+1] = mx--;
        }
        ll ans = 0;
        for (int i = 2; i <= n; ++i)
            ans = max(ans, A[i]-A[i-1]);
        return ans;
    } else {
        ll mn, mx;
        MinMax(0, 1e18, &mn, &mx);
        ll z = n-2 == 0 ? 0 : (mx-mn-1)/(n-2);
        vector<ll> num;
        num.push_back(mn);
        for (int i = 0; i < n-2; ++i) {
            ll l = mn+1 + z*i;
            ll r = mn+1 + z*(i+1) - 1;
            if (i == n-3) r = mx-1;
            ll mn2, mx2;
            MinMax(l, r, &mn2, &mx2);
            if (mn2 != -1) {
                num.push_back(mn2);
                num.push_back(mx2);
            }
        }
        num.push_back(mx);
        ll ans = 0;
        for (int i = 1; i < num.size(); ++i)
            ans = max(ans, num[i]-num[i-1]);
        return ans;
    }
}
