#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool is_cube(ll x) {
    ll lo = 1, hi = 1000000;
    while (lo < hi) {
        ll mid = (lo + hi + 1) / 2;
        if (mid * mid * mid <= x) lo = mid;
        else hi = mid - 1;
    }
    return lo * lo * lo == x;
}

int phi[101];
int main() {
    int N = 100;
    vector<int> primes;
    for (int i=2;i<=N;i++) {
        if(!phi[i]) { phi[i]=i-1; primes.push_back(i); }
        for(int p:primes) {
            if(i*p>N) break;
            if(i%p==0) { phi[i*p]=phi[i]*p; break; }
            else phi[i*p]=phi[i]*(p-1);
        }
    }
    phi[1]=1;
    ll sum=0;
    for(int n=2;n<N;n++) {
        if(is_cube((ll)n*phi[n])) {
            sum+=n;
            cout << "n=" << n << " phi=" << phi[n] << " n*phi=" << n*phi[n] << endl;
        }
    }
    cout << "sum=" << sum << endl;
}
