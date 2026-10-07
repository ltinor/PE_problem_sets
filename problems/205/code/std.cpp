#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// PE 205 — Dice Game
// Peter: a dice, each b-sided (1..b)
// Colin: c dice, each d-sided (1..d)
// Compute probability Peter wins, rounded to 7 decimal places

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c, d;
    cin >> a >> b >> c >> d;

    int maxP = a * b;
    int maxC = c * d;

    // dpP[s] = number of ways Peter gets sum s
    vector<ll> dpP(maxP + 1, 0);
    dpP[0] = 1;
    for(int i = 0; i < a; i++){
        vector<ll> ndp(maxP + 1, 0);
        for(int s = 0; s <= maxP; s++){
            if(dpP[s] == 0) continue;
            for(int face = 1; face <= b; face++){
                ndp[s + face] += dpP[s];
            }
        }
        dpP = move(ndp);
    }

    // dpC[s] = number of ways Colin gets sum s
    vector<ll> dpC(maxC + 1, 0);
    dpC[0] = 1;
    for(int i = 0; i < c; i++){
        vector<ll> ndp(maxC + 1, 0);
        for(int s = 0; s <= maxC; s++){
            if(dpC[s] == 0) continue;
            for(int face = 1; face <= d; face++){
                ndp[s + face] += dpC[s];
            }
        }
        dpC = move(ndp);
    }

    // Count winning cases: Peter's sum > Colin's sum
    // Use prefix sums over Colin's distribution
    vector<ll> prefC(maxC + 1, 0);
    for(int s = 0; s <= maxC; s++){
        prefC[s] = dpC[s] + (s > 0 ? prefC[s-1] : 0);
    }

    ll win = 0;
    for(int sp = a; sp <= maxP; sp++){
        if(dpP[sp] == 0) continue;
        // Colin's sum is strictly less than sp
        // max Colin sum < sp is sp-1, but capped at maxC
        int maxCsum = min(sp - 1, maxC);
        if(maxCsum >= 0){
            win += dpP[sp] * prefC[maxCsum];
        }
    }

    ll total = 1;
    for(int i = 0; i < a; i++) total *= b;
    for(int i = 0; i < c; i++) total *= d;

    double prob = (double)win / total;
    cout << fixed << setprecision(7) << prob << "\n";
}
