#include<bits/stdc++.h>
using namespace std;
#define ll long long

const ll MOD = 1000000000;

// brute: enumerate all n < 10^D for small D (D <= 7)
int digit_square_sum(ll n){
    int s = 0;
    while(n > 0){
        int d = n % 10;
        s += d * d;
        n /= 10;
    }
    return s;
}

bool is_square(int x){
    int r = (int)sqrt(x);
    return r * r == x;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int D;
    cin >> D;

    ll limit = 1;
    for(int i = 0; i < D; i++) limit *= 10;

    ll total = 0;
    for(ll n = 1; n < limit; n++){
        int s = digit_square_sum(n);
        if(is_square(s)){
            total = (total + n) % MOD;
        }
    }

    cout << total << "\n";
}
