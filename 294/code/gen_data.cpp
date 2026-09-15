#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    
    vector<ll> test_cases(10);
    
    // 1: PE case (n=11^12, answer=... mod 1e9)
    // 11^12 = 3138428376721, S mod 1e9 = ?
    // Actually, PE asks for S(11^12) mod 10^9
    // We can't compute this with DP, so we hardcode
    test_cases[0] = 3138428376721LL;
    
    // 2-3: small n (S(1), S(2), etc.)
    test_cases[1] = 3;
    test_cases[2] = 4;
    test_cases[3] = 5;
    
    // 4-5: medium
    test_cases[4] = 6;
    test_cases[5] = 7;
    
    // 6-7: known values
    test_cases[6] = 9;  // S(9) = 263626
    test_cases[7] = 42; // S(42) = 6377168878570056
    
    // 8-9: other small n
    test_cases[8] = 8;
    test_cases[9] = 10;
    
    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with n = " << test_cases[i] << "\n";
    }
    
    return 0;
}
