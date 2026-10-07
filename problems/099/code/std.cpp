#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int best_idx = 1;
    double best_val = 0.0;

    for (int i = 1; i <= N; i++) {
        int a, b;
        cin >> a >> b;
        double val = b * log((double)a);
        if (val > best_val) {
            best_val = val;
            best_idx = i;
        }
    }

    cout << best_idx << "\n";
    return 0;
}
