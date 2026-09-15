#include<bits/stdc++.h>
using namespace std;

#define ll long long

// Brute force: same formula as std but simpler for verification
ll cross_hatched(int w, int h) {
    ll regular = (ll)w * (w + 1) / 2 * h * (h + 1) / 2;

    int K = w + h + 1;
    ll diag = 0;

    for (int k1 = 0; k1 < K; k1++) {
        for (int k2 = k1 + 1; k2 < K; k2++) {
            int d1 = k1 - h;
            int d2 = k2 - h;

            for (int l1 = 0; l1 < K; l1++) {
                for (int l2 = l1 + 1; l2 < K; l2++) {
                    int s1 = l1;
                    int s2 = l2;

                    int x1 = d1 + s1, y1 = s1 - d1;
                    int x2 = d1 + s2, y2 = s2 - d1;
                    int x3 = d2 + s1, y3 = s1 - d2;
                    int x4 = d2 + s2, y4 = s2 - d2;

                    if (x1 >= 0 && x1 <= 2*w && y1 >= 0 && y1 <= 2*h &&
                        x2 >= 0 && x2 <= 2*w && y2 >= 0 && y2 <= 2*h &&
                        x3 >= 0 && x3 <= 2*w && y3 >= 0 && y3 <= 2*h &&
                        x4 >= 0 && x4 <= 2*w && y4 >= 0 && y4 <= 2*h) {
                        diag++;
                    }
                }
            }
        }
    }

    return regular + diag;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int W, H;
    cin >> W >> H;

    ll total = 0;
    for (int w = 1; w <= W; w++) {
        for (int h = 1; h <= H; h++) {
            total += cross_hatched(w, h);
        }
    }

    cout << total << "\n";
    return 0;
}
