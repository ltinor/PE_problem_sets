#include<bits/stdc++.h>
using namespace std;
#define ll long long

// brute: enumerate all (a,b) pairs with a > b, same parity, a^2 - b^2 <= N
// Works for small N

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    ll total = 0;

    for(int a = 2; ; a++){
        ll a2 = (ll)a * a;
        // need b < a, same parity, a^2 - b^2 <= N
        // b starts from a-2 down to (parity allows)
        int b_start = a - 2;
        if(b_start >= 1){
            for(int b = b_start; b >= 1; b -= 2){
                if(a2 - (ll)b * b > N) break;
                total++;
            }
        }
        // Check if even the smallest possible gives > N
        // smallest a^2 - b^2 with b = a-2 is a^2 - (a-2)^2 = 4a-4
        // or b=1 if parity matches
        // simplest: if a=2, b none. a=3, b=1: 9-1=8
        // For a > N/4+1, the minimum is > N
        if(a > 2 && a2 - (ll)(a-2)*(a-2) > N){
            // But we might still find some with b=1? No, b=a-2 is the smallest difference
            // Actually: a^2 - (a-2)^2 = 4a-4. If this > N, no more solutions for this a or larger
            if(4LL*a - 4 > N) break;
        }
    }

    cout << total << "\n";
}
