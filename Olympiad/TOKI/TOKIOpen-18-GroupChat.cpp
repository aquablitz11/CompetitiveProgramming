/**
 * TOKI Open 2018 - Group Chat
 * https://github.com/timpostuvan/CompetitiveProgramming/blob/master/Olympiad/TOKI/GroupChat2018.cpp
 */

#include "group.h"
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
#define x first
#define y second

const int N = 1e5+10;
const int inf = 2e9;

int n;
pii P[N];

struct rect {
    int x1, y1, x2, y2;
    rect() : x1(inf), y1(inf), x2(-inf), y2(-inf) {}
    rect(int x, int y) : x1(x), x2(x), y1(y), y2(y) {}
    rect(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
    rect expand(rect o) {
        return rect(min(x1, o.x1), min(y1, o.y1), max(x2, o.x2), max(y2, o.y2));
    }
    int size() {
        if (x1 > x2 || y1 > y2) return 0;
        return max(abs(x1-x2), abs(y1-y2));
    }
};

int mnx=inf, mxx=-inf, mny=inf, mxy=-inf;
bool used[N];
bool check(int d)
{
    //printf("checking d = %d\n", d);
    for (int t = 0; t < 2; ++t) {
        fill(used+1, used+n+1, false);
        rect L, R;
        if (t == 0) L = rect(mnx, mny), R = rect(mxx, mxy);
        else L = rect(mnx, mxy), R = rect(mxx, mny);
        for (int i = 1; i <= n; ++i) {
            rect x = rect(P[i].x, P[i].y);
            if (L.expand(x).size() <= d) {
                //printf("left fill to %d %d\n", P[i].x, P[i].y);
                used[i] = true;
                L = L.expand(x);
            }
        }
        for (int i = n; i >= 1; --i) {
            rect x = rect(P[i].x, P[i].y);
            if (R.expand(x).size() <= d) {
                //printf("right fill to %d %d\n", P[i].x, P[i].y);
                used[i] = true;
                R = R.expand(x);
            }
        }
        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            if (used[i])
                ++cnt;
        }
        if (cnt == n)
            return true;
    }
    return false;
}

int getMinimumDelay(int n, vector<int> ox, vector<int> oy)
{
    ::n = n;
    for (int i = 0; i < n; ++i) {
        P[i+1] = pii(ox[i]+oy[i], ox[i]-oy[i]);
        mnx = min(mnx, P[i+1].x);
        mxx = max(mxx, P[i+1].x);
        mny = min(mny, P[i+1].y);
        mxy = max(mxy, P[i+1].y);
    }
    sort(P+1, P+n+1);
    
    int b = 0, e = 2e9;
    while (b < e) {
        int m = b+(e-b)/2;
        if (check(m))
            e = m;
        else
            b = m+1;
    }

    return b;
}
