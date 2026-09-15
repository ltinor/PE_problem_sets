#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: generate Fibonacci words until we have enough digits

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string A, B;
    getline(cin, A);
    getline(cin, B);

    ll n;
    cin >> n;

    // Generate Fibonacci words until we have >= n digits
    string s1 = A, s2 = B;
    while ((ll)s2.size() < n) {
        string next = s1 + s2;
        s1 = s2;
        s2 = next;
    }

    // The first term with >= n digits is the current s2
    cout << s2[n - 1] << "\n";
    return 0;
}
