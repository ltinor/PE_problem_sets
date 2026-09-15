#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1000000;

vector<int> phi;

void compute_phi(int n){
    phi.assign(n + 1, 0);
    for(int i = 1; i <= n; i++) phi[i] = i;
    for(int i = 2; i <= n; i++){
        if(phi[i] == i){ // prime
            for(int j = i; j <= n; j += i){
                phi[j] -= phi[j] / i;
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    compute_phi(MAXN);

    int N;
    cin >> N;
    double best_ratio = 0;
    int best_n = 1;
    
    for(int i = 1; i <= N; i++){
        double ratio = (double)i / phi[i];
        if(ratio > best_ratio){
            best_ratio = ratio;
            best_n = i;
        }
    }
    
    cout << best_n << "\n";
    
    return 0;
}
