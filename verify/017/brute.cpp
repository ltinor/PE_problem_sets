#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int ones[] = {0, 3, 3, 5, 4, 4, 3, 5, 5, 4, 3, 6, 6, 8, 8, 7, 7, 9, 8, 8};
const int tens[] = {0, 0, 6, 6, 5, 5, 5, 7, 6, 6};
const int HUNDRED = 7;
const int AND = 3;
const int THOUSAND = 8;

ll count_letters(int n) {
    if (n == 0) return 0;
    if (n <= 19) return ones[n];
    if (n < 100) return tens[n / 10] + ones[n % 10];
    if (n < 1000) {
        int h = n / 100, r = n % 100;
        int base = ones[h] + HUNDRED;
        if (r > 0) base += AND + count_letters(r);
        return base;
    }
    return ones[1] + THOUSAND;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        ll ans = 0;
        for (int i = 1; i <= n; i++) ans += count_letters(i);
        cout << ans << "\n";
    }
}
