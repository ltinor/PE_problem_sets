#include<bits/stdc++.h>
using namespace std;

int mygcd(int a, int b) { while(b){int t=b; b=a%b; a=t;} return a; }

#define ll long long

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
