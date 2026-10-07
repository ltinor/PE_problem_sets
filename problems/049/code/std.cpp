#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Generate primes up to 10^D - 1 using sieve
vector<bool> sieve(int limit){
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i * i <= limit; i++){
        if(is_prime[i]){
            for(int j = i * i; j <= limit; j += i){
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

// Get digit signature: sorted digits of n as a string
string signature(int n){
    string s = to_string(n);
    // Pad with leading zeros to D digits
    // Since we only generate D-digit numbers, no padding needed
    sort(s.begin(), s.end());
    return s;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int D;
    cin >> D;
    
    int lo = 1, hi = 1;
    for(int i = 0; i < D - 1; i++) lo *= 10;
    for(int i = 0; i < D; i++) hi *= 10;
    hi--;
    
    vector<bool> is_prime = sieve(hi);
    
    // Group D-digit primes by digit signature
    map<string, vector<int>> groups;
    for(int p = lo; p <= hi; p++){
        if(is_prime[p]){
            groups[signature(p)].push_back(p);
        }
    }
    
    // Known example to exclude: 1487, 4817, 8147 (for D=4)
    set<int> known = {1487, 4817, 8147};
    
    // For each group with at least 3 primes, check arithmetic progressions
    for(auto &[sig, primes] : groups){
        int m = primes.size();
        if(m < 3) continue;
        
        for(int i = 0; i < m; i++){
            for(int j = i + 1; j < m; j++){
                int diff = primes[j] - primes[i];
                if(diff == 0) continue;
                int third = primes[j] + diff;
                // Check if third is in the group
                if(binary_search(primes.begin(), primes.end(), third)){
                    vector<int> tri = {primes[i], primes[j], third};
                    // Exclude known example
                    if(D == 4 && known.count(tri[0]) && known.count(tri[1]) && known.count(tri[2])){
                        continue;
                    }
                    // Output concatenated 3*D digits
                    cout << tri[0] << tri[1] << tri[2] << "\n";
                    return 0;
                }
            }
        }
    }
    
    return 0;
}
