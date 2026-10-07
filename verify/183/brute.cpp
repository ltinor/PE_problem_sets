#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: check all k from 1 to N
// Determine terminating decimal by checking if k (stripped of 2,5) divides N

bool is_terminating(int N, int k) {
    int kk = k;
    while (kk % 2 == 0) kk /= 2;
    while (kk % 5 == 0) kk /= 5;
    return N % kk == 0;
}

int best_k_brute(int N) {
    int best = 1;
    double best_val = log((double)N); // k=1 gives N^1

    for (int k = 2; k <= N; k++) {
        double val = k * log((double)N / k);
        if (val > best_val) {
            best_val = val;
            best = k;
        }
    }
    return best;
}

int D_brute(int N) {
    int k = best_k_brute(N);
    if (is_terminating(N, k)) return -N;
    else return N;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        ll sum = 0;
        for (int i = 5; i <= N; i++) {
            sum += D_brute(i);
        }
        cout << sum << "\n";
    }

    return 0;
}
