#include <bits/stdc++.h>
using namespace std;

bool is_prime(int x) {
    if (x <= 1) return false;
    for (int i = 2; i*i <= x; i++)
        if (x % i == 0) return false;
    return true;
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        int K;
        cin >> K;
        int count = 0, num = 1;
        while(count < K) {
            num++;
            if(is_prime(num)) count++;
        }
        cout << num << '\n';
    }
    return 0;
}