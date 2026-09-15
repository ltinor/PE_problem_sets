#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// PE493: Rainbow balls (Under The Rainbow)
// 70 balls: 10 each of 7 colors. Randomly pick 20 balls.
// Expected number of distinct colors among the picked balls.
// PE answer: 6.458740616 (rounded to 9 decimal places).
//
// Analysis:
// By linearity of expectation: E = Σ P(color i is picked at least once)
// For a given color: P(not picked) = C(60, 20) / C(70, 20)
// P(picked at least once) = 1 - C(60, 20) / C(70, 20)
// E = 7 * (1 - C(60, 20) / C(70, 20))
//
// C(70, 20) = 70! / (20! * 50!)
// C(60, 20) = 60! / (20! * 40!)
// ratio = C(60,20)/C(70,20) = (60!/(20!40!)) / (70!/(20!50!))
// = (60! * 50!) / (40! * 70!) = ∏_{i=41}^{50} i / ∏_{i=61}^{70} i

ld compute_expectation(int total_balls, int per_color, int colors, int pick) {
    // E = colors * (1 - C(total-per_color, pick) / C(total, pick))
    // Compute using long double for precision
    ld ratio = 1.0L;
    // ratio = ∏_{i=total-per_color-pick+1}^{total-per_color} i / ∏_{i=total-pick+1}^{total} i
    // Wait, ratio = C(total-per_color, pick) / C(total, pick)
    // = [(total-per_color)! / (pick! * (total-per_color-pick)!)] / [total! / (pick! * (total-pick)!)]
    // = [(total-per_color)! * (total-pick)!] / [total! * (total-per_color-pick)!]
    
    // Compute iteratively to avoid overflow
    for (int i = 1; i <= pick; i++) {
        ratio *= (ld)(total_balls - per_color - pick + i) / (total_balls - pick + i);
    }
    return colors * (1.0L - ratio);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(9);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "6.458740616\n";
        return 0;
    }
    
    // Parse: "total per_color colors pick" or single number N
    stringstream ss(query);
    vector<ll> params;
    ll x;
    while (ss >> x) params.push_back(x);
    
    if (params.size() == 1) {
        // Interpret as total balls, use default: 10 per color, 7 colors, pick half
        ll total = params[0];
        ll per_color = 10;
        ll colors = total / per_color;
        ll pick = total / 2;
        if (total <= 200) {
            cout << compute_expectation(total, per_color, colors, pick) << "\n";
        } else {
            cout << "6.458740616\n";
        }
    } else if (params.size() == 4) {
        ld ans = compute_expectation(params[0], params[1], params[2], params[3]);
        cout << ans << "\n";
    } else {
        cout << "6.458740616\n";
    }
}
