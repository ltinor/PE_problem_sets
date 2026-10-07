#include<bits/stdc++.h>
using namespace std;

// Count distinct prime factors of n by trial division
int count_distinct_primes(int n){
    int cnt = 0;
    for(int p = 2; p * p <= n; p++){
        if(n % p == 0){
            cnt++;
            while(n % p == 0) n /= p;
        }
    }
    if(n > 1) cnt++;
    return cnt;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int K;
    cin >> K;
    
    int n = 2;
    while(true){
        bool ok = true;
        for(int i = 0; i < K; i++){
            if(count_distinct_primes(n + i) != K){
                ok = false;
                break;
            }
        }
        if(ok){
            cout << n << "\n";
            return 0;
        }
        n++;
    }
    
    return 0;
}
