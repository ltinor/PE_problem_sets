#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool is_prime(int x) {
    if (x <= 1) return false;
    if (x <= 3) return true;
    if (x % 2 == 0 || x % 3 == 0) return false;
    for (int i = 5; i * i <= x; i += 6) {
        if (x % i == 0 || x % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    int N;
    cin >> N;

    // create initial permutation: digits N, N-1, ..., 1
    vector<int> digits(N);
    for (int i = 0; i < N; i++) digits[i] = N - i;

    // try all permutations from largest to smallest
    do {
        int num = 0;
        for (int i = 0; i < N; i++) num = num * 10 + digits[i];
        if (is_prime(num)) {
            cout << num << "\n";
            return 0;
        }
    } while (prev_permutation(digits.begin(), digits.end()));

    cout << -1 << "\n";
    return 0;
}
