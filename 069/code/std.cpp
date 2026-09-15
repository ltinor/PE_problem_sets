#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1000000;

vector<int> primes;
vector<int> phi;
vector<bool> is_composite;

void sieve(int n){
    is_composite.assign(n + 1, false);
    phi.assign(n + 1, 0);
    phi[1] = 1;
    
    for(int i = 2; i <= n; i++){
        if(!is_composite[i]){
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for(int p : primes){
            if((ll)i * p > n) break;
            is_composite[i * p] = true;
            if(i % p == 0){
                phi[i * p] = phi[i] * p;
                break;
            } else {
                phi[i * p] = phi[i] * (p - 1);
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve(MAXN);

    // 预计算最优答案（连续质数乘积）
    // n/φ(n) = Π(p/(p-1))，要最大化这个比值就取尽量多的不同小质数
    // 这样对于每个N可以快速回答
    vector<int> primes_list = {2,3,5,7,11,13,17,19,23,29,31,37};
    
    int N;
    cin >> N;
    // 找 ≤ N 的最大连续质数乘积
    ll best_n = 1;
    ll prod = 1;
    for(int p : primes_list){
        if(prod * p > N) break;
        prod *= p;
        best_n = prod;
    }
    cout << best_n << "\n";
    
    return 0;
}
