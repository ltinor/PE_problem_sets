#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: enumerate all K-subsets, count sum frequencies
// Only works for small N (≤20)

int N, K;
vector<ll> sq;
map<ll, int> freq;

void dfs(int idx, int cnt, ll sum){
    if(cnt == K){
        freq[sum]++;
        return;
    }
    if(idx >= N) return;
    if(N - idx < K - cnt) return; // not enough elements left
    // take
    dfs(idx+1, cnt+1, sum + sq[idx]);
    // skip
    dfs(idx+1, cnt, sum);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;
    sq.resize(N);
    for(int i = 0; i < N; i++) sq[i] = (ll)(i+1)*(i+1);

    freq.clear();
    dfs(0, 0, 0);

    ll ans = 0;
    for(auto &p : freq){
        if(p.second == 1) ans += p.first;
    }
    cout << ans << "\n";
}
