#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int MAX_K = 12000;
const int INF = 1e9;

int best[12005]; // best[k] = minimal N for k factors
int kmax;

void dfs(int product, int sum, int start, int depth){
    int k = product - sum + depth;
    if(k <= kmax && k >= 2){
        if(product < best[k]) best[k] = product;
    }
    for(int f = start; product * f <= 2 * kmax; f++){
        dfs(product * f, sum + f, f, depth + 1);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> kmax;

    for(int i = 2; i <= kmax; i++) best[i] = INF;

    dfs(1, 0, 2, 0);

    set<int> used;
    ll total = 0;
    for(int k = 2; k <= kmax; k++){
        if(best[k] < INF && used.find(best[k]) == used.end()){
            used.insert(best[k]);
            total += best[k];
        }
    }

    cout << total << "\n";
}
