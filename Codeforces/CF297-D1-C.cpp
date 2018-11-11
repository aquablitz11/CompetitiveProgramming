/**
 * Codeforces - 297C/298E Splitting the Uniqueness
 *
 * (Conceptually) sort the array and split array into 3 ranges,
 * such that there are no more than ceil(n/3)+1 zeros in A and B,
 * when you fill A and B's values like this:
 * - For all i in first range, set A[i] = 0 and B[i] = S[i].
 * - For all i in second range, set B[i] = 0 and A[i] = S[i].
 * - For all i in third range, try to set B[i] to minimum value possible,
 *   without creating duplicate A[i]/B[i] values.
 */

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
#define F first
#define S second
const int N = 1e5+10;

int A[N];
pii B[N];
int ansA[N], ansB[N];
set<int> SA, SB;

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &A[i]);
        B[i] = pii(A[i], i);
    }
    sort(B, B+n);
    int m = (n+2)/3;
    for (int i = 0; i <= m && i < n; ++i) {
        ansA[B[i].S] = 0;
        SA.insert(0);
        ansB[B[i].S] = B[i].F;
        SB.insert(B[i].F);
    }
    int bnd = B[0].F == 0 ? (m+m) : (m+m+1);
    for (int i = m+1; i <= bnd && i < n; ++i) {
        ansA[B[i].S] = B[i].F;
        SA.insert(B[i].F);
        ansB[B[i].S] = 0;
        SB.insert(0);
    }
    int pb = 0;
    for (int i = bnd+1; i < n; ++i) {
        while (SB.count(pb) || SA.count(B[i].F-pb)) ++pb;
        if (pb > B[i].F) {
            printf("NO\n");
            return 0;
        }
        ansB[B[i].S] = pb;
        SB.insert(pb);
        ansA[B[i].S] = B[i].F-pb;
        SA.insert(B[i].F-pb);
    }
    printf("YES\n");
    for (int i = 0; i < n; ++i) {
        if (i != 0) printf(" ");
        printf("%d", ansA[i]);
    }
    printf("\n");
    for (int i = 0; i < n; ++i) {
        if (i != 0) printf(" ");
        printf("%d", ansB[i]);
    }
    printf("\n");

    return 0;
}
