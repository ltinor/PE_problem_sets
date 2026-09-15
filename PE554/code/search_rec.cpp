#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    vector<ll> C = {0, 4, 25, 120, 497, 1924, 7265, 27288, 102745, 388692, 1477721, 5643064, 21632785, 83204260, 320932177, 1240939448};
    
    // Search for recurrence of order k
    for (int k = 2; k <= 6; k++) {
        cout << "Trying order " << k << "..." << endl;
        // Search small integer coefficients
        int range = 20;
        int total = 1;
        for (int i = 0; i < k; i++) total *= (2*range+1);
        
        vector<int> coeffs(k);
        for (int mask = 0; mask < total; mask++) {
            int m = mask;
            for (int i = 0; i < k; i++) {
                coeffs[i] = (m % (2*range+1)) - range;
                m /= (2*range+1);
            }
            
            // First coefficient should be positive (dominant term)
            if (coeffs[0] <= 0) continue;
            
            bool ok = true;
            for (int n = k+1; n < (int)C.size(); n++) {
                ll pred = 0;
                for (int j = 0; j < k; j++) {
                    pred += (ll)coeffs[j] * C[n-1-j];
                }
                if (pred != C[n]) { ok = false; break; }
            }
            if (ok) {
                cout << "Found! Coefficients: ";
                for (int j = 0; j < k; j++) cout << coeffs[j] << " ";
                cout << endl;
                return 0;
            }
        }
    }
    cout << "Not found in search range." << endl;
    return 0;
}
