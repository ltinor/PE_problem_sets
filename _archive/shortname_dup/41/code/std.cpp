#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool is_prime(int x) {
    if (x < 2) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;
    for (int i = 3; i * i <= x; i += 2) {
        if (x % i == 0) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // generate digits 1..N
    vector<int> digits(N);
    for (int i = 0; i < N; i++) digits[i] = N - i; // descending: N, N-1, ..., 1

    // try all permutations in descending order
    do {
        // build number from digits
        ll num = 0;
        for (int d : digits) num = num * 10 + d;
        if (is_prime(num)) {
            cout << num << "\n";
            return 0;
        }
    } while (prev_permutation(digits.begin(), digits.end()));

    cout << -1 << "\n";
    return 0;
}
