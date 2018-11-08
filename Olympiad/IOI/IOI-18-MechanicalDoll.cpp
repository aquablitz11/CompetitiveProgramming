/**
 * IOI '18 - Mechanical Doll
 *
 * Without "state reset to X when ball returns to origin" condition,
 * it's very easy to solve this problem with at most N switches:
 * - add 0 to the end of the sequence
 * - create a switch to separate odd and even positions of the sequence
 * - solve each part recursively
 *
 * With that condition, the tree must be complete. So, you have to insert more "blank" elements into the sequence.
 * (Each blank element will cause the ball to immediately return to the root of the switches.)
 * In the worst case, you have to use up to 2N switches. Earning at most 53 points for this problem.
 *
 * Notice that you can insert "blank elements" anywhere (it doesn't have to be conseuctive),
 * and if you're trying to solve a (sub)problem where every element in the list is the same, you don't have to build a switch.
 * The goal is to place blank elements in a way such that you could maximize the number of switches you don't have to build.
 * One such scheme is to place non-blank elements, alternating between right and left halves of the sequence (in all level).
 * For example, with 8 blank and non-blank elements, place non-blank elements in this order:
 * 1) _ _ _ _ _ _ _ x
 * 2) _ _ _ x _ _ _ x
 * 3) _ _ _ x _ x _ x
 * 4) _ x _ x _ x _ x
 * 5) _ x _ x _ x x x
 * 6) _ x x x _ x x x
 * 7) _ x x x x x x x
 * 8) x x x x x x x x
 * This is equivalent to adding elements in bit-reversed positions.
 */

#include <bits/stdc++.h>
#include "doll.h"
using namespace std;
 
vector<int> X, Y;
int get(int l, int r) {
    X.push_back(l);
    Y.push_back(r);
    return -X.size();
}
int solve(vector<int> &A) {
    vector<int> L, R;
    bool diff = false;
    for (int i = 0; i < A.size(); ++i) {
        if (A[i] != A[0]) diff = true;
        if (i%2==0) L.push_back(A[i]);
        else R.push_back(A[i]);
    }
    if (!diff)
        return A[0];
    A.clear();
    int l = solve(L);
    int r = solve(R);
    return get(l, r);
}
int rev(int n, int i) {
    int val = 0;
    while (n--) {
        val <<= 1;
        val |= i&1;
        i >>= 1;
    }
    return val;
}
 
void create_circuit(int m, vector<int> A) {
    A.push_back(0);
    int n = A.size();
    int k = 0;
    while ((1<<k) < n) ++k;
    vector<int> B(1<<k, 0);
    for (int i = 0; i < n; ++i) {
        int r = rev(k, (1<<k)-i-1);
        B[r] = 1;
    }
    int c = 0;
    for (int i = 0; i < (1<<k); ++i) {
        if (B[i]) B[i] = A[c++];
        else B[i] = m+1;
    }
    int u = solve(B);
    for (int i = 0; i < X.size(); ++i) {
        if (X[i] == m+1) X[i] = u;
        if (Y[i] == m+1) Y[i] = u;
    }
    vector<int> C(m+1, u);
    answer(C, X, Y);
}
