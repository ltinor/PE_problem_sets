#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE335: Gathering Beans
// x bowls in circle, each with 1 bean initially.
// Maintain bean counts in array, and track "non_one_count" = bowls != 1.
// Operation: at pos, b = beans[pos], set to 0, distribute b beans starting pos+1.
// Continue until non_one_count == 0 (all bowls have 1 bean).

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x;
    cin >> x;
    
    vector<int> beans(x, 1);
    int pos = 0;
    ll steps = 0;
    int non_one = 0; // Initially all are 1, so non_one = 0
    
    auto update = [&](int idx, int delta) {
        int old = beans[idx];
        beans[idx] += delta;
        int nw = beans[idx];
        if (old == 1 && nw != 1) non_one++;
        if (old != 1 && nw == 1) non_one--;
    };
    
    while (true) {
        int b = beans[pos];
        
        // Set beans[pos] to 0
        update(pos, -b);
        
        steps++;
        
        // Distribute b beans starting from pos+1
        if (b > 0) {
            if (b >= x) {
                // Each bowl gets at least b/x, remainder distributed
                int each = b / x;
                int rem = b % x;
                for (int i = 0; i < x; i++) update(i, each);
                for (int j = 1; j <= rem; j++) update((pos + j) % x, 1);
                pos = (pos + b) % x;
            } else {
                for (int j = 1; j <= b; j++) update((pos + j) % x, 1);
                pos = (pos + b) % x;
            }
        }
        
        if (non_one == 0) break;
    }
    
    cout << steps << "\n";
    
    return 0;
}
