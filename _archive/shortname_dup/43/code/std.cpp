#include<bits/stdc++.h>
using namespace std;
#define ll long long

int primes[] = {2, 3, 5, 7, 11, 13, 17};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ignore input
    int dummy;
    cin >> dummy;

    vector<int> digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ll total = 0;

    do {
        if (digits[0] == 0) continue; // d1 can't be 0 for a 10-digit number

        bool ok = true;
        for (int i = 0; i < 7; i++) {
            int num = digits[i + 1] * 100 + digits[i + 2] * 10 + digits[i + 3];
            if (num % primes[i] != 0) {
                ok = false;
                break;
            }
        }

        if (ok) {
            ll val = 0;
            for (int d : digits) val = val * 10 + d;
            total += val;
        }
    } while (next_permutation(digits.begin(), digits.end()));

    cout << total << "\n";
    return 0;
}
