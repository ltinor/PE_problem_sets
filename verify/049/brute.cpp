#include<bits/stdc++.h>
using namespace std;

// Simple primality test
bool is_prime(int n){
    if(n < 2) return false;
    if(n == 2 || n == 3) return true;
    if(n % 2 == 0) return false;
    for(int i = 3; i * i <= n; i += 2){
        if(n % i == 0) return false;
    }
    return true;
}

string signature(int n){
    string s = to_string(n);
    sort(s.begin(), s.end());
    return s;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int D;
    cin >> D;
    
    int lo = 1;
    for(int i = 0; i < D - 1; i++) lo *= 10;
    int hi = lo * 10 - 1;
    
    // Collect all D-digit primes
    vector<int> primes;
    for(int p = lo; p <= hi; p++){
        if(is_prime(p)) primes.push_back(p);
    }
    
    map<string, vector<int>> groups;
    for(int p : primes){
        groups[signature(p)].push_back(p);
    }
    
    set<int> known = {1487, 4817, 8147};
    
    for(auto &[sig, gp] : groups){
        int m = gp.size();
        if(m < 3) continue;
        
        for(int i = 0; i < m; i++){
            for(int j = i + 1; j < m; j++){
                int diff = gp[j] - gp[i];
                if(diff == 0) continue;
                int third = gp[j] + diff;
                if(binary_search(gp.begin(), gp.end(), third)){
                    if(D == 4 && known.count(gp[i]) && known.count(gp[j]) && known.count(third)){
                        continue;
                    }
                    cout << gp[i] << gp[j] << third << "\n";
                    return 0;
                }
            }
        }
    }
    
    return 0;
}
