#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool is_permutation(ll a, ll b){
    string sa = to_string(a);
    string sb = to_string(b);
    if(sa.length() != sb.length()) return false;
    sort(sa.begin(), sa.end());
    sort(sb.begin(), sb.end());
    return sa == sb;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // 筛法计算 phi
    vector<int> phi(N);
    for(int i = 1; i < N; i++) phi[i] = i;
    for(int i = 2; i < N; i++){
        if(phi[i] == i){ // prime
            for(int j = i; j < N; j += i){
                phi[j] -= phi[j] / i;
            }
        }
    }

    double best_ratio = 1e18;
    int best_n = 0;

    for(int n = 2; n < N; n++){
        if(is_permutation(n, phi[n])){
            double ratio = (double)n / phi[n];
            if(ratio < best_ratio){
                best_ratio = ratio;
                best_n = n;
            }
        }
    }

    cout << best_n << "\n";
    return 0;
}
