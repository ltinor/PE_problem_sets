#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 321: Sum of first K values of n where M(n) = n(n+2) is triangle number
// M(n) = n*(n+2) is triangle number means n*(n+2) = t*(t+1)/2
// => 2n(n+2) = t(t+1) => (4n+4)^2 - 2(2t+1)^2 = 14
// This is Pell-like: X^2 - 2Y^2 = 14 with X = 4n+4, Y = 2t+1
// 
// Two fundamental solution families:
// Family A: X0=4, Y0=1 → n=0 (discard), then n=3, 22, 133, ...
// Family B: X0=8, Y0=5 → n=1, 10, 63, 380, ...
// 
// Recurrence: (X_{k+1}, Y_{k+1}) = (3X_k + 4Y_k, 2X_k + 3Y_k)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    // Use __int128 for safety
    __int128 sum = 0;

    // Generate from both families using recurrence
    // Family A: (X,Y) = (4,1) initially
    __int128 Xa = 4, Ya = 1;
    // Family B: (X,Y) = (8,5) initially
    __int128 Xb = 8, Yb = 5;

    int cnt = 0;
    
    // Generate all terms by merging the two families
    // Use two generators and take the smaller n each time
    // n = (X-4)/4 must be integer
    
    // Advance family A once to skip n=0
    {
        __int128 Xan = 3*Xa + 4*Ya;
        __int128 Yan = 2*Xa + 3*Ya;
        Xa = Xan; Ya = Yan; // (16, 11) → n=3
    }

    while (cnt < K) {
        __int128 na = (Xa - 4) / 4;
        __int128 nb = (Xb - 4) / 4;

        if (na < nb) {
            sum += na;
            cnt++;
            // Advance family A
            __int128 Xan = 3*Xa + 4*Ya;
            __int128 Yan = 2*Xa + 3*Ya;
            Xa = Xan; Ya = Yan;
        } else {
            sum += nb;
            cnt++;
            // Advance family B
            __int128 Xbn = 3*Xb + 4*Yb;
            __int128 Ybn = 2*Xb + 3*Yb;
            Xb = Xbn; Yb = Ybn;
        }
    }

    cout << (ll)sum << "\n";
    return 0;
}
