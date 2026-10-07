#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool is_prime(int n){
    if(n < 2) return false;
    if(n == 2 || n == 3) return true;
    if(n % 2 == 0) return false;
    for(int i = 3; i * i <= n; i += 2){
        if(n % i == 0) return false;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while(cin >> N){
        // Generate all primes < N
        vector<int> primes;
        for(int p = 2; p < N; p++){
            if(is_prime(p)) primes.push_back(p);
        }
        int m = primes.size();
        
        vector<ll> pref(m + 1, 0);
        for(int i = 0; i < m; i++){
            pref[i + 1] = pref[i] + primes[i];
        }
        
        int best_prime = -1;
        int best_len = 0;
        
        // Double loop: enumerate all start/end pairs
        for(int start = 0; start < m; start++){
            for(int end = start; end < m; end++){
                ll sum = pref[end + 1] - pref[start];
                if(sum >= N) break;
                int len = end - start + 1;
                if(len > best_len && is_prime(sum)){
                    best_len = len;
                    best_prime = sum;
                }
            }
        }
        
        cout << best_prime << " " << best_len << "\n";
    }
    
    return 0;
}
