#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// PE469 brute: Monte Carlo simulation for small N
int simulate(int N) {
    vector<int> state(N, 0); // 0=empty, 1=occupied, -1=blocked
    // Actually simpler: track occupied positions
    set<int> occupied;
    
    while (true) {
        vector<int> avail;
        for (int i = 0; i < N; i++) {
            if (occupied.count(i)) continue;
            int left = (i - 1 + N) % N;
            int right = (i + 1) % N;
            if (occupied.count(left) || occupied.count(right)) continue;
            avail.push_back(i);
        }
        if (avail.empty()) break;
        int pick = avail[rand() % avail.size()];
        occupied.insert(pick);
    }
    return N - occupied.size(); // empty chairs
}

int main() {
    srand(time(0));
    int N, trials;
    cin >> N >> trials;
    ll total_empty = 0;
    for (int t = 0; t < trials; t++) {
        total_empty += simulate(N);
    }
    cout << fixed << setprecision(6) << (ld)total_empty / trials / N << "\n";
}
