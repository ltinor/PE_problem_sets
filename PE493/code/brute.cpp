#include<bits/stdc++.h>
using namespace std;
using ld = long double;
using ll = long long;

// Brute force for PE493: Monte Carlo simulation for small cases

int main() {
    string query;
    getline(cin, query);
    istringstream ss(query);
    vector<int> params;
    int x;
    while (ss >> x) params.push_back(x);
    
    if (params.size() < 4) {
        cout << "0\n";
        return 0;
    }
    
    int total = params[0], per = params[1], colors = params[2], pick = params[3];
    
    // Monte Carlo simulation
    int trials = 100000;
    if (total <= 20) trials = 500000;
    
    ll sum_distinct = 0;
    vector<int> balls;
    for (int c = 0; c < colors; c++)
        for (int j = 0; j < per; j++)
            balls.push_back(c);
    
    mt19937 rng(time(0));
    for (int t = 0; t < trials; t++) {
        shuffle(balls.begin(), balls.end(), rng);
        set<int> seen;
        for (int i = 0; i < pick; i++) seen.insert(balls[i]);
        sum_distinct += seen.size();
    }
    
    ld ev = (ld)sum_distinct / trials;
    cout << fixed << setprecision(6) << ev << "\n";
}
