#include <bits/stdc++.h>
using namespace std;

bool is_prime(int x) {
    if(x < 2) return false;
    for(int i = 2; i * i <= x; i++) {
        if(x % i == 0) return false;
    }
    return true;
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        int K;
        cin >> K;

        long long sum = 0;
        for(int i = 2; i < K; i++) {
            if(is_prime(i)) sum += i;
        }

        cout << sum << "\n";
    }

    return 0;
}