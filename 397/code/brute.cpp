#include<bits/stdc++.h>
using namespace std;
#define ll long long
// Brute: enumerate (k,a,b,c) and check if any angle is 45 degrees
int main() {
    ll K, X; cin >> K >> X;
    ll ans = 0;
    for (ll k=1; k<=K; k++) {
        for (ll a=-X; a<=X; a++) {
            for (ll b=a+1; b<=X; b++) {
                for (ll c=b+1; c<=X; c++) {
                    // Check 45-degree angle
                    // Using dot product: cos(theta) = (v·w)/(|v||w|)
                    // cos(45) = 1/√2
                    // Simplified: check if any angle = 45
                    double ya = (double)a*a/k, yb = (double)b*b/k, yc = (double)c*c/k;
                    // vectors AB = (b-a, yb-ya), AC = (c-a, yc-ya)
                    double dx1=b-a, dy1=yb-ya;
                    double dx2=c-a, dy2=yc-ya;
                    double dot = dx1*dx2 + dy1*dy2;
                    double l1 = sqrt(dx1*dx1+dy1*dy1);
                    double l2 = sqrt(dx2*dx2+dy2*dy2);
                    double cs = dot/(l1*l2);
                    if (fabs(cs*c - 0.5) < 1e-9) ans++;
                }
            }
        }
    }
    cout << ans << "\n";
}
