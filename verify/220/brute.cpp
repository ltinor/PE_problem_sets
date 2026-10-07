#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute: generate the string for small n and simulate

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    ll K;
    cin >> n >> K;
    
    // Brute for n <= 12 only
    if (n > 12) { cout << "0,0\n"; return 0; }
    
    // Generate string
    string s = "Fa";
    for (int i = 0; i < n; i++) {
        string t;
        for (char c : s) {
            if (c == 'a') t += "aRbFR";
            else if (c == 'b') t += "LFaLb";
            else t += c;
        }
        s = t;
    }
    
    ll x = 0, y = 0;
    int d = 0;
    
    for (char c : s) {
        if (c == 'F') {
            if (K > 0) {
                K--;
                x += dx[d];
                y += dy[d];
            }
        } else if (c == 'L') {
            d = (d + 3) % 4;
        } else if (c == 'R') {
            d = (d + 1) % 4;
        }
    }
    
    cout << x << "," << y << "\n";
}
