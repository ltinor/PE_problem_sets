#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE473 brute: enumerate numbers, convert to phigital, check palindrome
const long double phi = (1.0L + sqrtl(5.0L)) / 2.0L;

string to_phigital(ll N) {
    long double rem = N;
    vector<int> digits(100, 0);
    int max_k = 0;
    while (powl(phi, max_k+1) <= N+1e-12L) max_k++;
    int offset = 50;
    for (int k = max_k; k >= -40 && rem > 1e-12L; k--) {
        long double pk = powl(phi, k);
        if (k+1 <= max_k && digits[offset+k+1] == 1) continue;
        if (pk <= rem+1e-12L) {
            digits[offset+k] = 1;
            rem -= pk;
        }
    }
    string s;
    bool started = false;
    for (int i = offset+max_k; i >= 0; i--) {
        if (i == offset-1) { s += '.'; started = true; }
        if (!started && !digits[i]) continue;
        started = true;
        s += (digits[i] ? '1' : '0');
    }
    return s;
}

bool is_pal(const string& s) {
    int n = s.size();
    for (int i = 0; i < n/2; i++)
        if (s[i] != s[n-1-i]) return false;
    return true;
}

int main() {
    ll N; cin >> N;
    ll sum = 0;
    for (ll x = 1; x <= N; x++) {
        if (is_pal(to_phigital(x))) sum += x;
    }
    cout << sum << "\n";
}
