#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// Brute force for PE499: Monte Carlo simulation

int main() {
    string query;
    getline(cin, query);
    stringstream ss(query);
    int S, C, T;
    ss >> S >> C >> T;
    
    if (T > 50) {
        cout << "0\n";
        return 0;
    }
    
    int trials = 500000;
    int wins = 0;
    
    for (int t = 0; t < trials; t++) {
        int money = S;
        int max_steps = 1000;
        for (int step = 0; step < max_steps; step++) {
            if (money >= T) { wins++; break; }
            if (money < C) break; // can't afford to play
            money -= C;
            // Flip until heads
            int k = 1;
            while (rand() % 2 == 0) k++; // tails then heads
            money += (1 << k);
            if (money >= T) { wins++; break; }
        }
    }
    
    ld prob = (ld)wins / trials;
    cout << fixed << setprecision(8) << prob << "\n";
}
