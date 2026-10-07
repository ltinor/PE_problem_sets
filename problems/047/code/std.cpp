#include<bits/stdc++.h>
using namespace std;

// Sieve variant: count distinct prime factors for each number
// Then find first K consecutive numbers each with K distinct prime factors

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int K;
    cin >> K;
    
    // Upper bound: for K=4, answer is 134043; use generous bound
    int limit = 200000;
    vector<int> distinct_primes(limit + 1, 0);
    
    // Sieve to count distinct prime factors
    for(int i = 2; i <= limit; i++){
        if(distinct_primes[i] == 0){ // i is prime
            for(int j = i; j <= limit; j += i){
                distinct_primes[j]++;
            }
        }
    }
    
    // Find first K consecutive numbers with K distinct prime factors
    int consecutive = 0;
    for(int n = 2; n <= limit; n++){
        if(distinct_primes[n] == K){
            consecutive++;
            if(consecutive == K){
                cout << n - K + 1 << "\n";
                return 0;
            }
        } else {
            consecutive = 0;
        }
    }
    
    return 0;
}
