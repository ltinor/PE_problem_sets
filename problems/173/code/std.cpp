#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 173: Hollow square laminae, tiles = a^2 - b^2 = 4k(b+k)
// Count distinct (a,b) pairs with tiles <= N
// N <= 10^6

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    ll total = 0;

    // tiles = 4k(b+k), k >= 1, b >= 1
    // For each k: b ranges from 1 to N/(4k) - k
    // 4k(k+1) <= N  => k <= sqrt(N/4) approximately
    for(int k = 1; ; k++){
        // b >= 1 => 4k(1+k) <= N
        ll min_tiles = 4LL * k * (1 + k);
        if(min_tiles > N) break;

        ll max_b = N / (4LL * k) - k;
        if(max_b >= 1){
            total += max_b;
        }
    }

    cout << total << "\n";
}
