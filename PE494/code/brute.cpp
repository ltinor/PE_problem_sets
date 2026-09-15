#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force for PE494: enumerate all n ≤ N, check all patterns

int main() {
    string query;
    getline(cin, query);
    stringstream ss(query);
    ll K, N;
    ss >> K >> N;
    
    if (K > 8 || N > 5000) {
        cout << "0\n";
        return 0;
    }
    
    ll total = 0;
    for (ll n = 1; n <= N; n++) {
        for (ll pat = 0; pat < (1LL << K); pat++) {
            ll cur = n;
            bool match = true;
            for (int i = 0; i < K; i++) {
                bool odd = (pat >> i) & 1;
                if (odd) {
                    if (cur % 2 == 0) { match = false; break; }
                    cur = 3 * cur + 1;
                } else {
                    if (cur % 2 != 0) { match = false; break; }
                    cur /= 2;
                }
            }
            if (match) total++;
        }
    }
    cout << total << "\n";
}
