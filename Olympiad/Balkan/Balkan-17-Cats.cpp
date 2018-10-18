/**
 * Balkan OI '17 - Cats
 *
 * First, handle trivial cases (when there are only no cats/dogs/lions) separately.
 *
 * Notice that if you move a cat or a dog, you can easily merge it into some existing segments of cats/dogs.
 * The only exception is when you move all cats/dogs in which case you can't rely on existing segments - we will deal with this later.
 * 
 * We will determine the final sequence starting from the first position to last position using dynamic programming.
 * Our DP state contains 1) current index, 2) number of lions we've used and 3) animal placed in previous position.
 *
 * The choices are 1) let this cat/dog stay in place, 2) move this cat/dog to some other segments (we don't care where we move them to),
 * 3) place a lion here (either use one in this position, or move it from somewhere else).
 * For the third choice, we check/increment the number of lions accordingly. If we've used all, ignore any lions we find later in the sequence.
 *
 * This is not enough. For the case 0 0 2 0 1 0 2 0 0, we can't simply move 1 out and consider it merged with some other 1-segments,
 * because there are no other segments to merge with. To deal with this, we will introduce two more boolean variables
 * to store whether we've found or created a cat subsegment and a dog subsegment. In the end, both must be set to True to be valid.
 * We can set boolean to True when we've found and placed the actual cat/dog, or decide to create a cat/dog segment right after a lion.
 * (Or right before the whole sequence).
 *
 * In order for the program to satisfy the memory limit, keep the last two rows of DP only.
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 5010;

int A[N], C[3];
int dp[2][N][3][2][2];

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {

        int n;
        scanf("%d", &n);
        C[0] = C[1] = C[2] = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &A[i]);
            ++C[A[i]];
        }
        if (C[0] == 0 || C[1] == 0 || C[2] == 0) {
            if (C[0] > 0 && C[1] > 0)
                printf("-1\n");
            else
                printf("0\n");
            continue;
        }

        for (int j = C[2]; j >= 0; --j) {
            for (int k = 0; k < 3; ++k) {
                for (int ac = 0; ac < 2; ++ac) {
                    for (int ad = 0; ad < 2; ++ad) {
                        int x = ac, y = ad;
                        if (k == 0) x = 1;
                        if (k == 1) y = 1;
                        if (k == 2) {
                            if (x == 0) x = 1;
                            else y = 1;
                        }
                        dp[(n+1)&1][j][k][ac][ad] = x == 0 || y == 0 ? N : 0;
                    }
                }
            }
        }
        for (int i = n; i >= 1; --i) {
            int x = i&1;
            int y = x^1;
            for (int j = C[2]; j >= 0; --j) {
                for (int k = 0; k < 3; ++k) {
                    for (int ac = 0; ac < 2; ++ac) {
                        for (int ad = 0; ad < 2; ++ad) {
                            int &ans = dp[x][j][k][ac][ad];
                            ans = N;
                            // if previous one is lion, can accept either dog or cat from elsewhere
                            if (k == 2) {
                                ans = min(ans, dp[x][j][0][1][ad]);
                                ans = min(ans, dp[x][j][1][ac][1]);
                            }
                            // if not dealing with lion
                            if (A[i] != 2) {
                                // stay with this one (must be suitable)
                                if (k == 2 || k == A[i]) {
                                    if (A[i] == 0) // accept dog/cat
                                        ans = min(ans, dp[y][j][A[i]][1][ad]);
                                    else
                                        ans = min(ans, dp[y][j][A[i]][ac][1]);
                                }
                                // move this one elsewhere
                                ans = min(ans, 1+dp[y][j][k][ac][ad]);
                            }
                            // if dealing with lion
                            if (A[i] == 2) {
                                // use this free lion
                                if (j+1 <= C[2])
                                    ans = min(ans, dp[y][j+1][2][ac][ad]);
                                // skip this lion
                                ans = min(ans, dp[y][j][k][ac][ad]);
                            }
                            // use lion from elsewhere
                            if (j+1 <= C[2])
                                ans = min(ans, 1+dp[y][j+1][2][ac][ad]);
                        }
                    }
                }
            }
        }
        printf("%d\n", dp[1][0][2][0][0]);

    }

    return 0;
}
