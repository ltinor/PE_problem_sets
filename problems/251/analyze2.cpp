#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Count how many x have 8x-3 with square factors
int main() {
    const ll XMAX = 100000;
    int cnt_sq = 0, cnt_nosq = 0;
    int max_sq = 0;
    for (ll x = 1; x <= XMAX; x++) {
        ll v = 8*x - 3;
        // Find largest square dividing v
        ll sq = 1;
        for (ll d = 2; d*d <= v; d++) {
            int exp = 0;
            while (v % d == 0) { v /= d; exp++; }
            for (int i = 0; i < exp/2; i++) sq *= d;
        }
        // v is now squarefree; if v > 1, it contributes no square factor
        if (sq > 1) {
            cnt_sq++;
            if (sq > max_sq) { max_sq = sq; printf("x=%lld sq=%lld\n", x, sq*sq); }
        } else cnt_nosq++;
    }
    printf("With sq factor: %d, without: %d\n", cnt_sq, cnt_nosq);
    return 0;
}
