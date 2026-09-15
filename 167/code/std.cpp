#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Ulam sequence: U(1)=a, U(2)=b. Each subsequent term is smallest integer
// representable in EXACTLY ONE way as sum of two distinct previous terms.

vector<ll> ulam(ll a, ll b, int K) {
    vector<ll> seq = {a, b};
    ll cur = b + 1;
    while((int)seq.size() < K) {
        map<ll,int> cnt;
        int sz = seq.size();
        for(int i=0; i<sz; i++)
            for(int j=i+1; j<sz; j++) {
                ll s = seq[i] + seq[j];
                if(s > cur) cnt[s]++;
            }
        // Find smallest > last term with count==1
        bool found = false;
        for(auto& p : cnt) {
            if(p.second == 1 && p.first > seq.back()) {
                seq.push_back(p.first);
                found = true;
                break;
            }
        }
        if(!found) break; // shouldn't happen
    }
    return seq;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int K; cin >> K;
    // For n=2..10, compute U(2,2n+1)_K and sum
    ll sum = 0;
    for(int n=2; n<=10; n++) {
        auto seq = ulam(2, 2*n+1, K);
        if((int)seq.size() >= K) sum += seq[K-1];
    }
    cout << sum << "\n";
}
