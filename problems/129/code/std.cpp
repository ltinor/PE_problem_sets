#include<bits/stdc++.h>
using namespace std;

int mygcd(int a, int b) { while(b){int t=b; b=a%b; a=t;} return a; }

#define ll long long

// Compute A(n): smallest k such that R(k) % n == 0
// R(k) = 111...1 (k ones)
// Use remainder recurrence: r_{i+1} = (r_i * 10 + 1) % n
int A(int n) {
    int r = 1 % n;
    int k = 1;
    while (r != 0) {
        r = (r * 10 + 1) % n;
        k++;
    }
    return k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    // Find the least n such that A(n) > T and gcd(n, 10) = 1
    // Start from n = T (or slightly above), skip evens and multiples of 5
    int n = T;
    if (n % 2 == 0) n++;
    if (n % 5 == 0) n += 2;
    if (n < 3) n = 3;

    while (true) {
        if (n % 5 == 0) { n += 2; continue; }
        if (mygcd(n, 10) != 1) { n += 2; continue; }

        int a = A(n);
        if (a > T) {
            cout << n << "\n";
            return 0;
        }
        n += 2;
    }

    return 0;
}
