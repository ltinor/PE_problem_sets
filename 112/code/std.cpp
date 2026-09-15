#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool is_increasing(ll x) {
    int last = 10;
    while (x > 0) {
        int d = x % 10;
        if (d > last) return false;
        last = d;
        x /= 10;
    }
    return true;
}

bool is_decreasing(ll x) {
    int last = -1;
    while (x > 0) {
        int d = x % 10;
        if (d < last) return false;
        last = d;
        x /= 10;
    }
    return true;
}

bool is_bouncy(ll x) {
    return !is_increasing(x) && !is_decreasing(x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int P;
    cin >> P;

    ll bouncy = 0;
    ll n = 0;
    while (true) {
        n++;
        if (is_bouncy(n)) bouncy++;
        // bouncy / n * 100 >= P → bouncy * 100 >= P * n
        if (bouncy * 100 >= (ll)P * n) {
            cout << n << "\n";
            break;
        }
    }
    return 0;
}
