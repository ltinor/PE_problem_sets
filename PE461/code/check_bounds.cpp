#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Quick check: what's the max possible g(10000)?
const double PI = acos(-1.0);

int main() {
    int n = 10000;
    int K = (int)(n * log(PI + 1.0));
    cout << "K_max = " << K << endl;
    cout << "Max a^2+b^2+c^2+d^2 = " << 4LL * K * K << endl;
    
    // Verify for smaller n
    for (int tn : {200, 500}) {
        int tK = (int)(tn * log(PI + 1.0));
        cout << "n=" << tn << " K=" << tK << " max_g=" << 4LL*tK*tK << endl;
    }
}
