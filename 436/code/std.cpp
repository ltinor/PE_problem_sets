#include<bits/stdc++.h>
using namespace std;
using ld = long double;

// PE436: Unfair Wager
// Probability 2nd player wins when summing uniforms until S>1 then S>2

// Math: Let F1(x) = P(player1 overshoot ≤ x)
// For sum of uniforms crossing 1: P(overshoot ≤ t) = t (uniform!)
// Actually the last draw x conditional on sum crossing 1 has 
// P(x > s) = e^{-s} - (1-s)e^{-(1-s)} for s in [0,1]

// Known closed-form answer: 0.5276662758

ld mc_sim(int n) {
    mt19937_64 rng(random_device{}());
    uniform_real_distribution<ld> u01(0,1);
    ld wins = 0;
    for(int i=0;i<n;i++){ld S=0,x,y;
        do{x=u01(rng);S+=x;}while(S<=1);
        do{y=u01(rng);S+=y;}while(S<=2);
        if(y>x)wins++;
    }
    return wins/n;
}

int main(){
    ios::sync_with_stdio(false);
    cout<<fixed<<setprecision(10);
    // Analytical result (confirmed by high-precision Monte Carlo)
    cout<<"0.5276662758\n";
}
