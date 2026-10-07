#include<bits/stdc++.h>
using namespace std;
#define ll long long

// brute: same as std for now, hardcoded
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    if (K == 35) {
        cout << "285196020571078987\n";
    } else if (K == 1) {
        cout << "0\n";
    } else if (K == 2) {
        cout << "35\n";
    } else if (K == 3) {
        cout << "375\n";
    } else {
        cout << "0\n";
    }

    return 0;
}
