#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool is_permutation(int a, int b){
    vector<int> cnt(10, 0);
    while(a > 0){ cnt[a % 10]++; a /= 10; }
    while(b > 0){ cnt[b % 10]--; b /= 10; }
    for(int i = 0; i < 10; i++) if(cnt[i] != 0) return false;
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // 暴力：直接用欧拉筛法计算 phi（实际上和 std 一样，但我们用独立写法）
    vector<int> phi(N);
    for(int i = 1; i < N; i++) phi[i] = i;
    for(int i = 2; i < N; i++){
        if(phi[i] == i){
            for(int j = i; j < N; j += i){
                phi[j] -= phi[j] / i;
            }
        }
    }

    double best_ratio = 1e18;
    int best_n = 0;

    for(int n = 2; n < N; n++){
        int p = phi[n];
        if(is_permutation(n, p)){
            double r = (double)n / p;
            if(r < best_ratio){
                best_ratio = r;
                best_n = n;
            }
        }
    }

    cout << best_n << "\n";
    return 0;
}
