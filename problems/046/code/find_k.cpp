#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    const int MAX = 200000000; // 200M - should find K=3..10
    // Use vector<char> instead of vector<bool> for faster access
    vector<char> is_prime(MAX + 1, 1);
    is_prime[0] = is_prime[1] = 0;
    for (ll i = 2; i * i <= MAX; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= MAX; j += i) {
                is_prime[j] = 0;
            }
        }
    }
    cerr << "Sieve done" << endl;

    // Precompute 2*s^2 values
    vector<int> ts_list;
    for (int s = 1; ; s++) {
        ll ts = 2LL * s * s;
        if (ts >= MAX) break;
        ts_list.push_back((int)ts);
    }
    cerr << "ts_list size: " << ts_list.size() << endl;

    int cnt = 0;
    for (int odd = 9; odd <= MAX; odd += 2) {
        if (odd % 10000001 == 1) cerr << "Processing odd=" << odd << ", cnt=" << cnt << endl;
        if (is_prime[odd]) continue;
        bool ok = false;
        for (int ts : ts_list) {
            if (ts >= odd) break;
            if (is_prime[odd - ts]) {
                ok = true;
                break;
            }
        }
        if (!ok) {
            cnt++;
            cout << "K=" << cnt << ": " << odd << "\n";
            cout.flush();
            if (cnt >= 10) break;
        }
    }
    if (cnt < 10) cout << "Only found " << cnt << " up to " << MAX << "\n";
}
