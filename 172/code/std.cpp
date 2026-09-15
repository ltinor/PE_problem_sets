#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 172: count D-digit numbers where each digit appears at most 3 times
// D <= 18

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int D;
    cin >> D;

    if(D < 1 || D > 18) return 1;

    // Generate all possible distributions of 10 digits (0-3 each)
    // Total count = sum over valid distributions of:
    //   total_arrangements - arrangements_with_leading_zero
    // where arrangements = D! / (c0! * c1! * ... * c9!)

    // Precompute factorials
    vector<ll> fact(D + 1, 1);
    for(int i = 1; i <= D; i++) fact[i] = fact[i-1] * i;

    // Use recursion/DFS to enumerate all 10-tuples
    ll total = 0;

    function<void(int, int, ll, ll)> dfs = [&](int digit, int used, ll prod_fact, int c0){
        if(digit == 10){
            if(used == D){
                // Valid distribution
                ll arrangements = fact[D] / prod_fact;
                total += arrangements;
                // Subtract cases where leading digit is 0
                if(c0 > 0){
                    // First position fixed as 0, remaining D-1 positions
                    // Digit 0 now has c0-1 remaining
                    ll prod_fact_leading0 = prod_fact / c0; // remove one factor of c0!
                    // Actually prod_fact includes c0!, so we need: (c0-1)! * prod_other
                    // prod_fact / c0 gives (c0-1)! * prod_other
                    ll arrangements_zero = fact[D-1] / prod_fact_leading0;
                    total -= arrangements_zero;
                }
            }
            return;
        }
        int max_cnt = min(3, D - used);
        for(int cnt = 0; cnt <= max_cnt; cnt++){
            ll new_prod = prod_fact * fact[cnt];
            int new_c0 = (digit == 0) ? cnt : c0;
            dfs(digit + 1, used + cnt, new_prod, new_c0);
        }
    };

    dfs(0, 0, 1, 0);

    cout << total << "\n";
}
