#include<bits/stdc++.h>
using namespace std;
using ll = long long;
// Brute: enumerate (k,a,b,c) and check if any angle is 45 degrees
// Uses integer arithmetic: 2*(v·w)^2 = |v|^2 * |w|^2

// After clearing denominators (multiply by k^4), we have:
// vector AB = (k*(b-a), b^2 - a^2)
// vector AC = (k*(c-a), c^2 - a^2)
// |AB|^2 = k^2*(b-a)^2 + (b^2-a^2)^2
// |AC|^2 = k^2*(c-a)^2 + (c^2-a^2)^2
// AB·AC = k^2*(b-a)*(c-a) + (b^2-a^2)*(c^2-a^2)
// Condition: 2*(AB·AC)^2 = |AB|^2 * |AC|^2

bool check_45(ll k, ll a, ll b, ll c) {
    // Check angle at A
    {
        ll dx1 = k*(b-a), dy1 = b*b - a*a;
        ll dx2 = k*(c-a), dy2 = c*c - a*a;
        ll dot = dx1*dx2 + dy1*dy2;
        ll len1 = dx1*dx1 + dy1*dy1;
        ll len2 = dx2*dx2 + dy2*dy2;
        if (2*dot*dot == len1*len2) return true;
    }
    // Check angle at B
    {
        ll dx1 = k*(a-b), dy1 = a*a - b*b;
        ll dx2 = k*(c-b), dy2 = c*c - b*b;
        ll dot = dx1*dx2 + dy1*dy2;
        ll len1 = dx1*dx1 + dy1*dy1;
        ll len2 = dx2*dx2 + dy2*dy2;
        if (2*dot*dot == len1*len2) return true;
    }
    // Check angle at C
    {
        ll dx1 = k*(a-c), dy1 = a*a - c*c;
        ll dx2 = k*(b-c), dy2 = b*b - c*c;
        ll dot = dx1*dx2 + dy1*dy2;
        ll len1 = dx1*dx1 + dy1*dy1;
        ll len2 = dx2*dx2 + dy2*dy2;
        if (2*dot*dot == len1*len2) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll K, X; cin >> K >> X;
    ll ans = 0;
    for (ll k = 1; k <= K; k++) {
        for (ll a = -X; a <= X; a++) {
            for (ll b = a+1; b <= X; b++) {
                for (ll c = b+1; c <= X; c++) {
                    if (check_45(k, a, b, c)) ans++;
                }
            }
        }
    }
    cout << ans << "\n";
}
