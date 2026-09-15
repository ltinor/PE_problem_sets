#include <bits/stdc++.h>
using namespace std;

const int MAXK = 2000000;

int main() {
    vector<bool> is_prime(MAXK + 1, true);
    is_prime[0] = is_prime[1] = false;

    for(int i = 2; i * i <= MAXK; i++) {
        if(is_prime[i]) {
            for(int j = i * i; j <= MAXK; j += i) {
                is_prime[j] = false;
            }
        }
    }

    vector<long long> prefix(MAXK + 1, 0);
    for(int i = 1; i <= MAXK; i++) {
        prefix[i] = prefix[i-1];
        if(is_prime[i]) prefix[i] += i;
    }

    int T;
    cin >> T;
    while(T--) {
        int K;
        cin >> K;
        if(K <= 1) {
            cout << 0 << "\n";
        } else {
            cout << prefix[K-1] << "\n"; 
        }
    }

    return 0;
}