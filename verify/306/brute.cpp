#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    // Brute force: compute Grundy numbers O(N^2)
    // Works for N up to ~5000
    vector<int> g(N + 1, 0);
    for (int n = 2; n <= N; n++) {
        set<int> s;
        for (int i = 0; i <= n - 2; i++) {
            s.insert(g[i] ^ g[n - i - 2]);
        }
        int mex = 0;
        while (s.count(mex)) mex++;
        g[n] = mex;
    }

    ll ans = 0;
    for (ll n = 1; n <= N; n++) {
        if (g[n] != 0) ans++;
    }
    cout << ans << "\n";
    return 0;
}
