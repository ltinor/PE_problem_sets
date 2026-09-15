#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// Brute force: enumerate all possible dice outcomes
// Only works for very small a,c (≤7) due to exponential complexity

int a, b, c, d;
ll win = 0, total = 0;

void dfs2(int idx, int sumC, int sumP){
    if(idx == c){
        if(sumP > sumC) win++;
        total++;
        return;
    }
    for(int face = 1; face <= d; face++){
        dfs2(idx+1, sumC+face, sumP);
    }
}

void dfs1(int idx, int sumP){
    if(idx == a){
        dfs2(0, 0, sumP);
        return;
    }
    for(int face = 1; face <= b; face++){
        dfs1(idx+1, sumP+face);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b >> c >> d;

    win = 0;
    total = 0;
    dfs1(0, 0);

    double prob = (double)win / total;
    cout << fixed << setprecision(7) << prob << "\n";
}
