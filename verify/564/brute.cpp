#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force for PE564: enumerate all partitions and compute expected area

int main() {
    ll n;
    cin >> n;
    
    // Enumerate all compositions (ordered splits) of 2n-3 into n positive parts
    // Actually, enumerate all multisets and count permutations
    // For small n, direct enumeration
    ll N = n - 3;
    
    // Recursively generate partitions and compute area
    cout << "0.0\n"; // placeholder
    return 0;
}
