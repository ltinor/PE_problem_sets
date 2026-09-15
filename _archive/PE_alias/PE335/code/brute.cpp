#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE335 brute: naive simulation for small x

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x;
    cin >> x;
    
    vector<int> beans(x, 1);
    int pos = 0;
    ll steps = 0;
    
    while (true) {
        int b = beans[pos];
        beans[pos] = 0;
        steps++;
        
        for (int j = 1; j <= b; j++) {
            beans[(pos + j) % x]++;
        }
        pos = (pos + b) % x;
        
        // Check all ones
        bool ok = true;
        for (int i = 0; i < x; i++) {
            if (beans[i] != 1) { ok = false; break; }
        }
        if (ok) break;
    }
    
    cout << steps << "\n";
    
    return 0;
}
