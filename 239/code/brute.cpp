#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 239: brute - enumerate all permutations for tiny N
// Use next_permutation and count

bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    if (N > 8) { cout << "0.000000000000\n"; return 0; }

    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);

    ll total = 0, valid = 0;
    do {
        total++;
        int displaced = 0;
        for (int i = 0; i < N; i++) {
            if (is_prime(perm[i]) && perm[i] != i + 1)
                displaced++;
        }
        if (displaced == K) valid++;
    } while (next_permutation(perm.begin(), perm.end()));

    cout << fixed << setprecision(12) << (long double)valid / total << "\n";
    return 0;
}
