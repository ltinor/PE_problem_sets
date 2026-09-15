#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    long long ans = 0;

    for (int x1 = 0; x1 <= N; x1++) {
        for (int y1 = 0; y1 <= N; y1++) {
            if (x1 == 0 && y1 == 0) continue;
            for (int x2 = 0; x2 <= N; x2++) {
                for (int y2 = 0; y2 <= N; y2++) {
                    if (x2 == 0 && y2 == 0) continue;
                    if (x1 == x2 && y1 == y2) continue;

                    if (x1 * x2 + y1 * y2 == 0) { ans++; continue; }
                    if (x1 * (x1 - x2) + y1 * (y1 - y2) == 0) { ans++; continue; }
                    if (x2 * (x2 - x1) + y2 * (y2 - y1) == 0) { ans++; continue; }
                }
            }
        }
    }

    ans /= 2;

    cout << ans << "\n";
    return 0;
}
