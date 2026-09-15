#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Sieve to generate primes up to limit
vector<int> get_primes(int limit){
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i * i <= limit; i++){
        if(is_prime[i]){
            for(int j = i * i; j <= limit; j += i){
                is_prime[j] = false;
            }
        }
    }
    vector<int> primes;
    for(int i = 2; i <= limit; i++){
        if(is_prime[i]) primes.push_back(i);
    }
    return primes;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while(cin >> N){
        vector<int> primes = get_primes(N - 1);
        int m = primes.size();
        
        // Prefix sums for O(1) range sum
        vector<ll> pref(m + 1, 0);
        for(int i = 0; i < m; i++){
            pref[i + 1] = pref[i] + primes[i];
        }
        
        // Sieve for primality check (reuse up to N)
        vector<bool> is_prime(N, true);
        is_prime[0] = is_prime[1] = false;
        for(int i = 2; i * i < N; i++){
            if(is_prime[i]){
                for(int j = i * i; j < N; j += i){
                    is_prime[j] = false;
                }
            }
        }
        
        int best_prime = -1;
        int best_len = 0;
        
        // Sliding window: for each start, find the longest sequence with sum < N
        for(int start = 0; start < m; start++){
            ll current_sum = 0;
            for(int end = start; end < m; end++){
                current_sum += primes[end];
                if(current_sum >= N) break;
                int len = end - start + 1;
                if(len > best_len && is_prime[current_sum]){
                    best_len = len;
                    best_prime = current_sum;
                }
            }
        }
        
        cout << best_prime << " " << best_len << "\n";
    }
    
    return 0;
}
