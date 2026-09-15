#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute: simulate one by one using priority queue for small N

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    if (N > 100000) { cout << "0\n"; return 0; }
    if (N <= 1) { cout << "0\n"; return 0; }
    
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    pq.push(0);
    
    for (int i = 1; i < N; i++) {
        ll c = pq.top(); pq.pop();
        pq.push(c + 1);
        pq.push(c + 4);
    }
    
    ll total = 0;
    while (!pq.empty()) {
        total += pq.top(); pq.pop();
    }
    
    cout << total << "\n";
}
